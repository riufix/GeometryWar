#pragma once
#include "SFML/Graphics.hpp"

class Monster
{

public:
	sf::ConvexShape shape;
	int positionIndex = 0;

	void InitializeGraphic();
};

