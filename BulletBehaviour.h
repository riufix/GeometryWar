#pragma once

#include <SFML/Graphics.hpp>

class BulletBehaviour
{
private :
	sf::CircleShape shape;
	int progression;
	enum class Owner {
		Player,
		Ennemy
	};
	Owner currentOwner;



public :
	void ProcessBullet();
	void DisplayBullet(sf::RenderWindow& window);
};

