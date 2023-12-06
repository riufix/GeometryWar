#pragma once
#include "BulletManager.h"
#include "Monster.h"
#include "deathParticle.h"

class MonsterManager
{
public :
	int lastCorridor;
	std::list<Monster> monsterList;
	void ProcessMonsters(Audio& audioSystem, Player& player, Effect& effect, ParticleSystem& particles, GameManager& gameManager, sf::RenderWindow& window, BulletManager& bulletManager, std::vector<sf::Vector3f>& positionVector, sf::Vector2f windowCenter, float deltaTime, float gameOverTempo);
	void SpawnMonster(std::vector<sf::Vector3f>&positionVector, sf::Vector2f windowCenter, int currentLevel);
	void PushFirstMonster(std::vector<sf::Vector3f>& positionVector, sf::Vector2f windowCenter);
};

