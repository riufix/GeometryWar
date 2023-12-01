#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <list>

#include "Player.h"
#include "BulletBehaviour.h"
#include "map.h"
#include "Monster.h"
#include "Effect.h"
#include "text.h"

constexpr enum gameState {
	MainMenu,
	Game,
	GameOver,
	LevelTransition
};

//Prototypes
void SpawnMonster(std::list<Monster>& monsterList, std::vector<sf::Vector3f>& positionVector, sf::Vector2f windowCenter, int currentLevel);
void ChkPlayerHit(Player& player, Effect& effect, gameState& currentState);

int main()
{
	//Init Window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Geometry Wars",sf::Style::Default, settings);
	window.setVerticalSyncEnabled(true);
	//clock
	sf::Clock frameClock;
	//Center of window
	sf::Vector2f windowCenter;
	windowCenter.x = window.getSize().x / 2.0f;
	windowCenter.y = window.getSize().y / 2.0f;
	
	//Init GameState
	gameState currentGameState = Game;
	int score = 0;
	int scoreNeeded = 100;
	int scoreNextLvl = 300;
	int level = 1;

	//Init Effect
	Effect effect;

	//Init Player
	Player player;
	player.InitializeGraphic();
	
	//Init Bullet List
	std::list<BulletBehaviour> bulletList;

	//Init Map
	sf::ConvexShape map;
	std::vector<sf::Vector3f> positionVector;
	levelShape currentLevel = levelShape::triangle;
	changeLevel(map, positionVector, currentLevel);

	//Init Ennemy List
	std::list<Monster> monsterList;
	int newCorridor = rand() % positionVector.size();
	monsterList.push_back(Monster(windowCenter, positionVector[newCorridor], newCorridor, 1));

	//Init Transition level & Game Over Timer
	float transitionTime = 1.0f;

	while (window.isOpen())
	{
		float deltaTime = frameClock.restart().asSeconds();
		//std::cout << 1.f / deltaTime << " FPS" << std::endl;

		//Event
		sf::Event event;
		while (window.pollEvent(event))
		{
			// On gère l'événément
			switch (event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;

				default:
					break;
			}
		}

		/* --------------
			LOGIC
		-------------- */
		switch (currentGameState)
		{
		case MainMenu:
			break;

		case Game:
			//Process Player Input
			player.ProcessMoveInput(positionVector.size(), deltaTime);
			player.UpdateSprite(positionVector[player.positionIndex].x, positionVector[player.positionIndex].y, positionVector[player.positionIndex].z);
			if (player.ProcessFireInput(deltaTime))
			{
				bulletList.push_back(BulletBehaviour(BulletBehaviour::Owner::Player, 100, player.positionIndex, player.shape.getPosition()));
			}
			
			player.ProcessInvincibility(deltaTime);
			
			//Look if go to next level
			if (score >= scoreNeeded) 
			{
				scoreNeeded = scoreNeeded + scoreNextLvl;
				currentGameState = LevelTransition;
				transitionTime = 1.0f;
			}

			break;

		case GameOver:
			break;

		case LevelTransition:
			if (transitionTime < 40.0f)
				transitionTime = transitionTime + deltaTime * 15;
			else
			{
				//Change Level
				AddLevel(currentLevel);
				changeLevel(map, positionVector, currentLevel);

				//Clear bulletList & Reset player position
				player.positionIndex = 0;
				bulletList.clear();

				//Add level and add new number of monsters
				level++;
				if (level % 3 == 0) //Give one life if complete each map
					player.Health++;
				monsterList.clear();
				for(int i=0; i< level; i++)
					SpawnMonster(monsterList, positionVector, windowCenter, level);
				
				currentGameState = Game;
			}
			break;
		}




		/* --------------
			DISPLAY
		-------------- */
		window.clear();
		effect.UpdateEffect(window, deltaTime);

		switch (currentGameState)
		{
		case MainMenu:
		{

		}
		break;

		case Game:
		{
			//Display level
			DrawLevel(window, map, windowCenter, 5, 30);

			//Display & manage Ennemies
			std::list<Monster>::iterator monsterListIt = monsterList.begin();
			while (monsterListIt != monsterList.end())
			{
				bool skipToNext = false; //skip if collision
				if (monsterListIt->ProcessMonster(deltaTime, bulletList))
				{
					if (monsterListIt->progression > 100)
						ChkPlayerHit(player, effect, currentGameState);
					
					monsterListIt = monsterList.erase(monsterListIt);
					SpawnMonster(monsterList, positionVector, windowCenter, level);
				}
				else
				{
					//Manage Ennemies - Bullet Collision
					std::list<BulletBehaviour>::iterator bulletCollisionListIt = bulletList.begin();
					while (bulletCollisionListIt != bulletList.end())
					{
						if (monsterListIt->ChkCollision(*bulletCollisionListIt))
						{
							skipToNext = true;
							score = score + 25;

							bulletCollisionListIt = bulletList.erase(bulletCollisionListIt);
							bulletCollisionListIt = bulletList.end();

							monsterListIt->Health--;
							if(monsterListIt->progression < 95) //Knockback Effect
								monsterListIt->progression -= 5;
							if (monsterListIt->Health <= 0)
							{
								monsterListIt = monsterList.erase(monsterListIt);
								SpawnMonster(monsterList, positionVector, windowCenter, level);
							}
						}
						else
							bulletCollisionListIt++;			
					}

					if (skipToNext) continue;
					monsterListIt->DrawSprite(window);
					monsterListIt++;
				}
			}

			//Display & manage projectiles
			std::list<BulletBehaviour>::iterator bulletListIt = bulletList.begin();
			while (bulletListIt != bulletList.end())
			{
				if (bulletListIt->ProcessBullet(windowCenter))
				{
					if (bulletListIt->ChkCollision(player.positionIndex))
						ChkPlayerHit(player, effect, currentGameState);
					bulletListIt = bulletList.erase(bulletListIt);
				}
				else
				{
					bulletListIt->DisplayBullet(window);
					bulletListIt++;
				}
			}

			//Display player
			player.DrawSprite(window);

			//Display UI
			for (int i = 0; i < player.Health; i++)
			{
				player.UpdateSprite(100 + i * 150, 100, player.shape.getRotation());
				player.DrawSprite(window);
			}
			
		}
		break;

		case GameOver:
		{
			DrawLevel(window, map, windowCenter, 5, 30);
			for (Monster& monster : monsterList)
				monster.DrawSprite(window);
			for (BulletBehaviour& bullet : bulletList)
				bullet.DisplayBullet(window);
			player.DrawSprite(window);

			//Display Score

		}
		break;
		
		case LevelTransition:
		{
			DrawLevel(window, map, windowCenter, 5 * transitionTime, 30 * transitionTime, effect.RandomColor());

		}
		break;
		}

		window.display();
	}
}

void SpawnMonster(std::list<Monster>& monsterList, std::vector<sf::Vector3f>& positionVector, sf::Vector2f windowCenter, int currentLevel)
{
	int newCorridor = rand() % positionVector.size();
	int newHealth = 1 + rand() % currentLevel > 2 ? 3: 
								 currentLevel > 1 ? 2: 
													1;
	monsterList.push_back(Monster(windowCenter, positionVector[newCorridor], newCorridor, newHealth));
}

void ChkPlayerHit(Player& player, Effect& effect, gameState& currentState)
{
	if (!player.isInvincible())
		if (player.Hit())
			currentState = GameOver;
		else
		{
			effect.ChangeFlashScreen(1.0f, false, sf::Color::Red);
		}
}

/*
Main Menu

Game :
	Effect :
		when kill monster
	UI :
		Score

Game Over
	Logic -> goto Main Menu
	Display Score
	Animation

Sound :
	Player shoot
	Player Hit
	Monster Hit
	Transition
Music :
	Title screen
	Game
	GameOver

//Prb :
	Ennemies on top of each others
*/