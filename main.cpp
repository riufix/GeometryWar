#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <list>

#include "Player.h"
#include "BulletBehaviour.h"
#include "map.h"
#include "Monster.h"

constexpr enum levelShape {
	triangle,
	square,
	pantagone
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
	
	//Init Player
	Player player;
	player.InitializeGraphic();
	float convexRotate = 0;
	
	//Init Bullet List
	std::list<BulletBehaviour> bulletList;

	//Init Map
	sf::ConvexShape map = InitializeTriangle();
	map = InitializePantagone();
	map = InitializeSquare();

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
	sf::Vector3f PantagonePositionList[8] = {
	{0,0,0},
	{0,0,0},
	{0,0,0},
	{0,0,0},
	{0,0,0},
	{0,0,0},
	{0,0,0},
	{0,0,0}
	};

	std::vector<sf::Vector3f> positionVector;
	levelShape currentlevel = square;

	switch (currentlevel)
	{
	case triangle:
		for (int i = 0; i < 9; i++) {
			positionVector.push_back(TrianglePositionList[i]);
		}
		break;

	case square:
		for (int i = 0; i < 8; i++) {
			positionVector.push_back(SquarePositionList[i]);
		}
		break;

	case pantagone:
		for (int i = 0; i < 8; i++) {
			positionVector.push_back(PantagonePositionList[i]);
		}
		break;

	default:
		break;
	}


	//Init Ennemy List
	std::list<Monster> monsterList;
	int newCorridor = rand() % positionVector.size();
	monsterList.push_back(Monster(windowCenter, positionVector[newCorridor], newCorridor));

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

		//Process Player Input
		if (player.ProcessFireInput(deltaTime))
		{
			bulletList.push_back(BulletBehaviour(BulletBehaviour::Owner::Player, 100, player.positionIndex, player.shape.getPosition()));
		}
		player.ProcessMoveInput(positionVector.size(), deltaTime);
		//Update playerPosition
		player.UpdateSprite(positionVector[player.positionIndex].x,
							positionVector[player.positionIndex].y,
							positionVector[player.positionIndex].z);

		/* --------------
			DISPLAY
		-------------- */
		window.clear();

		//Display level
		DrawLevel(window, map, windowCenter, 5, 30);

		//Display & manage Ennemies
		std::list<Monster>::iterator monsterListIt = monsterList.begin();
		while (monsterListIt != monsterList.end())
		{
			bool skipToNext = false; //skip if collision
			if (monsterListIt->ProcessMonster(deltaTime))
			{
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

						monsterListIt = monsterList.erase(monsterListIt);
						bulletCollisionListIt = bulletList.erase(bulletCollisionListIt);

						int newCorridor = rand() % positionVector.size();
						monsterList.push_back(Monster(windowCenter, positionVector[newCorridor], newCorridor));

						bulletCollisionListIt = bulletList.end();
					}
					else
					{
						bulletCollisionListIt++;
					}
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
			{
				bulletListIt = bulletList.erase(bulletListIt);
			}
			else 
			{
				bulletListIt->DisplayBullet(window);
				bulletListIt++;
			}
		}

		//Display player
		player.DrawSprite(window);

		window.display();
	}
}
