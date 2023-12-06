#include "BulletManager.h"


void BulletManager::ProcessBullets(Audio& audioSystem, Effect& effect, Player& player, sf::RenderWindow& window, GameManager& gameManager, float deltaTime, float gameOverTempo, sf::Vector2f windowCenter)
{
	//Display & manage projectiles
	std::list<BulletBehaviour>::iterator bulletListIt = bulletList.begin();
	while (bulletListIt != bulletList.end())
	{
		//Collision btw Bullets
		if (bulletListIt->CheckOtherBulletCollision(bulletList, bulletListIt))
		{
			audioSystem.soundList["bulletHit"].play();
			continue;
		}

		if (bulletListIt->ProcessBullet(windowCenter))
		{
			if (bulletListIt->CheckPlayerCollision(player.positionIndex)) //Collision with player
				player.ChkPlayerHit(effect, gameManager, audioSystem, gameOverTempo);
			bulletListIt = bulletList.erase(bulletListIt);
		}
		else
		{
			bulletListIt->DisplayBullet(window, deltaTime);
			bulletListIt++;
		}
	}
}