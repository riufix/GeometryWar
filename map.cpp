#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "map.h"

sf::ConvexShape InitializeTriangle()
{
    sf::ConvexShape triangle;

    triangle.setPointCount(9);

    triangle.setOutlineColor(sf::Color::Blue);
    triangle.setOutlineThickness(.75f);
    triangle.setFillColor(sf::Color::Transparent);
    triangle.setOrigin(0, 0);

    triangle.setPoint(0, sf::Vector2f(-15,10));
    triangle.setPoint(1, sf::Vector2f(-10, 3.33333333333333f));
    triangle.setPoint(2, sf::Vector2f(-5, -3.333333333333f));
    
    triangle.setPoint(3, sf::Vector2f(0, -10));
    triangle.setPoint(4, sf::Vector2f(5, -3.333333333333f));
    triangle.setPoint(5, sf::Vector2f(10, 3.33333333333333f));

    triangle.setPoint(6, sf::Vector2f(15, 10));
    triangle.setPoint(7, sf::Vector2f(5, 10));
    triangle.setPoint(8, sf::Vector2f(-5, 10));

    return triangle;
}

sf::ConvexShape InitializeSquare() {
    sf::ConvexShape square;

    square.setPointCount(8);

    square.setOutlineColor(sf::Color::Blue);
    square.setFillColor(sf::Color::Transparent);
    square.setOutlineThickness(.75f);
    square.setOrigin(0, 0);

    square.setPoint(0, sf::Vector2f(-10,-10));
    square.setPoint(2, sf::Vector2f(+10,-10));
    square.setPoint(4, sf::Vector2f(+10,+10));
    square.setPoint(6, sf::Vector2f(-10,+10));
    
    square.setPoint(1, sf::Vector2f(0,-10));
    square.setPoint(3, sf::Vector2f(+10,0));
    square.setPoint(5, sf::Vector2f(0,+10));
    square.setPoint(7, sf::Vector2f(-10,0));
    
    return square;
}

sf::ConvexShape InitializePantagone() {
    sf::ConvexShape pantagone;

    pantagone.setPointCount(8);

    pantagone.setOutlineColor(sf::Color::Blue);
    pantagone.setFillColor(sf::Color::Transparent);
    pantagone.setOutlineThickness(.75f);
    pantagone.setOrigin(0, 0);

    pantagone.setPoint(0, sf::Vector2f(-10, -10));
    pantagone.setPoint(1, sf::Vector2f(+10, -10));
    pantagone.setPoint(2, sf::Vector2f(-10, -10));
    pantagone.setPoint(3, sf::Vector2f(-10, -10));
    pantagone.setPoint(4, sf::Vector2f(-10, -10));
    pantagone.setPoint(5, sf::Vector2f(-10, -10));
    pantagone.setPoint(6, sf::Vector2f(-10, -10));
    pantagone.setPoint(7, sf::Vector2f(-10, -10));

    return pantagone;
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

