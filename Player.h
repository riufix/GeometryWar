#pragma once

#include <SFML/Graphics.hpp>

class Player
{
private:
	float currentFireRate = 0;
	float currentMoveRate = 0;
	float currentInvicibilityRate = 0;
	//Propreties
	float moveRate = .2f;
	float fireRate = .2f;
	float invicibilityRate = 2.f;

public:
	sf::ConvexShape shape;
	int positionIndex = 0;
	int Health = 3;

	void InitializeGraphic();
	void DrawSprite(sf::RenderWindow& window);

	void ProcessInvincibility(float deltaTime);
	void ProcessMoveInput(int maxPosition, float deltaTime);
	bool ProcessFireInput(float deltaTime);
	void UpdateSprite(float px, float py, float angle);

	bool isInvincible();
	bool Hit();
};