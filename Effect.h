#pragma once

#include <SFML/Graphics.hpp>

class Effect
{
private :
	float FlashScreenDuration = 0.0f;
	bool FlashScreenRandom = false;
	sf::Color FlashScreenColor = sf::Color::Black;

public:
	void ChangeFlashScreen(float duration, bool randomness, sf::Color color = sf::Color::Black);
	sf::Color RandomColor();

	void UpdateEffect(sf::RenderWindow& window, float deltatime);
};