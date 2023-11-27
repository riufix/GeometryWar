#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include "Player.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Geometry Wars");
	window.setVerticalSyncEnabled(true);

	Player player;
	player.InitializeGraphic(sf::Vector2f(200,200));

	sf::Clock frameClock;

	float convexRotate = 0;
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
		sf::Vector2f playerPos = player.ProcessInput(deltaTime);
		player.UpdateSprite(playerPos.x, playerPos.y, convexRotate);

		// Affichage
		window.clear();

		player.DrawSprite(window);

		window.display();
	}
}
