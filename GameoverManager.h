#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include "Effect.h"
#include "text.h"

class GameoverManager
{
private:
	const std::vector<sf::ConvexShape> textGameOver1 = stringToDisplayable("GAME");
	const std::vector<sf::ConvexShape> textGameOver2 = stringToDisplayable("OVER");
	const std::vector<sf::ConvexShape> textGOScore = stringToDisplayable("Score  ");
	const std::vector<sf::ConvexShape> textGOHighScore = stringToDisplayable("HighScore  ");
	const std::vector<sf::ConvexShape> textGONewRecord = stringToDisplayable("New Record!");
	const std::vector<sf::ConvexShape> textBackToMenu = stringToDisplayable("press [Space] to go back to the menu");
	float gameOverTimer = 0;

public :
	float gameOverTempo = 0;
	void DisplayGameOver(sf::RenderWindow& window, Effect& effect, sf::Vector2f windowCenter, float deltaTime, int score, int highScore);
};

