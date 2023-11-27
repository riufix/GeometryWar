#pragma once

#include <SFML/Graphics.hpp>

class Player
{
private:
	sf::ConvexShape shape;
	float currentRate = 0;

	//Propreties
	float moveSpeed = 500;
	float fireRate = .2;

public:
	void InitializeGraphic(sf::Vector2f origin);
	void DrawSprite(sf::RenderWindow& window);

	sf::Vector2f ProcessInput(float deltaTime);
	void UpdateSprite(float px, float py, float angle);
};