#include "Effect.h"

#include <iostream>

void Effect::ChangeFlashScreen(int duration, bool randomness, sf::Color color)
{
	FlashScreenDuration = duration;
	FlashScreenRandom = randomness;
	FlashScreenColor = color; 
}

void Effect::UpdateEffect(sf::RenderWindow& window, float deltatime)
{
	if (FlashScreenDuration >= 0)
	{

		FlashScreenDuration = FlashScreenDuration - deltatime;

		sf::RectangleShape rectScreen;
		rectScreen.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
		rectScreen.setScale(10, 10);

		if(FlashScreenRandom)
		{
			rectScreen.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
		}
		else
		{
			rectScreen.setFillColor(sf::Color(FlashScreenColor.r * cos(FlashScreenDuration * 50),
											  FlashScreenColor.g * cos(FlashScreenDuration * 50),
											  FlashScreenColor.b * cos(FlashScreenDuration * 50)));
		}

		window.draw(rectScreen);
	}
}