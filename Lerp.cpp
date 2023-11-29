#include "Lerp.h"

sf::Vector2f Vector2Lerp(sf::Vector2f a, sf::Vector2f b, float t)
{
	return sf::Vector2f(a.x + (b.x - a.x) * t,
		a.y + (b.y - a.y) * t);
}
