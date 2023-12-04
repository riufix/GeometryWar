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

	//Letter size 6x8
	//Schematic to create letters
	//(-2,-3) | ( 0,-3) | ( 2,-3)
	//(-2,-1) | ( 0,-1) | ( 2,-1)
	//(-2, 1) | ( 0, 1) | ( 2, 1)
	//(-2, 3) | ( 0, 3) | ( 2, 3)

	switch (letter)
	{
#pragma region Numbers
	case '0':
		shape.setPointCount(4);
		shape.setPoint(0, sf::Vector2f(-2, 3));
		shape.setPoint(1, sf::Vector2f(-2, -3));
		shape.setPoint(2, sf::Vector2f(2, -3));
		shape.setPoint(3, sf::Vector2f(2, 3));
		break;
	case '1':
		shape.setPointCount(7);
		shape.setPoint(0, sf::Vector2f(0, 3));
		shape.setPoint(1, sf::Vector2f(-2, 3));
		shape.setPoint(2, sf::Vector2f(2, 3));
		shape.setPoint(3, sf::Vector2f(0, 3));
		shape.setPoint(4, sf::Vector2f(0, -3));
		shape.setPoint(5, sf::Vector2f(-2, -1));
		shape.setPoint(6, sf::Vector2f(0, -3));
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
		shape.setPoint(2, sf::Vector2f(2, 0));
		shape.setPoint(3, sf::Vector2f(-2, 0));
		shape.setPoint(4, sf::Vector2f(-2, -3));
		shape.setPoint(5, sf::Vector2f(-2, 0));
		shape.setPoint(6, sf::Vector2f(2, 0));
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
	case '6':
		shape.setPointCount(7);
		shape.setPoint(0, sf::Vector2f(-2, 3));
		shape.setPoint(1, sf::Vector2f(2, 3));
		shape.setPoint(2, sf::Vector2f(2, 1));
		shape.setPoint(3, sf::Vector2f(-2, -1));
		shape.setPoint(4, sf::Vector2f(-2, -3));
		shape.setPoint(5, sf::Vector2f(2, -3));
		shape.setPoint(6, sf::Vector2f(-2, -3));
		break;
	case '7':
		shape.setPointCount(4);
		shape.setPoint(0, sf::Vector2f(-2, 3));
		shape.setPoint(1, sf::Vector2f(2, -3));
		shape.setPoint(2, sf::Vector2f(-2, -3));
		shape.setPoint(3, sf::Vector2f(2, -3));
		break;
	case '8':
		shape.setPointCount(8);
		shape.setPoint(0, sf::Vector2f(-2, 3));
		shape.setPoint(1, sf::Vector2f(2, 3));
		shape.setPoint(2, sf::Vector2f(2, 0));
		shape.setPoint(3, sf::Vector2f(-2, 0));
		shape.setPoint(4, sf::Vector2f(-2, -3));
		shape.setPoint(5, sf::Vector2f(2, -3));
		shape.setPoint(6, sf::Vector2f(2, 0));
		shape.setPoint(7, sf::Vector2f(-2, 0));
		break;
	case '9':
		shape.setPointCount(7);
		shape.setPoint(0, sf::Vector2f(2, -3));
		shape.setPoint(1, sf::Vector2f(-2, -3));
		shape.setPoint(2, sf::Vector2f(-2, -1));
		shape.setPoint(3, sf::Vector2f(2, 1));
		shape.setPoint(4, sf::Vector2f(2, 3));
		shape.setPoint(5, sf::Vector2f(-2, 3));
		shape.setPoint(6, sf::Vector2f(2, 3));
		break;
#pragma endregion

#pragma region Letters
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
	case 'E': case 'e':
		shape.setPointCount(9);
		shape.setPoint(0, sf::Vector2f(2, 3));
		shape.setPoint(1, sf::Vector2f(-2, 3));
		shape.setPoint(2, sf::Vector2f(-2, 0));
		shape.setPoint(3, sf::Vector2f(2, 0));
		shape.setPoint(4, sf::Vector2f(-2, 0));
		shape.setPoint(5, sf::Vector2f(-2, -3));
		shape.setPoint(6, sf::Vector2f(2, -3));
		shape.setPoint(7, sf::Vector2f(-2, -3));
		shape.setPoint(8, sf::Vector2f(-2, 3));
		break;
	case 'F': case 'f':
		shape.setPointCount(7);
		shape.setPoint(0, sf::Vector2f(-2, 3));
		shape.setPoint(1, sf::Vector2f(-2, 0));
		shape.setPoint(2, sf::Vector2f(0, 0));
		shape.setPoint(3, sf::Vector2f(-2, 0));
		shape.setPoint(4, sf::Vector2f(-2, -3));
		shape.setPoint(5, sf::Vector2f(2, -3));
		shape.setPoint(6, sf::Vector2f(-2, -3));
		break;
	case 'G': case 'g':
		shape.setPointCount(10);
		shape.setPoint(0, sf::Vector2f(2, -3));
		shape.setPoint(1, sf::Vector2f(-2, -3));
		shape.setPoint(2, sf::Vector2f(-2, 3));
		shape.setPoint(3, sf::Vector2f(2, 3));
		shape.setPoint(4, sf::Vector2f(2, 1));
		shape.setPoint(5, sf::Vector2f(0, 1));
		shape.setPoint(6, sf::Vector2f(2, 1));
		shape.setPoint(7, sf::Vector2f(2, 3));
		shape.setPoint(8, sf::Vector2f(-2, 3));
		shape.setPoint(9, sf::Vector2f(-2, -3));
		break;
	case 'H': case 'h':
		shape.setPointCount(8);
		shape.setPoint(0, sf::Vector2f(-2, -3));
		shape.setPoint(1, sf::Vector2f(-2, 3));
		shape.setPoint(2, sf::Vector2f(-2, 0));
		shape.setPoint(3, sf::Vector2f(2, 0));
		shape.setPoint(4, sf::Vector2f(2, -3));
		shape.setPoint(5, sf::Vector2f(2, 3));
		shape.setPoint(6, sf::Vector2f(2, 0));
		shape.setPoint(7, sf::Vector2f(-2, 0));
		break;
	case 'I': case 'i':
		shape.setPointCount(8);
		shape.setPoint(0, sf::Vector2f(0, 3));
		shape.setPoint(1, sf::Vector2f(-2, 3));
		shape.setPoint(2, sf::Vector2f(2, 3));
		shape.setPoint(3, sf::Vector2f(0, 3));
		shape.setPoint(4, sf::Vector2f(0, -3));
		shape.setPoint(5, sf::Vector2f(-2, -3));
		shape.setPoint(6, sf::Vector2f(2, -3));
		shape.setPoint(7, sf::Vector2f(0, -3));
		break;
	case 'J': case 'j':
		shape.setPointCount(8);
		shape.setPoint(0, sf::Vector2f(2, -3));
		shape.setPoint(1, sf::Vector2f(0, -3));
		shape.setPoint(2, sf::Vector2f(2, -3));
		shape.setPoint(3, sf::Vector2f(2, 1));
		shape.setPoint(4, sf::Vector2f(0, 3));
		shape.setPoint(5, sf::Vector2f(-2, 1));
		shape.setPoint(6, sf::Vector2f(0, 3));
		shape.setPoint(7, sf::Vector2f(2, 1));
		break;
	case 'K': case 'k':
		shape.setPointCount(7);
		shape.setPoint(0, sf::Vector2f(-2, -3));
		shape.setPoint(1, sf::Vector2f(-2, 3));
		shape.setPoint(2, sf::Vector2f(-2, 0));
		shape.setPoint(3, sf::Vector2f(2, -3));
		shape.setPoint(4, sf::Vector2f(-2, 0));
		shape.setPoint(5, sf::Vector2f(2, 3));
		shape.setPoint(6, sf::Vector2f(-2, 0));
		break;
	case 'L': case 'l':
		shape.setPointCount(4);
		shape.setPoint(0, sf::Vector2f(-2, -3));
		shape.setPoint(1, sf::Vector2f(-2, 3));
		shape.setPoint(2, sf::Vector2f(2, 3));
		shape.setPoint(3, sf::Vector2f(-2, 3));
		break;
	case'M': case 'm':
		shape.setPointCount(8);
		shape.setPoint(0, sf::Vector2f(-2, 3));
		shape.setPoint(1, sf::Vector2f(-2, -3));
		shape.setPoint(2, sf::Vector2f(0, 1));
		shape.setPoint(3, sf::Vector2f(2, -3));
		shape.setPoint(4, sf::Vector2f(2, 3));
		shape.setPoint(5, sf::Vector2f(2, -3));
		shape.setPoint(6, sf::Vector2f(0, 1));
		shape.setPoint(7, sf::Vector2f(-2, -3));
		break;
	case 'N': case 'n':
		shape.setPointCount(6);
		shape.setPoint(0, sf::Vector2f(-2, 3));
		shape.setPoint(1, sf::Vector2f(-2, -3));
		shape.setPoint(2, sf::Vector2f(2, 3));
		shape.setPoint(3, sf::Vector2f(2, -3));
		shape.setPoint(4, sf::Vector2f(2, 3));
		shape.setPoint(5, sf::Vector2f(-2, -3));
		break;
	case 'O': case 'o':
		shape.setPointCount(4);
		shape.setPoint(0, sf::Vector2f(-2, 3));
		shape.setPoint(1, sf::Vector2f(-2, -3));
		shape.setPoint(2, sf::Vector2f(2, -3));
		shape.setPoint(3, sf::Vector2f(2, 3));
		break;
	case 'P': case 'p':
		shape.setPointCount(5);
		shape.setPoint(0, sf::Vector2f(-2, 3));
		shape.setPoint(1, sf::Vector2f(-2, -3));
		shape.setPoint(2, sf::Vector2f(2, -3));
		shape.setPoint(3, sf::Vector2f(2, 0));
		shape.setPoint(4, sf::Vector2f(-2, 0));
		break;
	case 'Q': case 'q':
		shape.setPointCount(7);
		shape.setPoint(0, sf::Vector2f(2, 1));
		shape.setPoint(1, sf::Vector2f(2, -3));
		shape.setPoint(2, sf::Vector2f(-2, -3));
		shape.setPoint(3, sf::Vector2f(-2, 1));
		shape.setPoint(4, sf::Vector2f(0, 1));
		shape.setPoint(5, sf::Vector2f(2, 3));
		shape.setPoint(6, sf::Vector2f(0, 1));
		break;
	case 'R': case 'r':
		shape.setPointCount(7);
		shape.setPoint(0, sf::Vector2f(-2, 3));
		shape.setPoint(1, sf::Vector2f(-2, -3));
		shape.setPoint(2, sf::Vector2f(2, -3));
		shape.setPoint(3, sf::Vector2f(2, 0));
		shape.setPoint(4, sf::Vector2f(-2, 0));
		shape.setPoint(5, sf::Vector2f(2, 3));
		shape.setPoint(6, sf::Vector2f(-2, 0));
		break;
	case 'S': case 's':
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
	case 'T': case 't':
		shape.setPointCount(5);
		shape.setPoint(0, sf::Vector2f(0, 3));
		shape.setPoint(1, sf::Vector2f(0, -3));
		shape.setPoint(2, sf::Vector2f(2, -3));
		shape.setPoint(3, sf::Vector2f(-2, -3));
		shape.setPoint(4, sf::Vector2f(0.01, -3));
		break;
	case 'U': case 'u':
		shape.setPointCount(6);
		shape.setPoint(0, sf::Vector2f(-2, -3));
		shape.setPoint(1, sf::Vector2f(-2, 3));
		shape.setPoint(2, sf::Vector2f(2, 3));
		shape.setPoint(3, sf::Vector2f(2, -3));
		shape.setPoint(4, sf::Vector2f(2, 3));
		shape.setPoint(5, sf::Vector2f(-2, 3));
		break;
	case 'V': case 'v':
		shape.setPointCount(4);
		shape.setPoint(0, sf::Vector2f(-2, -3));
		shape.setPoint(1, sf::Vector2f(0, 3));
		shape.setPoint(2, sf::Vector2f(2, -3));
		shape.setPoint(3, sf::Vector2f(0, 3));
		break;
	case 'W': case 'w':
		shape.setPointCount(8);
		shape.setPoint(0, sf::Vector2f(-2, -3));
		shape.setPoint(1, sf::Vector2f(-2, 3));
		shape.setPoint(2, sf::Vector2f(0, -1));
		shape.setPoint(3, sf::Vector2f(2, 3));
		shape.setPoint(4, sf::Vector2f(2, -3));
		shape.setPoint(5, sf::Vector2f(2, 3));
		shape.setPoint(6, sf::Vector2f(0, -1));
		shape.setPoint(7, sf::Vector2f(-2, 3));
		break;
	case 'X': case 'x':
		shape.setPointCount(6);
		shape.setPoint(0, sf::Vector2f(-2, -3));
		shape.setPoint(1, sf::Vector2f(2, 3));
		shape.setPoint(2, sf::Vector2f(0, 0));
		shape.setPoint(3, sf::Vector2f(-2, 3));
		shape.setPoint(4, sf::Vector2f(2, -3));
		shape.setPoint(5, sf::Vector2f(0, 0));
		break;
	case 'Y': case 'y':
		shape.setPointCount(6);
		shape.setPoint(0, sf::Vector2f(0, 3));
		shape.setPoint(1, sf::Vector2f(0, -1));
		shape.setPoint(2, sf::Vector2f(-2, -3));
		shape.setPoint(3, sf::Vector2f(0, -1));
		shape.setPoint(4, sf::Vector2f(2, -3));
		shape.setPoint(5, sf::Vector2f(0.001, -1));
		break;
	case 'Z': case 'z':
		shape.setPointCount(6);
		shape.setPoint(0, sf::Vector2f(-2, -3));
		shape.setPoint(1, sf::Vector2f(2, -3));
		shape.setPoint(2, sf::Vector2f(-2, 3));
		shape.setPoint(3, sf::Vector2f(2, 3));
		shape.setPoint(4, sf::Vector2f(-2, 3));
		shape.setPoint(5, sf::Vector2f(2, -3));
		break;
#pragma endregion

#pragma region Symbols
	case '!':
		shape.setPointCount(7);
		shape.setPoint(0, sf::Vector2f(0, 3));
		shape.setPoint(1, sf::Vector2f(-1, 2));
		shape.setPoint(2, sf::Vector2f(-0.01, 1));
		shape.setPoint(3, sf::Vector2f(-0.01, -3));
		shape.setPoint(4, sf::Vector2f(0.01, -3));
		shape.setPoint(5, sf::Vector2f(0.01, 1));
		shape.setPoint(6, sf::Vector2f(1, 2));
		break;
	case '[':
		shape.setPointCount(6);
		shape.setPoint(0, sf::Vector2f(0, -3));
		shape.setPoint(1, sf::Vector2f(-2, -3));
		shape.setPoint(2, sf::Vector2f(-2, 3));
		shape.setPoint(3, sf::Vector2f(0, 3));
		shape.setPoint(4, sf::Vector2f(-2, 3));
		shape.setPoint(5, sf::Vector2f(-2, -3));
		break;
	case ']':
		shape.setPointCount(6);
		shape.setPoint(0, sf::Vector2f(0, -3));
		shape.setPoint(1, sf::Vector2f(2, -3));
		shape.setPoint(2, sf::Vector2f(2, 3));
		shape.setPoint(3, sf::Vector2f(0, 3));
		shape.setPoint(4, sf::Vector2f(2, 3));
		shape.setPoint(5, sf::Vector2f(2, -3));
		break;
	case '|':
		shape.setPointCount(4);
		shape.setPoint(0, sf::Vector2f(0.01, 3));
		shape.setPoint(1, sf::Vector2f(0.01, -3));
		shape.setPoint(2, sf::Vector2f(-0.01, -3));
		shape.setPoint(3, sf::Vector2f(-0.01, 3));
#pragma endregion

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

void DisplayText(sf::RenderWindow& window, std::vector<sf::ConvexShape> textVector, sf::Vector2f position, float scale, sf::Color color = sf::Color::White, textOrigin origin = center) {
	int size = textVector.size();
	float offset = 0;

	if (origin == center) {
		offset = ((size - 1) * 5 * scale + (size - 1) * 1 * scale) / 2;
	}
	else if (origin == right) {
		offset = (size - 1) * 5 * scale + (size - 1) * 1 * scale;
	}
	else if (origin == left) {
		offset = 0;
	}

	position.x -= offset;
	for (int i = 0; i < size; i++) { //Draw each letter of the string given depending on the position, origin, scale and color
		textVector[i].setScale(scale, scale);
		textVector[i].setPosition(position);
		textVector[i].setOutlineColor(color);
		textVector[i].setRotation(0);
		window.draw(textVector[i]);

		position.x += 5*scale + 1*scale;
	}
}