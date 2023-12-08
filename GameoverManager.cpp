#include "GameoverManager.h"

void GameoverManager::DisplayGameOver(sf::RenderWindow& window, Effect& effect, sf::Vector2f windowCenter, float deltaTime, int score, int highScore)
{
	gameOverTimer += deltaTime;
	//Display Game Over
	float gameOverWaveAnimation = 20 * sin(gameOverTimer);
	sf::Color gameOverWaveColor = sf::Color(255, 191 + 64 * sin(gameOverTimer * 30), 191 + 64 * sin(gameOverTimer * 30));
	DisplayText(window, textGameOver1, sf::Vector2f(windowCenter.x, windowCenter.y - 10 * 20.0f + gameOverWaveAnimation), 20.0f, gameOverWaveColor);
	DisplayText(window, textGameOver2, sf::Vector2f(windowCenter.x, windowCenter.y + 0 * 20.0f + gameOverWaveAnimation), 20.0f, gameOverWaveColor);

	//Display Score
	if (gameOverTempo >= 5.0f) 	DisplayText(window, textGOScore, sf::Vector2f(windowCenter.x + 20, windowCenter.y + 10 * 20.0f), 10.0f, sf::Color::White, right);
	if (gameOverTempo >= 10.0f) DisplayText(window, stringToDisplayable(std::to_string(score)), sf::Vector2f(windowCenter.x + 20, windowCenter.y + 10 * 20.0f), 10.0f, sf::Color::White, textOrigin::left);
	if (gameOverTempo >= 15.0f) DisplayText(window, textGOHighScore, sf::Vector2f(windowCenter.x + 20, windowCenter.y + 15 * 20.0f), 10.0f, sf::Color::White, right);
	if (gameOverTempo >= 20.0f) {
		if (score == highScore) {
			DisplayText(window, stringToDisplayable(std::to_string(highScore)), sf::Vector2f(windowCenter.x + 20, windowCenter.y + 15 * 20.0f), 10.0f, effect.RandomColor(), textOrigin::left);
			DisplayText(window, textGONewRecord, sf::Vector2f(windowCenter.x + 18, windowCenter.y + 18 * 20.0f), 3.0f, effect.RandomColor(), textOrigin::left);
		}
		else {
			DisplayText(window, stringToDisplayable(std::to_string(highScore)), sf::Vector2f(windowCenter.x + 20, windowCenter.y + 15 * 20.0f), 10.0f, sf::Color::White, textOrigin::left);
		}
	}
	if (gameOverTempo >= 25.0f) DisplayText(window, textBackToMenu, sf::Vector2f(windowCenter.x, windowCenter.y + 21 * 20.0f), 5.0f, sf::Color::Green);
}