#pragma once

#include <SFML/Graphics.hpp>

class Player
{
private:
	float currentFireRate = 0;
	float currentMoveRate = 0;
	//Propreties
	float moveRate = .2f;
	
	float fireRate = .2f;

public:
	sf::ConvexShape shape;
	int positionIndex = 0;
	void InitializeGraphic();
	void DrawSprite(sf::RenderWindow& window);

	void ProcessMoveInput(int maxPosition, float deltaTime);
	bool ProcessFireInput(float deltaTime);
	void UpdateSprite(float px, float py, float angle);
};