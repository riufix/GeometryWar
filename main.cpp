#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>
#include <list>

#include "GameManager.h"
#include "BulletManager.h"
#include "MonsterManager.h"

#include "audio.h"
#include "Player.h"
#include "BulletBehaviour.h"
#include "map.h"
#include "Monster.h"
#include "Effect.h"
#include "text.h"
#include "deathParticle.h"

int main()
{
#pragma region AwakeInitialisation
	//Init Window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Orkan", sf::Style::Default, settings);
	window.setVerticalSyncEnabled(true);
	//clock
	sf::Clock frameClock;
	//Center of window
	sf::Vector2f windowCenter;
	windowCenter.x = window.getSize().x / 2.0f;
	windowCenter.y = window.getSize().y / 2.0f;

	//Init GameState
	GameManager gameManager;
	gameManager.currentGameState = MainMenu;
	gameManager.Reset();

	//Init Effect & Particles
	Effect effect;
	ParticleSystem particles;

	//Init Player
	Player player;
	player.InitializeGraphic();

	//Init Bullet List
	BulletManager bulletManager;

	//Init Map
	sf::ConvexShape map;
	std::vector<sf::Vector3f> positionVector;
	levelShape currentLevel = levelShape::triangle;
	changeLevel(map, positionVector, currentLevel);


	//Init Menu
	const std::vector<sf::ConvexShape> textCopyright = stringToDisplayable("2023 | Baptiste V | Enguerrand C | Titouan D | A2 JV GP");
	const std::vector<sf::ConvexShape> textTitle = stringToDisplayable("ORKAN");
	const std::vector<sf::ConvexShape> textMission1 = stringToDisplayable("Welcome Aboard Captain!");
	const std::vector<sf::ConvexShape> textMission2 = stringToDisplayable("Your mission is to prevent enemy ships");
	const std::vector<sf::ConvexShape> textMission3 = stringToDisplayable("from reaching your position!");
	const std::vector<sf::ConvexShape> textControl1 = stringToDisplayable("[SPACE] to fire   ");
	const std::vector<sf::ConvexShape> textControl2 = stringToDisplayable("   [Q][D] to move");
	const std::vector<sf::ConvexShape> textControl3 = stringToDisplayable("   [Arrows]");
	const std::vector<sf::ConvexShape> textHighScore = stringToDisplayable("current HighScore   ");
	const std::vector<sf::ConvexShape> textStart = stringToDisplayable("Press [Space] when ready to start");
	float titleScale = 0;
	float startTempo = 0;
	float isStarting = false;

	//Init Ennemy List
	MonsterManager monsterManager;

	//Init GameOver
	const std::vector<sf::ConvexShape> textGameOver1 = stringToDisplayable("GAME");
	const std::vector<sf::ConvexShape> textGameOver2 = stringToDisplayable("OVER");
	const std::vector<sf::ConvexShape> textGOScore = stringToDisplayable("Score  ");
	const std::vector<sf::ConvexShape> textGOHighScore = stringToDisplayable("HighScore  ");
	const std::vector<sf::ConvexShape> textGONewRecord = stringToDisplayable("New Record!");
	const std::vector<sf::ConvexShape> textBackToMenu = stringToDisplayable("press [Space] to go back to the menu");
	float gameOverTempo = 0;
	float gameOverTimer = 0;
	int highScore = 1000;

	//Init audio
	Audio audioSystem;
	audioSystem.InitializeSoundBuffer();
	audioSystem.InitializeMusicBuffer();

#pragma endregion

	audioSystem.musicList["Menu"].play();
	while (window.isOpen())
	{
		float deltaTime = frameClock.restart().asSeconds();
		//std::cout << 1.f / deltaTime << " FPS" << std::endl;

		//Event
		sf::Event event;
		while (window.pollEvent(event))
		{
			// On gère l'événément
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			default:
				break;
			}
		}

		/* --------------
			LOGIC
		-------------- */
		switch (gameManager.currentGameState)
		{
		case MainMenu:
			//Intro Title animation
			if (titleScale < 20) titleScale += 0.1;
			else {
				titleScale = 20;
				if (player.ProcessFireInput(deltaTime) || isStarting) {

					if (startTempo < 10) startTempo += 0.1;
					else {
						//Reset Variables
						player.Reset();
						gameManager.Reset();

						//Reset Level
						currentLevel = levelShape::triangle;
						changeLevel(map, positionVector, currentLevel);

						bulletManager.bulletList.clear();
						monsterManager.monsterList.clear();
						monsterManager.PushFirstMonster(positionVector, windowCenter);

						
						audioSystem.musicList["Menu"].stop();
						audioSystem.musicList["Game"].play();
						//Reset transitionTimer & launch levelIntro
						gameManager.transitionTime = 0.0f;
						gameManager.currentGameState = LevelIntro;
					}
					isStarting = true;
				}
			}
			break;

		case LevelIntro:
			if(gameManager.transitionTime == 0)
				audioSystem.soundList["levelIntro"].play();

			if (gameManager.transitionTime < 1.0f)
			{
				gameManager.transitionTime = gameManager.transitionTime + deltaTime;
				particles.AddParticle(sf::Vector2f(rand() % (int)(windowCenter.x * 2), rand() % (int)(windowCenter.y * 2)), true, windowCenter);
			}
			else
			{
				particles.ClearParticles();
				gameManager.currentGameState = Game;
			}
			break;

		case Game:
			//Process Player Input
			player.ProcessMoveInput(positionVector.size(), deltaTime);
			player.UpdateSprite(positionVector[player.positionIndex].x, positionVector[player.positionIndex].y, positionVector[player.positionIndex].z);
			if (player.ProcessFireInput(deltaTime))
			{
				bulletManager.bulletList.push_back(BulletBehaviour(BulletBehaviour::Owner::Player, 100, player.positionIndex, player.shape.getPosition()));
				audioSystem.soundList["playerShoot"].play();
			}

			player.ProcessInvincibility(deltaTime);

			//Look if go to next level
			gameManager.ChkNextLevel(audioSystem, particles);
			break;

		case GameOver:
			gameOverTimer += deltaTime;

			if (gameOverTempo < 25.0f) gameOverTempo += 0.1f;
			else {
				if (player.ProcessFireInput(deltaTime)) {
					titleScale = 0;
					startTempo = 0;
					isStarting = false;

					audioSystem.musicList["Gameover"].stop();
					audioSystem.musicList["Menu"].play();

					gameManager.currentGameState = MainMenu;
				}
			}

			if (gameManager.score > highScore) highScore = gameManager.score;
			break;

		case LevelTransition:
			if (gameManager.transitionTime < 40.0f)
				gameManager.transitionTime = gameManager.transitionTime + deltaTime * 15;
			else
			{
				//Change Level
				AddLevel(currentLevel);
				changeLevel(map, positionVector, currentLevel);

				//Clear bulletList & Reset player position
				player.positionIndex = 0;
				bulletManager.bulletList.clear();

				//Add level and add new number of monsters
				gameManager.level++;
				monsterManager.monsterList.clear();
				for (int i = 0; i < gameManager.level; i++)
					monsterManager.SpawnMonster(positionVector, windowCenter, gameManager.level);

				if (gameManager.level % 3 == 0) //Give one life if complete each map
					player.Health++;

				//Reset transitionTimer & launch levelIntro
				gameManager.transitionTime = 0.0f;
				gameManager.currentGameState = LevelIntro;
			}
			break;
		}


		/*-------------
		   PARTICLES
		--------------*/
		particles.update(sf::seconds(deltaTime), gameManager.currentGameState == LevelIntro);


		/* --------------
			DISPLAY
		-------------- */
		window.clear();
		effect.UpdateEffect(window, deltaTime);

		switch (gameManager.currentGameState)
		{
		case MainMenu:
		{
			if (startTempo < 10) {
				DisplayText(window, textCopyright, sf::Vector2f(windowCenter.x, 50), 3);
				DisplayText(window, textTitle, sf::Vector2f(windowCenter.x, 200), titleScale, effect.RandomColor());

				if (titleScale >= 20) {
					DisplayText(window, textMission1, sf::Vector2f(windowCenter.x, 400), 6, sf::Color::Yellow);
					DisplayText(window, textMission2, sf::Vector2f(windowCenter.x, 475), 6);
					DisplayText(window, textMission3, sf::Vector2f(windowCenter.x, 525), 6);

					DisplayText(window, textControl1, sf::Vector2f(windowCenter.x, 650), 6, sf::Color::Red, right);
					DisplayText(window, textControl2, sf::Vector2f(windowCenter.x, 650), 6, sf::Color::Red, left);
					DisplayText(window, textControl3, sf::Vector2f(windowCenter.x, 700), 6, sf::Color::Red, left);

					DisplayText(window, textHighScore, sf::Vector2f(windowCenter.x +180, 800), 5, sf::Color::White, right);
					DisplayText(window, stringToDisplayable(std::to_string(highScore)), sf::Vector2f(windowCenter.x +180, 800), 5, sf::Color::White, left);

					if (!isStarting) DisplayText(window, textStart, sf::Vector2f(windowCenter.x, 1000), 6, sf::Color::Green);
					else DisplayText(window, textStart, sf::Vector2f(windowCenter.x, 1000), 6, effect.RandomColor());
				}
			}
			else window.clear();
		}
		break;

		case Game:
		{
			//Display level
			DrawLevel(window, map, windowCenter, 5, 30, player.positionIndex);

			//Display & manage Ennemies
			monsterManager.ProcessMonsters(audioSystem, player, effect, particles, gameManager, window, bulletManager, positionVector, windowCenter, deltaTime, gameOverTempo);
			bulletManager.ProcessBullets(audioSystem, effect, player, window, gameManager, deltaTime, gameOverTempo, windowCenter);

			//Display player
			player.DrawSprite(window);

			//Display UI
			for (int i = 0; i < player.Health; i++)
			{
				player.UpdateSprite(100 + i * 150, 100, player.shape.getRotation());
				player.DrawSprite(window);
			}
			DisplayText(window, stringToDisplayable(std::to_string(gameManager.score)), sf::Vector2f(windowCenter.x * 2 - 50, 100), 10.0f, sf::Color::White, textOrigin::right);
		}
		break;

		case GameOver:
		{
			//Display static gameplay
			DrawLevel(window, map, windowCenter, 5, 30, -1);

			for (Monster& monster : monsterManager.monsterList)
				monster.DrawSprite(window);
			for (BulletBehaviour& bullet : bulletManager.bulletList)
				bullet.DisplayBullet(window, 0);
			player.DrawSprite(window);

			//Display Game Over
			float gameOverWaveAnimation =  20 * sin(gameOverTimer);
			sf::Color gameOverWaveColor = sf::Color(255, 191 + 64 * sin(gameOverTimer * 30), 191 + 64 * sin(gameOverTimer * 30));
			DisplayText(window, textGameOver1, sf::Vector2f(windowCenter.x, windowCenter.y - 10 * 20.0f + gameOverWaveAnimation), 20.0f, gameOverWaveColor);
			DisplayText(window, textGameOver2, sf::Vector2f(windowCenter.x, windowCenter.y + 0 * 20.0f + gameOverWaveAnimation), 20.0f, gameOverWaveColor);

			//Display Score
			if (gameOverTempo >= 5.0f) 	DisplayText(window, textGOScore, sf::Vector2f(windowCenter.x + 20, windowCenter.y + 10 * 20.0f), 10.0f, sf::Color::White, right);
			if (gameOverTempo >= 10.0f) DisplayText(window, stringToDisplayable(std::to_string(gameManager.score)), sf::Vector2f(windowCenter.x + 20, windowCenter.y + 10 * 20.0f), 10.0f, sf::Color::White, textOrigin::left);
			if (gameOverTempo >= 15.0f) DisplayText(window, textGOHighScore, sf::Vector2f(windowCenter.x + 20, windowCenter.y + 15 * 20.0f), 10.0f, sf::Color::White, right);
			if (gameOverTempo >= 20.0f) {
				if (gameManager.score == highScore) {
					DisplayText(window, stringToDisplayable(std::to_string(highScore)), sf::Vector2f(windowCenter.x + 20, windowCenter.y + 15 * 20.0f), 10.0f, effect.RandomColor(), textOrigin::left);
					DisplayText(window, textGONewRecord, sf::Vector2f(windowCenter.x + 18, windowCenter.y + 18 * 20.0f), 3.0f, effect.RandomColor(), textOrigin::left);
				}
				else {
					DisplayText(window, stringToDisplayable(std::to_string(highScore)), sf::Vector2f(windowCenter.x + 20, windowCenter.y + 15 * 20.0f), 10.0f, sf::Color::White, textOrigin::left);
				}
			}
			if (gameOverTempo >= 25.0f) DisplayText(window, textBackToMenu, sf::Vector2f(windowCenter.x, windowCenter.y + 21 * 20.0f), 5.0f, sf::Color::Green);
		}
		break;

		case LevelIntro:
		case LevelTransition:
		{
			DrawLevel(window, map, windowCenter, 5 * gameManager.transitionTime, 30 * gameManager.transitionTime, -1, effect.RandomColor());
		}
		break;
		}

		//display particle effect
		window.draw(particles);
		window.display();
	}
}

/*void saveScore(std::string text) {
	std::ifstream iSavefile("score.txt");
	std::ofstream oSavefile("score.txt");
	std::string currentLine;

	if (oSavefile.is_open()) {
		while (std::getline(iSavefile, currentLine)) {
			if (currentLine == "highscore:") oSavefile << text;
			else oSavefile << "highscore:" << text;
		}

		oSavefile.close();
		std::cout << "information written\n";
	}
	else std::cout << "Unable to open file 'savedData/score.txt\n'";
}
std::string readScore() {
	std::ifstream iSavefile("score.txt");
	std::string currentLine;
	std::string score = "0";

	if (iSavefile.is_open()) {
		std::getline(iSavefile, currentLine);

		if (currentLine == "highscore:") {
			score = iSavefile.get();
		}

		iSavefile.close();
	}
	else std::cout << "Unable to open file 'savedData/score.txt\n'";

	std::cout << score << std::endl;
	return score;
}*/

/*
//optimize:
	Transfer bullet display to bullet Manager
	Transfer Ennemis display to ennemy Manager
*/