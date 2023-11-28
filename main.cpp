#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <list>

#include "Player.h"
#include "BulletBehaviour.h"
#include "map.h"

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Geometry Wars",sf::Style::Default, settings);
	window.setVerticalSyncEnabled(true);

	Player player;
	player.InitializeGraphic(sf::Vector2f(200,200));

	sf::Clock frameClock;

	float convexRotate = 0;
	
	std::list<BulletBehaviour> bulletList;
	BulletBehaviour newBullet(BulletBehaviour::Owner::Player, 100, player.shape.getPosition());
	bulletList.push_back(newBullet);

	sf::ConvexShape map = InitializeTriangle();
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
		convexRotate = convexRotate + 50 * deltaTime;
		sf::Vector2f playerPos = player.ProcessMoveInput(deltaTime);
		player.ProcessFireInput(deltaTime);
		player.UpdateSprite(playerPos.x, playerPos.y, convexRotate);
		

		// Affichage
		window.clear();

		sf::Vector2f centerVector;
		centerVector.x = window.getSize().x / 2.0;
		centerVector.y = window.getSize().y / 2.0;
		DrawLevel(window, map, centerVector, 5, 15);

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
