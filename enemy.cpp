#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

void drawEnemy(sf::RenderWindow& window, sf::Vector2f position, sf::Color color) {
    // create an empty shape
    sf::ConvexShape enemy1;

    // resize it to 5 points
    enemy1.setPointCount(7);

    // define the points

    int px = window.getSize().x / 2;
    int py = window.getSize().y / 2;

    enemy1.setFillColor(sf::Color::Blue);
    enemy1.setOrigin(px, py);
    enemy1.setPoint(0, sf::Vector2f(px, py));
    enemy1.setPoint(1, sf::Vector2f(px + 60, py - 10));
    enemy1.setPoint(2, sf::Vector2f(px + 20, py + 10));
    enemy1.setPoint(3, sf::Vector2f(px + 60, py + 30));
    enemy1.setPoint(4, sf::Vector2f(px - 60, py + 30));
    enemy1.setPoint(5, sf::Vector2f(px - 20, py + 10));
    enemy1.setPoint(6, sf::Vector2f(px - 60, py - 10));

    enemy1.setPosition(px, py);

    window.draw(enemy1);
}