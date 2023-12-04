#pragma once

#include <SFML/Graphics.hpp>
#include "Lerp.h"
#include <math.h>
#include <list>

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
	void DisplayBullet(sf::RenderWindow& window, float deltaTime);
	bool CheckPlayerCollision(int playerIndex);
	bool CheckOtherBulletCollision(std::list<BulletBehaviour>& bulletList, std::list<BulletBehaviour>::iterator& currentBullet);

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

