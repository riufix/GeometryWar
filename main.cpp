#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <list>

#include "Player.h"
#include "BulletBehaviour.h"
#include "map.h"

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
	windowCenter.x = window.getSize().x / 2.0;
	windowCenter.y = window.getSize().y / 2.0;
	
	//Init Player
	Player player;
	player.InitializeGraphic(sf::Vector2f(200,200));
	float convexRotate = 0;
	
	//Init Bullet List
	std::list<BulletBehaviour> bulletList;

	//Init Map
	sf::ConvexShape map = InitializeTriangle();

	//Init position list
	sf::Vector3f TrianglePositionList[9] = {
	{1090,330,55},
	{1220,500, 60},
	{1360,700,55},
	{1250,890,180},
	{960,890,180},
	{690,890,180},
	{560,700,-50},
	{690,510,-55},
	{830,330,-55}
	};
	std::vector<sf::Vector3f> positionVector;
	for (int i = 0; i < 9; i++) {
		positionVector.push_back(TrianglePositionList[i]);
	}
	int positionVectorSize = 9;

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

			bulletList.push_back(BulletBehaviour(BulletBehaviour::Owner::Player, 100, player.shape.getPosition()));
		}
		player.ProcessMoveInput(positionVectorSize, deltaTime);
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

		//Display ennemies

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
