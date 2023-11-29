#pragma once
#include "SFML/Graphics.hpp"
#include "Lerp.h"

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

	Monster(sf::Vector2f start, sf::Vector3f end);

	void InitializeGraphic();
	void DrawSprite(sf::RenderWindow& window);

	bool ProcessMonster();
	void UpdateSprite(float px, float py, float angle);
};

/*
	TODO :
-Déplacement
-Spawning
-Atteint la fin
- collision
*/