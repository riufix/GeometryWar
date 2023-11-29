#include "BulletBehaviour.h"
#include <iostream>

//Prototype
sf::Vector2f Vector2Lerp(sf::Vector2f a, sf::Vector2f b, float t);

BulletBehaviour::BulletBehaviour(Owner newOwner, int newProgression, sf::Vector2f newSpawnPosition)
{
	currentOwner = newOwner;
	progression = newProgression;
	spawnPosition = newSpawnPosition;

	switch (currentOwner)
	{
	case BulletBehaviour::Owner::Player:
		direction = BulletBehaviour::Direction::Fond;
		shape.setOutlineColor(sf::Color::Yellow);
		break;
	case BulletBehaviour::Owner::Ennemy:
		direction = BulletBehaviour::Direction::Bord;
		shape.setOutlineColor(sf::Color::Red);
		break;
	default :
		direction = BulletBehaviour::Direction::Bord;
		break;
	}

	//Init shape
	shape.setRadius(10);
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineThickness(3);
	shape.setOrigin(shape.getRadius(), shape.getRadius());
	shape.setPosition(newSpawnPosition.x - shape.getRadius(), newSpawnPosition.y - shape.getRadius());
}

bool BulletBehaviour::ProcessBullet(sf::Vector2f origin)
{
	progression = progression + (int)direction;

	float newScale = fullScale * ((float)progression / 100.0f);
	shape.setScale(newScale, newScale);
	
	sf::Vector2f newPosition = Vector2Lerp(origin, spawnPosition, ((float)progression / 100.0f));
	shape.setPosition(newPosition);

	return (progression < 0 || progression > 100);
}

void BulletBehaviour::DisplayBullet(sf::RenderWindow& window)
{
	window.draw(shape);
}

