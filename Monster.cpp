#include "Monster.h"

//Prototype
sf::Vector2f Vector2Lerp(sf::Vector2f a, sf::Vector2f b, float t);

Monster::Monster(sf::Vector2f start, sf::Vector3f end, int corridor, int health) {
	positionIndex = corridor;
	SpawningPosition = start;
	Health = health;
	EndingPosition = sf::Vector2f(end.x,end.y);
	
	timeStep = .015f * health;

	shape.setRotation(end.z + 180);
	InitializeGraphic();
}

void Monster::InitializeGraphic()
{
	shape.setPointCount(10);
	shape.setFillColor(sf::Color::Red);

	shape.setPoint(0, sf::Vector2f(0, 0));
	shape.setPoint(1, sf::Vector2f(10, 30));
	shape.setPoint(2, sf::Vector2f(20, 10));
	shape.setPoint(3, sf::Vector2f(30, 30));
	shape.setPoint(4, sf::Vector2f(25, -10));
	shape.setPoint(5, sf::Vector2f(0, -20));
	shape.setPoint(6, sf::Vector2f(-25, -10));
	shape.setPoint(7, sf::Vector2f(-30, 30));
	shape.setPoint(8, sf::Vector2f(-20, 10));
	shape.setPoint(9, sf::Vector2f(-10, 30));
	shape.setOrigin(0, 30);
}

void Monster::DrawSprite(sf::RenderWindow& window)
{
	sf::Color fillColor = sf::Color(255,0,127 * (Health - 1));
	shape.setFillColor(fillColor);
	window.draw(shape);
}

bool Monster::ProcessMonster(float deltaTime, std::list<BulletBehaviour>& bulletList)
{
	//Movement
	if (currentStep > 0)
	{
		currentStep = currentStep - deltaTime;
		return false;
	}
	progression = progression + 1;
	currentStep = timeStep;

	float newScale = maxScale * ((float)progression / 100.0f);
	shape.setScale(newScale, newScale);

	sf::Vector2f newPosition = Vector2Lerp(SpawningPosition, EndingPosition, ((float)progression / 100.0f));
	shape.setPosition(newPosition);

	shape.rotate(cos(progression / 10) * 2);

	//Shoot (if has 3HP)
	if (Health >= 3)
	{
		bulletTimer -= deltaTime;
		if (bulletTimer <= 0)
		{
			bulletList.push_back(BulletBehaviour(BulletBehaviour::Owner::Ennemy, progression, positionIndex, EndingPosition));
			bulletTimer = timeBetweenBullet;
		}
	}

	return (progression < 0 || progression > 100);
}

void Monster::UpdateSprite(float px, float py, float angle)
{
	shape.setPosition(px, py);
	shape.setRotation(angle);
}

bool Monster::ChkCollision(BulletBehaviour bullet)
{
	return ((bullet.progression == progression || bullet.progression + 1 == progression) && 
			positionIndex == bullet.positionIndex && bullet.currentOwner == BulletBehaviour::Owner::Player);
}