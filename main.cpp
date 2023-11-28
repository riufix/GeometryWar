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
	sf::Vector2f centerVector;
	centerVector.x = window.getSize().x / 2.0;
	centerVector.y = window.getSize().y / 2.0;
	
	//Init Player
	Player player;
	player.InitializeGraphic(sf::Vector2f(200,200));
	float convexRotate = 0;
	
	//Init Bullet List
	std::list<BulletBehaviour> bulletList;
	BulletBehaviour newBullet(BulletBehaviour::Owner::Player, 100, player.shape.getPosition());
	bulletList.push_back(newBullet);

	//Init Map
	sf::ConvexShape map = InitializeTriangle();
	//Init position list
	std::vector<sf::Vector3f> positionvVector;


	while (window.isOpen())
	{
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

		float deltaTime = frameClock.restart().asSeconds();
		//std::cout << 1.f / deltaTime << " FPS" << std::endl;
		
		// Logique
		//convexRotate = convexRotate + 50 * deltaTime;
		//int playerPos = player.ProcessMoveInput(deltaTime);
		//player.UpdateSprite(playerPos.x, playerPos.y, convexRotate);

		if (player.ProcessFireInput(deltaTime))
		{

		}

		//player.UpdateSprite(1090,330,55); //0
		//player.UpdateSprite(1220,500, 60); //1
		//player.UpdateSprite(1360,700,55); //2
		//player.UpdateSprite(1250,890,180); //3
		//player.UpdateSprite(960,890,180); //4
		//player.UpdateSprite(690,890,180); //5
		//player.UpdateSprite(560,700,-50); //6
		//player.UpdateSprite(690,510,-55); //7
		//player.UpdateSprite(830,330,-55); //8

		// Affichage
		window.clear();

		DrawLevel(window, map, centerVector, 5, 30);

		//Gestion bullets
		std::list<BulletBehaviour>::iterator bulletListIt = bulletList.begin();
		while (bulletListIt != bulletList.end())
		{
			if (bulletListIt->ProcessBullet(sf::Vector2f(0, 0))) 
			{
				bulletListIt = bulletList.erase(bulletListIt);
			}
			else 
			{
				bulletListIt->DisplayBullet(window);
				bulletListIt++;
			}
		}

		player.DrawSprite(window);

		window.display();
	}
}
