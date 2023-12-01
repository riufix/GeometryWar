#pragma once
#include "SFML/Graphics.hpp"
#include "Lerp.h"
#include "BulletBehaviour.h"

class Monster
{
private :
	float maxScale = 2;
	float currentStep;

public:
	sf::ConvexShape shape;
	int progression = 0;
	int positionIndex = 0;
	float timeStep = .01f; //Time between step

	sf::Vector2f SpawningPosition;
	sf::Vector2f EndingPosition;

	Monster(sf::Vector2f start, sf::Vector3f end, int corridor);

	void InitializeGraphic();
	void DrawSprite(sf::RenderWindow& window);

	bool ProcessMonster(float deltaTime);
	void UpdateSprite(float px, float py, float angle);
	bool ChkCollision(BulletBehaviour bullet);
};

/*
	TODO :
- collision
*/