#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

enum class levelShape {
	triangle,
	square,
	pentagon
};

void DrawLevel(sf::RenderWindow& window, sf::ConvexShape shape, sf::Vector2f Position, float minScale, float maxScale,int playerPos, sf::Color color = sf::Color::Blue, sf::Color playerColor = sf::Color::Yellow);
void AddLevel(levelShape& level);
void changeLevel(sf::ConvexShape& map, std::vector<sf::Vector3f>& positionList, levelShape currentShape);