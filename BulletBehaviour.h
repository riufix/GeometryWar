#pragma once

#include <SFML/Graphics.hpp>
#include "Lerp.h"

class BulletBehaviour
{
public :
	int progression;
	int positionIndex;

	enum class Owner {
		Player,
		Ennemy
	};
	Owner currentOwner;

	BulletBehaviour(Owner newOwner, int newProgression, int spawningCorridor,sf::Vector2f spawnPosition);

	bool ProcessBullet(sf::Vector2f origin); // return true if need to be Destroy
	void DisplayBullet(sf::RenderWindow& window);
	bool ChkCollision(int playerIndex);

private:
	sf::CircleShape shape;
	float fullScale = 5;


	enum class Direction {
		Fond = -1,
		Bord = 1
	};
	Direction direction;

	sf::Vector2f spawnPosition;
};

