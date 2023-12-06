#pragma once
#include "SFML/Graphics.hpp"
#include "Effect.h"
#include "GameManager.h"
#include "text.h"

class MenuManager
{
private:
	const std::vector<sf::ConvexShape> textCopyright = stringToDisplayable("2023 | Baptiste V | Enguerrand C | Titouan D | A2 JV GP");
	const std::vector<sf::ConvexShape> textTitle = stringToDisplayable("ORKAN");
	const std::vector<sf::ConvexShape> textMission1 = stringToDisplayable("Welcome Aboard Captain!");
	const std::vector<sf::ConvexShape> textMission2 = stringToDisplayable("Your mission is to prevent enemy ships");
	const std::vector<sf::ConvexShape> textMission3 = stringToDisplayable("from reaching your position!");
	const std::vector<sf::ConvexShape> textControl1 = stringToDisplayable("[SPACE] to fire   ");
	const std::vector<sf::ConvexShape> textControl2 = stringToDisplayable("   [Q][D] to move");
	const std::vector<sf::ConvexShape> textControl3 = stringToDisplayable("   [Arrows]");
	const std::vector<sf::ConvexShape> textHighScore = stringToDisplayable("current HighScore   ");
	const std::vector<sf::ConvexShape> textStart = stringToDisplayable("Press [Space] when ready to start");

public:
	float titleScale = 0;
	float startTempo = 0;
	float isStarting = false;

	void Reset();
	void DisplayMenu(sf::RenderWindow& window, sf::Vector2f windowCenter, Effect& effect, GameManager& gameManager);
};

