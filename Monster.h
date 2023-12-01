#pragma once
#include "SFML/Graphics.hpp"
#include "Lerp.h"
#include "BulletBehaviour.h"
#include <list>

class Monster
{
private :
	float maxScale = 2;
	float currentStep;
	
	float timeBetweenBullet = .2f;
	float bulletTimer = timeBetweenBullet;

public:
	sf::ConvexShape shape;
	int progression = 0;
	int positionIndex = 0;
	int Health = 1;
	float timeStep = .01f; //Time between step

	sf::Vector2f SpawningPosition;
	sf::Vector2f EndingPosition;

	Monster(sf::Vector2f start, sf::Vector3f end, int corridor, int health);

	void InitializeGraphic();
	void DrawSprite(sf::RenderWindow& window);

	bool ProcessMonster(float deltaTime, std::list<BulletBehaviour>& bulletList);
	void UpdateSprite(float px, float py, float angle);
	bool ChkCollision(BulletBehaviour bullet);
};

/*
	TODO :
- collision
*/