#pragma once

#include <SFML/Graphics.hpp>

class Player
{
private:
	float currentRate = 0;

	//Propreties
	float moveRate = .2;
	
	float fireRate = .2;

public:
	sf::ConvexShape shape;
	void InitializeGraphic(sf::Vector2f origin);
	void DrawSprite(sf::RenderWindow& window);

	int ProcessMoveInput(float deltaTime);
	bool ProcessFireInput(float deltaTime);
	void UpdateSprite(float px, float py, float angle);
};