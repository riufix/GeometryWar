#include "BulletBehaviour.h"
#include <iostream>

BulletBehaviour::BulletBehaviour(Owner newOwner, int newProgression, sf::Vector2f spawnPosition)
{
	currentOwner = newOwner;
	progression = newProgression;

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
	shape.setPosition(spawnPosition.x - shape.getRadius(), spawnPosition.y - shape.getRadius());
}

bool BulletBehaviour::ProcessBullet(sf::Vector2f origin)
{
	std::cout << progression << std::endl;
	progression = progression + (int)direction;

	float newScale = fullScale * ((float)progression / 100.0f);
	shape.setScale(newScale, newScale);

	return (progression < 0 || progression > 100);
}

void BulletBehaviour::DisplayBullet(sf::RenderWindow& window)
{
	window.draw(shape);
}

/*
public static Vector2 Lerp(Vector2 a, Vector2 b, float t)
{
    t = Mathf.Clamp01(t);
    return new Vector2(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t);
}
*/