#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <list>

#include "audio.h"
#include "Player.h"
#include "BulletBehaviour.h"
#include "map.h"
#include "Monster.h"
#include "Effect.h"
#include "text.h"
#include "deathParticle.h"

constexpr enum gameState {
	MainMenu,
	LevelIntro,
	Game,
	GameOver,
	LevelTransition
};

//Prototypes
void SpawnMonster(std::list<Monster>& monsterList, std::vector<sf::Vector3f>& positionVector, sf::Vector2f windowCenter, int currentLevel);
void ChkPlayerHit(Player& player, Effect& effect, gameState& currentState, float& gameOverTimer, Audio& soundSystem);

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
	gameState currentGameState = MainMenu;
	int score = 0;
	int scoreNeeded = 100;
	int scoreNextLvl = 300;
	int level = 1;

	//Init Effect & Particles
	Effect effect;
	ParticleSystem particles;

	//Init Player
	Player player;
	player.InitializeGraphic();

	//Init Bullet List
	std::list<BulletBehaviour> bulletList;

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
	const std::vector<sf::ConvexShape> textStart = stringToDisplayable("Press [Space] when ready to start");
	float titleScale = 0;
	float startTempo = 0;
	float isStarting = false;

	//Init Ennemy List
	std::list<Monster> monsterList;
	int newCorridor = rand() % positionVector.size();
	monsterList.push_back(Monster(windowCenter, positionVector[newCorridor], newCorridor, 1));

	//Init Transition level & Game Over Timer
	float transitionTime = 1.0f;

	//Init GameOver
	const std::vector<sf::ConvexShape> textGameOver1 = stringToDisplayable("GAME");
	const std::vector<sf::ConvexShape> textGameOver2 = stringToDisplayable("OVER");
	const std::vector<sf::ConvexShape> textGOScore = stringToDisplayable("Score  ");
	const std::vector<sf::ConvexShape> textGOHighScore = stringToDisplayable("HighScore  ");
	const std::vector<sf::ConvexShape> textBackToMenu = stringToDisplayable("press [Space] to go back to the menu");
	float gameOverTempo = 0;
	float gameOverTimer = 0;
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
		switch (currentGameState)
		{
		case MainMenu:
			//Intro Title animation
			if (titleScale < 20) titleScale += 0.1;
			else {
				titleScale = 20;
				if (player.ProcessFireInput(deltaTime) || isStarting) {
					if (startTempo < 10) startTempo += 0.1;
					else {
						//Start Level
						level = 1;
						score = 0;
						scoreNeeded = 100;

						//Reset Variables
						player.Reset();
						bulletList.clear();
						monsterList.clear();
						int newCorridor = rand() % positionVector.size();
						monsterList.push_back(Monster(windowCenter, positionVector[newCorridor], newCorridor, 1));
						
						audioSystem.musicList["Menu"].stop();
						audioSystem.musicList["Game"].play();
						//Reset transitionTimer & launch levelIntro
						transitionTime = 0.0f;
						currentGameState = LevelIntro;
					}
					isStarting = true;
				}
			}
			break;

		case LevelIntro:
			if(transitionTime == 0)
				audioSystem.soundList["levelIntro"].play();

			if (transitionTime < 1.0f)
				transitionTime = transitionTime + deltaTime;
			else
				currentGameState = Game;
			break;

		case Game:
			//Process Player Input
			player.ProcessMoveInput(positionVector.size(), deltaTime);
			player.UpdateSprite(positionVector[player.positionIndex].x, positionVector[player.positionIndex].y, positionVector[player.positionIndex].z);
			if (player.ProcessFireInput(deltaTime))
			{
				bulletList.push_back(BulletBehaviour(BulletBehaviour::Owner::Player, 100, player.positionIndex, player.shape.getPosition()));
				audioSystem.soundList["playerShoot"].play();
			}

			player.ProcessInvincibility(deltaTime);

			//Look if go to next level
			if (score >= scoreNeeded)
			{
				scoreNeeded = scoreNeeded + scoreNextLvl * level;
				particles.ClearParticles();

				currentGameState = LevelTransition;
				audioSystem.soundList["levelEnd"].play();
				transitionTime = 1.0f;
			}

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

					currentGameState = MainMenu;
				}
			}
			break;

		case LevelTransition:
			if (transitionTime < 40.0f)
				transitionTime = transitionTime + deltaTime * 15;
			else
			{
				//Change Level
				AddLevel(currentLevel);
				changeLevel(map, positionVector, currentLevel);

				//Clear bulletList & Reset player position
				player.positionIndex = 0;
				bulletList.clear();

				//Add level and add new number of monsters
				level++;
				monsterList.clear();
				for (int i = 0; i < level; i++)
					SpawnMonster(monsterList, positionVector, windowCenter, level);

				if (level % 3 == 0) //Give one life if complete each map
					player.Health++;

				//Reset transitionTimer & launch levelIntro
				transitionTime = 0.0f;
				currentGameState = LevelIntro;
			}
			break;
		}


		/*-------------
		   PARTICLES
		--------------*/
		particles.update(sf::seconds(deltaTime));


		/* --------------
			DISPLAY
		-------------- */
		window.clear();
		effect.UpdateEffect(window, deltaTime);

		switch (currentGameState)
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
			DrawLevel(window, map, windowCenter, 5, 30);

			//Display & manage Ennemies
			std::list<Monster>::iterator monsterListIt = monsterList.begin();
			while (monsterListIt != monsterList.end())
			{
				bool skipToNext = false; //skip if collision
				if (monsterListIt->ProcessMonster(deltaTime, bulletList))
				{
					if (monsterListIt->progression > 100)
						ChkPlayerHit(player, effect, currentGameState, gameOverTempo, audioSystem);

					monsterListIt = monsterList.erase(monsterListIt);
					SpawnMonster(monsterList, positionVector, windowCenter, level);
				}
				else
				{
					//Manage Ennemies - Bullet Collision
					std::list<BulletBehaviour>::iterator bulletCollisionListIt = bulletList.begin();
					while (bulletCollisionListIt != bulletList.end())
					{
						if (monsterListIt->ChkCollision(*bulletCollisionListIt))
						{
							skipToNext = true;
							score = score + 25;

							bulletCollisionListIt = bulletList.erase(bulletCollisionListIt);
							bulletCollisionListIt = bulletList.end();

							monsterListIt->Health--;
							if (monsterListIt->progression < 95) //Knockback Effect
								monsterListIt->progression -= 10;
							if (monsterListIt->Health <= 0)
							{
								particles.addParticles(100, monsterListIt->shape.getPosition());
								//particle on ennemi death position
								audioSystem.soundList["monsterDeath"].play();
								monsterListIt = monsterList.erase(monsterListIt);

								SpawnMonster(monsterList, positionVector, windowCenter, level);
							}
							else
								audioSystem.soundList["monsterHit"].play();
						}
						else
							bulletCollisionListIt++;
					}

					if (skipToNext) continue;
					monsterListIt->DrawSprite(window);
					monsterListIt++;
				}
			}

			//Display & manage projectiles
			std::list<BulletBehaviour>::iterator bulletListIt = bulletList.begin();
			while (bulletListIt != bulletList.end())
			{
				//Collision btw Bullets
				if (bulletListIt->CheckOtherBulletCollision(bulletList, bulletListIt))
				{
					audioSystem.soundList["bulletHit"].play();
					continue;
				}

				if (bulletListIt->ProcessBullet(windowCenter))
				{
					if (bulletListIt->CheckPlayerCollision(player.positionIndex)) //Collision with player
						ChkPlayerHit(player, effect, currentGameState, gameOverTempo, audioSystem);
					bulletListIt = bulletList.erase(bulletListIt);
				}
				else
				{
					bulletListIt->DisplayBullet(window, deltaTime);
					bulletListIt++;
				}
			}

			//Display player
			player.DrawSprite(window);

			//Display UI
			for (int i = 0; i < player.Health; i++)
			{
				player.UpdateSprite(100 + i * 150, 100, player.shape.getRotation());
				player.DrawSprite(window);
			}
			DisplayText(window, stringToDisplayable(std::to_string(score)), sf::Vector2f(windowCenter.x * 2 - 50, 100), 10.0f, sf::Color::White, textOrigin::right);
		}
		break;

		case GameOver:
		{
			//Display static gameplay
			DrawLevel(window, map, windowCenter, 5, 30);

			for (Monster& monster : monsterList)
				monster.DrawSprite(window);
			for (BulletBehaviour& bullet : bulletList)
				bullet.DisplayBullet(window, 0);
			player.DrawSprite(window);

			//Display Game Over
			float gameOverWaveAnimation =  20 * sin(gameOverTimer);
			sf::Color gameOverWaveColor = sf::Color(255, 64 + 64 * sin(gameOverTimer * 10), 64 + 64 * sin(gameOverTimer * 10));
			DisplayText(window, textGameOver1, sf::Vector2f(windowCenter.x, windowCenter.y - 10 * 20.0f + gameOverWaveAnimation), 20.0f, gameOverWaveColor);
			DisplayText(window, textGameOver2, sf::Vector2f(windowCenter.x, windowCenter.y + 0 * 20.0f + gameOverWaveAnimation), 20.0f, gameOverWaveColor);

			//Display Score
			if (gameOverTempo >= 5.0f) 	DisplayText(window, textGOScore, sf::Vector2f(windowCenter.x + 20, windowCenter.y + 10 * 20.0f), 10.0f, sf::Color::White, right);
			if (gameOverTempo >= 10.0f) DisplayText(window, stringToDisplayable(std::to_string(score)), sf::Vector2f(windowCenter.x + 20, windowCenter.y + 10 * 20.0f), 10.0f, sf::Color::White, textOrigin::left);
			if (gameOverTempo >= 15.0f) DisplayText(window, textGOHighScore, sf::Vector2f(windowCenter.x + 20, windowCenter.y + 15 * 20.0f), 10.0f, sf::Color::White, right);
			if (gameOverTempo >= 20.0f) DisplayText(window, stringToDisplayable(std::to_string(score)), sf::Vector2f(windowCenter.x + 20, windowCenter.y + 15 * 20.0f), 10.0f, sf::Color::White, textOrigin::left);
			if (gameOverTempo >= 25.0f) DisplayText(window, textBackToMenu, sf::Vector2f(windowCenter.x, windowCenter.y + 21 * 20.0f), 5.0f, sf::Color::Green);
		}
		break;

		case LevelIntro:
		case LevelTransition:
		{
			DrawLevel(window, map, windowCenter, 5 * transitionTime, 30 * transitionTime, effect.RandomColor());

		}
		break;
		}

		//display particle effect
		window.draw(particles);
		window.display();
	}
}

void SpawnMonster(std::list<Monster>& monsterList, std::vector<sf::Vector3f>& positionVector, sf::Vector2f windowCenter, int currentLevel)
{
	int newCorridor = rand() % positionVector.size();
	int newHealth = 1 + rand() % currentLevel > 2 ? 3 :
		currentLevel > 1 ? 2 :
		1;
	monsterList.push_back(Monster(windowCenter, positionVector[newCorridor], newCorridor, newHealth));
}

void ChkPlayerHit(Player& player, Effect& effect, gameState& currentState, float& gameOverTimer, Audio& audioSystem)
{
	if (!player.isInvincible())
		if (player.Hit()) {
			audioSystem.musicList["Game"].stop();
			audioSystem.musicList["Gameover"].play();
			currentState = GameOver;
			gameOverTimer = 0;
		}
		else
		{
			effect.ChangeFlashScreen(1.0f, false, sf::Color::Red);
			audioSystem.soundList["playerHit"].play();
		}
}

/*
//Prb :
	Enemies on top of each others

//optimize:
	Transfer bullet display to bullet Manager
	Transfer Ennemis display to ennemy Manager
*/