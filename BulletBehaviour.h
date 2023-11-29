#pragma once

#include <SFML/Graphics.hpp>
#include "Lerp.h"

class BulletBehaviour
{
public :
	int progression;
	enum class Owner {
		Player,
		Ennemy
	};

	BulletBehaviour(Owner newOwner, int newProgression, sf::Vector2f spawnPosition);

	bool ProcessBullet(sf::Vector2f origin); // return true if need to be Destroy
	void DisplayBullet(sf::RenderWindow& window);

private:
	sf::CircleShape shape;
	float fullScale = 5;

	Owner currentOwner;

	enum class Direction {
		Fond = -1,
		Bord = 1
	};
	Direction direction;

	sf::Vector2f spawnPosition;
};

