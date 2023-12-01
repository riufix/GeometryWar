#pragma once
#include "SFML/Graphics.hpp"

enum class levelShape {
	triangle,
	square,
	pentagon
};

void DrawLevel(sf::RenderWindow& window, sf::ConvexShape shape, sf::Vector2f Position, float minScale, float maxScale, sf::Color color = sf::Color::Blue);
void AddLevel(levelShape& level);
void changeLevel(sf::ConvexShape& map, std::vector<sf::Vector3f>& positionList, levelShape currentShape);