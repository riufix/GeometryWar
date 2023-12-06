#pragma once
#include "SFML/Graphics.hpp"
#include <list>

#include "GameManager.h"
#include "BulletBehaviour.h"
#include "audio.h"
#include "Player.h"
#include "Effect.h"

class BulletManager
{
public :
	std::list<BulletBehaviour> bulletList;
	void ProcessBullets(Audio& audioSystem, Effect& effect, Player& player, sf::RenderWindow& window, GameManager& gameManager, float deltaTime, float gameOverTempo, sf::Vector2f windowCenter);
};

