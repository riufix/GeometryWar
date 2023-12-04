#include "BulletBehaviour.h"

//Prototype
sf::Vector2f Vector2Lerp(sf::Vector2f a, sf::Vector2f b, float t);

BulletBehaviour::BulletBehaviour(Owner newOwner, int newProgression, int spawningCorridor, sf::Vector2f newSpawnPosition)
{
	currentOwner = newOwner;
	progression = newProgression;
	positionIndex = spawningCorridor;
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
	shape.setRadius(7);
	shape.setPointCount(8);
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

	shape.rotate(1);

	return (progression < 0 || progression > 100);
}

void BulletBehaviour::DisplayBullet(sf::RenderWindow& window)
{
	window.draw(shape);
}

bool BulletBehaviour::CheckPlayerCollision(int playerIndex)
{
	return (positionIndex == playerIndex && currentOwner != Owner::Player);
}

bool BulletBehaviour::CheckOtherBulletCollision(std::list<BulletBehaviour>& bulletList, std::list<BulletBehaviour>::iterator& currentBullet)
{
	std::list<BulletBehaviour>::iterator bulletListCollisionIt = bulletList.begin();
	while (bulletListCollisionIt != bulletList.end())
	{
		if ((currentBullet->progression == bulletListCollisionIt->progression ||
			currentBullet->progression + 1 == bulletListCollisionIt->progression) && //IF two bullet have roughly the same progression
			currentBullet->positionIndex == bulletListCollisionIt->positionIndex && //AND they are on the same corridor
			currentBullet != bulletListCollisionIt && //AND they're not the same
			currentBullet->currentOwner == BulletBehaviour::Owner::Player) //AND the first projectile is from the player
		{
			currentBullet = bulletList.erase(currentBullet);
			currentBullet = bulletList.erase(bulletListCollisionIt);
			return true;
		}
		bulletListCollisionIt++;
	}

	return false;
}