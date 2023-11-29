#include "Player.h"
#include <iostream>

void Player::InitializeGraphic(sf::Vector2f origin)
{
	shape.setPointCount(6);
	shape.setFillColor(sf::Color::Yellow);
	
	int px = origin.x;
	int py = origin.y;

	shape.setPoint(0, sf::Vector2f(0, 0));
	shape.setPoint(1, sf::Vector2f(0 + 50, 0 + 30));
	shape.setPoint(2, sf::Vector2f(0 + 60, 0 - 20));
	shape.setPoint(3, sf::Vector2f(0, 0 - 60));
	shape.setPoint(4, sf::Vector2f(0 - 60, 0 - 20));
	shape.setPoint(5, sf::Vector2f(0 - 50, 0 + 30));
	shape.setOrigin(0, 0);
	
	shape.setPosition(px,py);
}

void Player::ProcessMoveInput(int maxPosition, float deltaTime)
{
	if (currentMoveRate <= 0)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			positionIndex = positionIndex - 1;
			if (positionIndex < 0) positionIndex = maxPosition - 1;
			currentMoveRate = .3f;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			positionIndex = positionIndex + 1;
			if (positionIndex >= maxPosition) positionIndex = 0;
			currentMoveRate = .3f;
		};
	}
	if (currentMoveRate > 0) currentMoveRate = currentMoveRate - deltaTime;
}

bool Player::ProcessFireInput(float deltaTime)
{	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && currentFireRate <= 0) 
	{
		currentFireRate = fireRate;
		return true;
	}
	if (currentFireRate > 0) currentFireRate = currentFireRate - deltaTime;

	return false;
}

void Player::UpdateSprite(float px, float py, float angle)
{
	shape.setPosition(px, py);

	float bodyOffset = std::sin(angle / 10);
	shape.setPoint(2, sf::Vector2f(bodyOffset * 10 + 60, -20));
	shape.setPoint(3, sf::Vector2f(bodyOffset * 20, -60));
	shape.setPoint(4, sf::Vector2f(bodyOffset * 10 - 60, -20));

	shape.setRotation(angle);
}

void Player::DrawSprite(sf::RenderWindow& window) 
{
	window.draw(shape);
}