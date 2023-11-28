#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "map.h"

void maps(sf::RenderWindow& window) {
	sf::ConvexShape triangle;

    triangle.setPointCount(3);

    //center of the screen
    int centerX = window.getSize().x / 2;
    int centerY = window.getSize().y / 2;


    triangle.setOutlineColor(sf::Color::Blue);
    triangle.setOutlineThickness(.5f);
    triangle.setFillColor(sf::Color::Transparent);
    triangle.setOrigin(centerX, centerY + 10);
    triangle.setPoint(0, sf::Vector2f(centerX - 15, centerY + 20));
    triangle.setPoint(1, sf::Vector2f(centerX, centerY));
    triangle.setPoint(2, sf::Vector2f(centerX + 15, centerY + 20));
    triangle.scale(20, 20);

    triangle.setPosition(centerX, centerY);
    window.draw(triangle);

    triangle.setScale(10, 10);
    window.draw(triangle);

    //line point position
    sf::Vertex Line[] = {
        sf::Vertex(sf::Vector2f(centerX, centerY - 100), sf::Color::Blue),
        sf::Vertex(sf::Vector2f(centerX, centerY - 200), sf::Color::Blue),
        sf::Vertex(sf::Vector2f(centerX - 300,centerY + 200), sf::Color::Blue),
        sf::Vertex(sf::Vector2f(centerX - 150,centerY + 100), sf::Color::Blue),
        sf::Vertex(sf::Vector2f(centerX + 300,centerY + 200), sf::Color::Blue),
        sf::Vertex(sf::Vector2f(centerX + 150,centerY + 100), sf::Color::Blue),
    };
    window.draw(Line, 6, sf::Lines);
    

}

void Square(sf::RenderWindow& window) {
    sf::ConvexShape square;

    square.setPointCount(4);

    int cx = window.getSize().x / 2;
    int cy = window.getSize().y / 2;

    square.setOutlineColor(sf::Color::Blue);
    square.setFillColor(sf::Color::Transparent);
    square.setOutlineThickness(1);
    square.setOrigin(0, 0);
    square.setPoint(0, sf::Vector2f(cx -50,cy -50));
    square.setPoint(1, sf::Vector2f(cx +50,cy -50));
    square.setPoint(2, sf::Vector2f(cx +50,cy +50));
    square.setPoint(3, sf::Vector2f(cx -50,cy +50));
    square.setPosition(cx, cy);
    window.draw(square);

}