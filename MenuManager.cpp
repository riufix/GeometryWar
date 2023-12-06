#include "MenuManager.h"

void MenuManager::DisplayMenu(sf::RenderWindow& window, sf::Vector2f windowCenter, Effect& effect, GameManager& gameManager)
{
	if (startTempo < 10) {
		DisplayText(window, textCopyright, sf::Vector2f(windowCenter.x, 50), 3);
		DisplayText(window, textTitle, sf::Vector2f(windowCenter.x, 200), titleScale, effect.RandomColor());

		if (titleScale >= 20) {
			DisplayText(window, textMission1, sf::Vector2f(windowCenter.x, 400), 6, sf::Color::Yellow);
			DisplayText(window, textMission2, sf::Vector2f(windowCenter.x, 475), 6);
			DisplayText(window, textMission3, sf::Vector2f(windowCenter.x, 525), 6);

			DisplayText(window, textControl1, sf::Vector2f(windowCenter.x, 650), 6, sf::Color::Red, right);
			DisplayText(window, textControl2, sf::Vector2f(windowCenter.x, 650), 6, sf::Color::Red, left);
			DisplayText(window, textControl3, sf::Vector2f(windowCenter.x, 700), 6, sf::Color::Red, left);

			DisplayText(window, textHighScore, sf::Vector2f(windowCenter.x + 180, 800), 5, sf::Color::White, right);
			DisplayText(window, stringToDisplayable(std::to_string(gameManager.highScore)), sf::Vector2f(windowCenter.x + 180, 800), 5, sf::Color::White, left);

			if (!isStarting) DisplayText(window, textStart, sf::Vector2f(windowCenter.x, 1000), 6, sf::Color::Green);
			else DisplayText(window, textStart, sf::Vector2f(windowCenter.x, 1000), 6, effect.RandomColor());
		}
	}
	else window.clear();
}

void MenuManager::Reset()
{
	titleScale = 0;
	startTempo = 0;
	isStarting = false;
}