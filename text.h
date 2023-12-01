#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <list>
#pragma once

enum textOrigin {
	center,
	left,
	right
};

sf::ConvexShape defineCharacter(char letter);

std::vector<sf::ConvexShape> stringToDisplayable(std::string text);
void DisplayText(sf::RenderWindow& window, std::vector<sf::ConvexShape> textVector, sf::Vector2f position, float scale, textOrigin origin = center);
