#include "MonsterManager.h"

void MonsterManager::ProcessMonsters(Audio& audioSystem, Player& player, Effect& effect, ParticleSystem& particles, GameManager& gameManager, sf::RenderWindow& window, BulletManager& bulletManager, std::vector<sf::Vector3f>& positionVector, sf::Vector2f windowCenter, float deltaTime, float gameOverTempo)
{
	std::list<Monster>::iterator monsterListIt = monsterList.begin();
	while (monsterListIt != monsterList.end())
	{
		bool skipToNext = false; //skip if collision
		if (monsterListIt->ProcessMonster(deltaTime, bulletManager.bulletList))
		{
			if (monsterListIt->progression > 100)
				player.ChkPlayerHit(effect, gameManager, audioSystem, gameOverTempo);

			monsterListIt = monsterList.erase(monsterListIt);
			SpawnMonster(positionVector, windowCenter, gameManager.level);
		}
		else
		{
			//Manage Ennemies - Bullet Collision
			std::list<BulletBehaviour>::iterator bulletCollisionListIt = bulletManager.bulletList.begin();
			while (bulletCollisionListIt != bulletManager.bulletList.end())
			{
				if (monsterListIt->ChkCollision(*bulletCollisionListIt))
				{
					skipToNext = true;
					gameManager.score = gameManager.score + 25;

					bulletCollisionListIt = bulletManager.bulletList.erase(bulletCollisionListIt);
					bulletCollisionListIt = bulletManager.bulletList.end();

					monsterListIt->Health--;
					if (monsterListIt->progression < 95) //Knockback Effect
						monsterListIt->progression -= 10;
					if (monsterListIt->Health <= 0)
					{
						gameManager.score = gameManager.score + 15;
						//particle on ennemi death position
						particles.addParticles(100, monsterListIt->shape.getPosition());
						audioSystem.soundList["monsterDeath"].play();

						monsterListIt = monsterList.erase(monsterListIt);
						SpawnMonster(positionVector, windowCenter, gameManager.level);
					}
					else
						audioSystem.soundList["monsterHit"].play();
				}
				else
					bulletCollisionListIt++;
			}

			if (skipToNext) continue;
			monsterListIt->DrawSprite(window);
			monsterListIt++;
		}
	}
}

void MonsterManager::SpawnMonster(std::vector<sf::Vector3f>& positionVector, sf::Vector2f windowCenter, int currentLevel)
{
	int newCorridor = 0;
	do
		newCorridor = rand() % positionVector.size();
	while (newCorridor == lastCorridor);
	lastCorridor = newCorridor;

	int newHealth = 1 + rand() % currentLevel > 2 ? 3 :
		currentLevel > 1 ? 2 :
		1;

	monsterList.push_back(Monster(windowCenter, positionVector[newCorridor], newCorridor, newHealth));
}

void MonsterManager::PushFirstMonster(std::vector<sf::Vector3f>& positionVector, sf::Vector2f windowCenter)
{
	int newCorridor = rand() % positionVector.size();
	int lastCorridor = newCorridor;
	monsterList.push_back(Monster(windowCenter, positionVector[newCorridor], newCorridor, 1));
}