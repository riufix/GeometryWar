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

sf::Vector2f Player::ProcessInput(float deltaTime)
{
	sf::Vector2f pos = shape.getPosition();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) pos.x = pos.x - deltaTime * moveSpeed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) pos.x = pos.x + deltaTime * moveSpeed;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && currentRate <= 0) 
	{
		currentRate = fireRate;
		std::cout << "FIRE" << std::endl;
	}
	if (currentRate > 0) currentRate = currentRate - deltaTime;

	return pos;
}

void Player::UpdateSprite(float px, float py, float angle)
{
	shape.setPosition(px, py);

	shape.setPoint(2, sf::Vector2f(std::sin(px / 50) * 10 + 60, -20));
	shape.setPoint(3, sf::Vector2f(std::sin(px / 50) * 20, -60));
	shape.setPoint(4, sf::Vector2f(std::sin(px / 50) * 10 - 60, -20));

	shape.setRotation(angle);
}

void Player::DrawSprite(sf::RenderWindow& window) 
{
	window.draw(shape);
}