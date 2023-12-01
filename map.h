#pragma once
#include "SFML/Graphics.hpp"

sf::ConvexShape InitializeTriangle();

void DrawLevel(sf::RenderWindow& window, sf::ConvexShape shape, sf::Vector2f Position, float minScale, float maxScale, sf::Color color = sf::Color::Blue);
sf::ConvexShape InitializeSquare();
sf::ConvexShape InitializePantagone();