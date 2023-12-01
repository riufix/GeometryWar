#pragma once
#include "SFML/Graphics.hpp"

constexpr enum class levelShape {
	triangle,
	square,
	pantagone
};

sf::ConvexShape InitializeTriangle();

void DrawLevel(sf::RenderWindow& window, sf::ConvexShape shape, sf::Vector2f Position, float minScale, float maxScale, sf::Color color = sf::Color::Blue);
sf::ConvexShape InitializeSquare();
sf::ConvexShape InitializePantagone();

void AddLevel(levelShape& level);
void changeLevel(sf::ConvexShape& map, std::vector<sf::Vector3f>& positionList, levelShape currentShape);