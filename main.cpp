#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>
#include <list>

#include "GameManager.h"
#include "BulletManager.h"
#include "MonsterManager.h"
#include "MenuManager.h"
#include "GameoverManager.h"

#include "Player.h"
#include "map.h"

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
	MenuManager menuManager;

	//Init Ennemy List
	MonsterManager monsterManager;

	//Init GameOver
	GameoverManager gameoverManager;

	//Init audio
	Audio audioSystem;
	audioSystem.InitializeSoundBuffer();
	audioSystem.InitializeMusicBuffer();
	audioSystem.ChangeMusic("Menu");
#pragma endregion

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
			if (menuManager.titleScale < 20) menuManager.titleScale += 0.1;
			else {
				menuManager.titleScale = 20;
				if (player.ProcessFireInput(deltaTime) || menuManager.isStarting) {

					if (menuManager.startTempo < 10) menuManager.startTempo += 0.1;
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

						
						audioSystem.ChangeMusic("Game");
						//Reset transitionTimer & launch levelIntro
						gameManager.transitionTime = 0.0f;
						gameManager.currentGameState = LevelIntro;
					}
					menuManager.isStarting = true;
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
			if (gameoverManager.gameOverTempo < 25.0f) gameoverManager.gameOverTempo += 0.1f;
			else {
				if (player.ProcessFireInput(deltaTime)) {
					menuManager.Reset();
					audioSystem.ChangeMusic("Menu");
					gameoverManager.gameOverTempo = 0;
					gameManager.currentGameState = MainMenu;
				}
			}

			if (gameManager.score > gameManager.highScore) gameManager.highScore = gameManager.score;
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
			menuManager.DisplayMenu(window, windowCenter, effect, gameManager);
		}
		break;

		case Game:
		{
			//Display level
			DrawLevel(window, map, windowCenter, 5, 30, player.positionIndex);

			//Display & manage Ennemies
			monsterManager.ProcessMonsters(audioSystem, player, effect, particles, gameManager, window, bulletManager, positionVector, windowCenter, deltaTime, gameoverManager.gameOverTempo);
			bulletManager.ProcessBullets(audioSystem, effect, player, window, gameManager, deltaTime, gameoverManager.gameOverTempo, windowCenter);

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

			gameoverManager.DisplayGameOver(window, effect, windowCenter, deltaTime, gameManager.score, gameManager.highScore);
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