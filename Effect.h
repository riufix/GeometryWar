#pragma once

<<<<<<< Updated upstream
void 
=======
#include <SFML/Graphics.hpp>

class Effect
{
public:
	int FlashScreenDuration = false;
	bool FlashScreenRandom = false;
	sf::Color FlashScreenColor = sf::Color::Black;

	void ChangeFlashScreen(int duration, bool randomness, sf::Color color = sf::Color::Black);

	void UpdateEffect(sf::RenderWindow& window, float deltatime);
};
>>>>>>> Stashed changes
