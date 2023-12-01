#include "Effect.h"

#include <iostream>

void Effect::ChangeFlashScreen(int duration, bool randomness, sf::Color color)
{
	FlashScreenDuration = duration;
	FlashScreenRandom = randomness;
	FlashScreenColor = color; 
}

sf::Color Effect::RandomColor()
{
	return sf::Color(rand() % 255, rand() % 255, rand() % 255);
}

void Effect::UpdateEffect(sf::RenderWindow& window, float deltatime)
{
	if (FlashScreenDuration > 0)
	{

		FlashScreenDuration = FlashScreenDuration - deltatime;

		sf::RectangleShape rectScreen;
		rectScreen.setPosition(0, 0);
		rectScreen.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));

		if(FlashScreenRandom)
		{
			rectScreen.setFillColor(RandomColor());
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