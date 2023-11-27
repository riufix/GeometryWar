#pragma once

#include <SFML/Graphics.hpp>

class Player
{
private:
	sf::ConvexShape shape;
	float moveSpeed = 500;

public:
	void InitializeGraphic(sf::Vector2f origin);
	sf::Vector2f ProcessInput(float deltaTime);
	void UpdateSprite(float px, float py, float angle);
	void DrawSprite(sf::RenderWindow& window);
};

