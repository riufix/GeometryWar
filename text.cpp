#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <list>

enum textOrigin {
	center,
	left,
	right
};

sf::ConvexShape defineCharacter(char letter) {
	sf::ConvexShape shape;
	shape.setOrigin(0, 0);
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineThickness(0.5f);
	shape.setOutlineColor(sf::Color::White);

	//Schema de création des lettres
	//(-2,-3) | ( 0,-3) | ( 2,-3)
	//(-2,-1) | ( 0,-1) | ( 2,-1)
	//(-2, 1) | ( 0, 1) | ( 2, 1)
	//(-2, 3) | ( 0, 3) | ( 2, 3)

	switch (letter)
	{
	case '0':
		shape.setPointCount(4);
		shape.setPoint(0, sf::Vector2f(-2, 3));
		shape.setPoint(1, sf::Vector2f(-2, -3));
		shape.setPoint(2, sf::Vector2f(2, -3));
		shape.setPoint(3, sf::Vector2f(2, 3));
		break;
	case '1':
		shape.setPointCount(4);
		shape.setPoint(0, sf::Vector2f(0, 3));
		shape.setPoint(1, sf::Vector2f(0, -3));
		shape.setPoint(2, sf::Vector2f(-2, -1));
		shape.setPoint(3, sf::Vector2f(0, -3));
		break;
	case '2':
		shape.setPointCount(10);
		shape.setPoint(0, sf::Vector2f(2, 3));
		shape.setPoint(1, sf::Vector2f(-2, 3));
		shape.setPoint(2, sf::Vector2f(-2, 1));
		shape.setPoint(3, sf::Vector2f(2, -1));
		shape.setPoint(4, sf::Vector2f(2, -3));
		shape.setPoint(5, sf::Vector2f(-2, -3));
		shape.setPoint(6, sf::Vector2f(2, -3));
		shape.setPoint(7, sf::Vector2f(2, -1));
		shape.setPoint(8, sf::Vector2f(-2, 1));
		shape.setPoint(9, sf::Vector2f(-2, 3));
		break;
	case '3':
		shape.setPointCount(9);
		shape.setPoint(0, sf::Vector2f(-2, 3));
		shape.setPoint(1, sf::Vector2f(2, 3));
		shape.setPoint(2, sf::Vector2f(2, 0));
		shape.setPoint(3, sf::Vector2f(0, 0));
		shape.setPoint(4, sf::Vector2f(2, 0));
		shape.setPoint(5, sf::Vector2f(2, -3));
		shape.setPoint(6, sf::Vector2f(-2, -3));
		shape.setPoint(7, sf::Vector2f(2, -3));
		shape.setPoint(8, sf::Vector2f(2, 3));
		break;
	case '4':
		shape.setPointCount(7);
		shape.setPoint(0, sf::Vector2f(2, 3));
		shape.setPoint(1, sf::Vector2f(2, -3));
		shape.setPoint(2, sf::Vector2f(2, 1));
		shape.setPoint(3, sf::Vector2f(-2, 1));
		shape.setPoint(4, sf::Vector2f(-2, -3));
		shape.setPoint(5, sf::Vector2f(-2, 1));
		shape.setPoint(6, sf::Vector2f(2, 1));
		break;
	case '5':
		shape.setPointCount(10);
		shape.setPoint(0, sf::Vector2f(-2, 3));
		shape.setPoint(1, sf::Vector2f(2, 3));
		shape.setPoint(2, sf::Vector2f(2, 1));
		shape.setPoint(3, sf::Vector2f(-2, -1));
		shape.setPoint(4, sf::Vector2f(-2, -3));
		shape.setPoint(5, sf::Vector2f(2, -3));
		shape.setPoint(6, sf::Vector2f(-2, -3));
		shape.setPoint(7, sf::Vector2f(-2, -1));
		shape.setPoint(8, sf::Vector2f(2, 1));
		shape.setPoint(9, sf::Vector2f(2, 3));
		break;

	case 'A': case 'a':
		shape.setPointCount(7);
		shape.setPoint(0, sf::Vector2f(-2, 3));
		shape.setPoint(1, sf::Vector2f(-2, -1));
		shape.setPoint(2, sf::Vector2f(0, -3));
		shape.setPoint(3, sf::Vector2f(2, -1));
		shape.setPoint(4, sf::Vector2f(2, 3));
		shape.setPoint(5, sf::Vector2f(2, 1));
		shape.setPoint(6, sf::Vector2f(-2, 1));
		break;
	case 'B': case 'b':
		shape.setPointCount(9);
		shape.setPoint(0, sf::Vector2f(-2, 3));
		shape.setPoint(1, sf::Vector2f(-2, -3));
		shape.setPoint(2, sf::Vector2f(0, -3));
		shape.setPoint(3, sf::Vector2f(2, -1));
		shape.setPoint(4, sf::Vector2f(0, 0));
		shape.setPoint(5, sf::Vector2f(-2, 0));
		shape.setPoint(6, sf::Vector2f(0, 0));
		shape.setPoint(7, sf::Vector2f(2, 1));
		shape.setPoint(8, sf::Vector2f(0, 3));
		break;
	case 'C': case 'c':
		shape.setPointCount(6);
		shape.setPoint(0, sf::Vector2f(2, 3));
		shape.setPoint(1, sf::Vector2f(-2, 3));
		shape.setPoint(2, sf::Vector2f(-2, -3));
		shape.setPoint(3, sf::Vector2f(2, -3));
		shape.setPoint(4, sf::Vector2f(-2, -3));
		shape.setPoint(5, sf::Vector2f(-2, 3));
		break;
	case 'D': case 'd':
		shape.setPointCount(6);
		shape.setPoint(0, sf::Vector2f(-2, 3));
		shape.setPoint(1, sf::Vector2f(-2, -3));
		shape.setPoint(2, sf::Vector2f(0, -3));
		shape.setPoint(3, sf::Vector2f(2, -1));
		shape.setPoint(4, sf::Vector2f(2, 1));
		shape.setPoint(5, sf::Vector2f(0, 3));
		break;


	default:
		break;
	}

	return shape;
}

std::vector<sf::ConvexShape> stringToDisplayable(std::string text) {
	int size = text.length();
	std::vector<sf::ConvexShape> displayText(size);

	for (int i = 0; i < size; i++) {
		displayText[i] = defineCharacter(text[i]);
	}

	return displayText;
}

void DisplayText(sf::RenderWindow& window, std::vector<sf::ConvexShape> textVector, sf::Vector2f position, float scale, textOrigin origin = center) {
	int size = textVector.size();
	float offset;

	if (origin == center) {
		offset = ((size - 1) * 4 * scale + (size - 1) * 1 * scale) / 2;
	}
	else if (origin == right) {
		offset = ((size - 1) * 4 * scale + (size - 1) * 1 * scale);
	}
	else if (origin == left) {
		offset = 0;
	}

	position.x -= offset;
	for (int i = 0; i < size; i++) {
		textVector[i].setScale(scale, scale);
		textVector[i].setPosition(position);
		window.draw(textVector[i]);

		position.x += 5*scale + 1*scale;
	}
}