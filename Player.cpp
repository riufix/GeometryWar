#include "Player.h"
#include <iostream>

void Player::InitializeGraphic(sf::ConvexShape& convex, sf::Vector2f origin)
{
	convex.setPointCount(6);
	convex.setFillColor(sf::Color::Yellow);
	
	int px = origin.x;
	int py = origin.y;

	convex.setPoint(0, sf::Vector2f(px, py));
	convex.setPoint(1, sf::Vector2f(px + 50, py + 30));
	convex.setPoint(2, sf::Vector2f(px + 60, py - 20));
	convex.setPoint(3, sf::Vector2f(px, py - 60));
	convex.setPoint(4, sf::Vector2f(px - 60, py - 20));
	convex.setPoint(5, sf::Vector2f(px - 50, py + 30));
	convex.setOrigin(px, py);

}

void Player::DisplaySprite(sf::ConvexShape& convex, float px, float py, float angle)
{
	convex.setPosition(px, py);
	convex.setRotation(angle);

}