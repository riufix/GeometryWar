#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "map.h"

sf::ConvexShape InitializeTriangle()
{
    sf::ConvexShape triangle;

    triangle.setPointCount(9);

    triangle.setOutlineColor(sf::Color::Blue);
    triangle.setOutlineThickness(.5f);
    triangle.setFillColor(sf::Color::Transparent);
    triangle.setOrigin(0, 0);

    triangle.setPoint(0, sf::Vector2f(-15,10));
    triangle.setPoint(1, sf::Vector2f(-10, 3.33333333333333));
    triangle.setPoint(2, sf::Vector2f(-5, -3.333333333333));
    
    triangle.setPoint(3, sf::Vector2f(0, -10));
    triangle.setPoint(4, sf::Vector2f(5, -3.333333333333));
    triangle.setPoint(5, sf::Vector2f(10, 3.33333333333333));

    triangle.setPoint(6, sf::Vector2f(15, 10));
    triangle.setPoint(7, sf::Vector2f(5, 10));
    triangle.setPoint(8, sf::Vector2f(-5, 10));

    return triangle;
}

void DrawLevel(sf::RenderWindow& window, sf::ConvexShape shape, sf::Vector2f Position, float minScale, float maxScale) {

    //center of the screen
    //int centerX = window.getSize().x / 2;
    //int centerY = window.getSize().y / 2;

    shape.setPosition(Position);
    
    shape.setScale(maxScale, maxScale);
    window.draw(shape);

    shape.setScale(minScale, minScale);
    window.draw(shape);

    //line point position
    for (int i = 0; i < shape.getPointCount(); i++) 
    {
        float startX = Position.x + shape.getPoint(i).x * (minScale);
        float startY = Position.y + shape.getPoint(i).y * (minScale);
        float endX = Position.x + shape.getPoint(i).x * maxScale;
        float endY = Position.y + shape.getPoint(i).y * (maxScale);



        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(startX, startY), sf::Color::Blue),
            sf::Vertex(sf::Vector2f(endX, endY), sf::Color::Blue)
        };

        window.draw(line, 2, sf::Lines);
    }
}

void InitializeSquare() {
    sf::ConvexShape square;

    square.setPointCount(4);

    int cx = window.getSize().x / 2;
    int cy = window.getSize().y / 2;

    square.setOutlineColor(sf::Color::Blue);
    square.setFillColor(sf::Color::Transparent);
    square.setOutlineThickness(1);
    square.setOrigin(0, 0);
    square.setPoint(0, sf::Vector2f(cx - 50, cy - 50));
    square.setPoint(1, sf::Vector2f(cx + 50, cy - 50));
    square.setPoint(2, sf::Vector2f(cx + 50, cy + 50));
    square.setPoint(3, sf::Vector2f(cx - 50, cy + 50));
    square.setPosition(cx, cy);
    window.draw(square);

}