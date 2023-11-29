#pragma once
#include "SFML/Graphics.hpp"
#include "Lerp.h"
#include "BulletBehaviour.h"

class Monster
{
private :
	int progression = 0;
	float maxScale = 2;

public:
	sf::ConvexShape shape;
	int positionIndex = 0;
	int Health = 1;

	sf::Vector2f SpawningPosition;
	sf::Vector2f EndingPosition;

	Monster(sf::Vector2f start, sf::Vector3f end, int corridor);

	void InitializeGraphic();
	void DrawSprite(sf::RenderWindow& window);

	bool ProcessMonster();
	void UpdateSprite(float px, float py, float angle);
	bool ChkCollision(BulletBehaviour bullet);
};

/*
	TODO :
- collision
*/