#pragma once

#include <SFML/Graphics.hpp>

class Player
{
public :
	sf::ConvexShape shape;

	void InitializeGraphic(sf::ConvexShape& convex, sf::Vector2f origin);
	void DisplaySprite(sf::ConvexShape& convex, float px, float py, float angle);
};

