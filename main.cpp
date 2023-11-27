#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include "Player.h"
#include "BulletBehaviour.h"

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

	BulletBehaviour newBullet(BulletBehaviour::Owner::Player, 100, player.shape.getPosition());

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

		newBullet.ProcessBullet(sf::Vector2f(0,0));
		newBullet.DisplayBullet(window);

		player.DrawSprite(window);

		window.display();
	}
}
