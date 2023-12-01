#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <list>

#include "Player.h"
#include "BulletBehaviour.h"
#include "map.h"
#include "Monster.h"
#include "Effect.h"
#include "text.h"

constexpr enum levelShape {
	triangle,
	square,
	pantagone
};

constexpr enum gameState {
	MainMenu,
	Game,
	GameOver,
	LevelTransition
};

int main()
{
	//Init Window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Geometry Wars",sf::Style::Default, settings);
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
	int scoreNextLvl = 150;
	//Init Effect
	Effect effect;

	//Init Player
	Player player;
	player.InitializeGraphic();
	
	//Init Bullet List
	std::list<BulletBehaviour> bulletList;

	//Init Map
	sf::ConvexShape map;

	//Init player position list
	sf::Vector3f TrianglePositionList[9] = {
	{1090,330,55},
	{1220,500, 60},
	{1360,730,55},
	{1250,890,180},
	{960,890,180},
	{690,890,180},
	{560,730,-50},
	{690,510,-55},
	{830,330,-55}
	};
	sf::Vector3f SquarePositionList[8] = {
	{1100,195,0},
	{1300,400,90},
	{1300,650,90},
	{1100,875,180},
	{800,875,180},
	{620,650,-90},
	{620,400,-90},
	{820,195,0}
	};
	sf::Vector3f PantagonePositionList[5] = {
	{1150,370,54},
	{1240,700,108},
	{975,890,175},
	{680,700,-108},
	{775,370,-54}
	};

	std::vector<sf::Vector3f> positionVector;
	levelShape currentlevel = pantagone;
	positionVector.clear();
	switch (currentlevel)
	{
	case triangle:
		map = InitializeTriangle();
		for (int i = 0; i < 9; i++) {
			positionVector.push_back(TrianglePositionList[i]);
		}
		break;

	case square:
		map = InitializeSquare();
		for (int i = 0; i < 8; i++) {
			positionVector.push_back(SquarePositionList[i]);
		}
		break;

	case pantagone:
		map = InitializePantagone();
		for (int i = 0; i < 5; i++) {
			positionVector.push_back(PantagonePositionList[i]);
		}
		break;

	default:
		break;
	}

	//Init Menu
	std::vector<sf::ConvexShape> textCopyright = stringToDisplayable("2023 | Baptiste V | Enguerrand C | Titouan D");
	std::vector<sf::ConvexShape> textTitle = stringToDisplayable("ORKAN");
	float titleScale = 0;

	std::vector<sf::ConvexShape> textMission1 = stringToDisplayable("Welcome Aboard Captain!");
	std::vector<sf::ConvexShape> textMission2 = stringToDisplayable("Your mission is to prevent enemy ships");
	std::vector<sf::ConvexShape> textMission3 = stringToDisplayable("from reaching your position!");

	std::vector<sf::ConvexShape> textControl1 = stringToDisplayable("[SPACE] to fire   ");
	std::vector<sf::ConvexShape> textControl2 = stringToDisplayable("   [Q][D] to move");
	std::vector<sf::ConvexShape> textControl3 = stringToDisplayable("   [Arrows]");

	std::vector<sf::ConvexShape> textStart = stringToDisplayable("Press [Space] when ready to start");
	float startTempo = 0;
	float isStarting = false;

	//Init Ennemy List
	std::list<Monster> monsterList;
	int newCorridor = rand() % positionVector.size();
	monsterList.push_back(Monster(windowCenter, positionVector[newCorridor], newCorridor));

	//Init Transition level variables
	float transitionTime = 1.0f;

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
			if (titleScale < 20) titleScale += 0.1;

			else {
				titleScale = 20;

				if (player.ProcessFireInput(deltaTime) || isStarting) {
					if (startTempo < 10) startTempo += 0.1;
					else if (startTempo >= 15) {
						//Start Level
					}

					isStarting = true;
				}
			}

			break;
		case Game:
			//Process Player Input
			player.ProcessMoveInput(positionVector.size(), deltaTime);
			player.UpdateSprite(positionVector[player.positionIndex].x, positionVector[player.positionIndex].y, positionVector[player.positionIndex].z);
			if (player.ProcessFireInput(deltaTime))
			{
				bulletList.push_back(BulletBehaviour(BulletBehaviour::Owner::Player, 100, player.positionIndex, player.shape.getPosition()));
			}
			
			player.ProcessInvincibility(deltaTime);
			
			if (score >= scoreNeeded) 
			{
				scoreNeeded = scoreNeeded + scoreNextLvl;
				currentGameState = LevelTransition;
				transitionTime = 1.0f;
			}

			break;

		case GameOver:
			break;
		case LevelTransition:
			if (transitionTime < 40.0f)
				transitionTime = transitionTime + deltaTime * 15;
			else
			{
				//Change Level
				//currentGameState = Game;
			}
			break;
		}




		/* --------------
			DISPLAY
		-------------- */
		window.clear();
		effect.UpdateEffect(window, deltaTime);

		switch (currentGameState)
		{
		case MainMenu:
		{
			//ORKAN
			float windowCenter = window.getSize().x/2;

			if (startTempo < 10) {
				DisplayText(window, textCopyright, sf::Vector2f(windowCenter, 50), 3);

				DisplayText(window, textTitle, sf::Vector2f(windowCenter, 200), titleScale, effect.RandomColor());
				if (titleScale >= 20) {
					DisplayText(window, textMission1, sf::Vector2f(windowCenter, 400), 6, sf::Color::Yellow);
					DisplayText(window, textMission2, sf::Vector2f(windowCenter, 475), 6);
					DisplayText(window, textMission3, sf::Vector2f(windowCenter, 525), 6);

					DisplayText(window, textControl1, sf::Vector2f(windowCenter, 650), 6, sf::Color::Red, right);
					DisplayText(window, textControl2, sf::Vector2f(windowCenter, 650), 6, sf::Color::Red, left);
					DisplayText(window, textControl3, sf::Vector2f(windowCenter, 700), 6, sf::Color::Red, left);

					if (!isStarting) DisplayText(window, textStart, sf::Vector2f(windowCenter, 1000), 6, sf::Color::Green);
					else DisplayText(window, textStart, sf::Vector2f(windowCenter, 1000), 6, effect.RandomColor());
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
				if (monsterListIt->ProcessMonster(deltaTime))
				{
					if (monsterListIt->progression > 100)
					{
						/*if (!player.isInvincible())
							if (player.Hit())
								currentGameState = GameOver;
							else
							{
								effect.ChangeFlashScreen(1.0f, false, sf::Color::Red);
							}*/
					}

					monsterListIt = monsterList.erase(monsterListIt);

					int newCorridor = rand() % positionVector.size();
					monsterList.push_back(Monster(windowCenter, positionVector[newCorridor], newCorridor));
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

							monsterListIt = monsterList.erase(monsterListIt);
							bulletCollisionListIt = bulletList.erase(bulletCollisionListIt);

							int newCorridor = rand() % positionVector.size();
							monsterList.push_back(Monster(windowCenter, positionVector[newCorridor], newCorridor));

							bulletCollisionListIt = bulletList.end();
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
				if (bulletListIt->ProcessBullet(windowCenter))
					bulletListIt = bulletList.erase(bulletListIt);
				else
				{
					bulletListIt->DisplayBullet(window);
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

		}
		break;
		case GameOver:
		{
			for (Monster& monster : monsterList)
				monster.DrawSprite(window);
			for (BulletBehaviour& bullet : bulletList)
				bullet.DisplayBullet(window);
			player.DrawSprite(window);

			//Display Score
		}
		break;
		case LevelTransition:
		{
			DrawLevel(window, map, windowCenter, 5 * transitionTime, 30 * transitionTime, effect.RandomColor());

		}
		break;

		}


		window.display();
	}
}

void changeLevel(sf::ConvexShape map, std::vector<sf::Vector3f> positionList) {

}

/*
Main Menu - F

Game :
	Effect : - F
		when dead 
		when kill monster
	Types of ennemies :
		2 hit
		3 hit + Fire back
	UI :
		Score - F

Game Over - F
	Logic -> goto Main Menu
	Display Score
	Animation

LevelTransition :
	Change Level - V

Sound :
	Player shoot
	Player Hit
	Monster Hit
	Transition
Music :
	Title screen
	Game
	GameOver
*/