#include "Player.h"
#include <iostream>

void Player::InitializeGraphic(sf::Vector2f origin)
{
	shape.setPointCount(6);
	shape.setFillColor(sf::Color::Yellow);
	
	int px = origin.x;
	int py = origin.y;

	shape.setPoint(0, sf::Vector2f(px, py));
	shape.setPoint(1, sf::Vector2f(px + 50, py + 30));
	shape.setPoint(2, sf::Vector2f(px + 60, py - 20));
	shape.setPoint(3, sf::Vector2f(px, py - 60));
	shape.setPoint(4, sf::Vector2f(px - 60, py - 20));
	shape.setPoint(5, sf::Vector2f(px - 50, py + 30));

	shape.setOrigin(px, py);
	
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
	shape.setRotation(angle);
}

void Player::DrawSprite(sf::RenderWindow& window) 
{
	window.draw(shape);
}