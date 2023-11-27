#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#pragma once <main.cpp>

int main() {
	sf::ConvexShape triangle;

    triangle.setPointCount(3);

    //int center = *
    int px = 300;
    int py = 500;

    triangle.setFillColor(sf::Color::Blue);
    triangle.setOrigin(px, py);
    triangle.setPoint(0, sf::Vector2f(px, py));
    triangle.setPoint(1, sf::Vector2f(px + 50, py + 30));
    triangle.setPoint(2, sf::Vector2f(px + 60, py - 20));


}