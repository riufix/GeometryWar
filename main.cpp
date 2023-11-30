#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <list>

#include "Player.h"
#include "BulletBehaviour.h"
#include "map.h"
#include "Monster.h"
#include "Effect.h"

constexpr enum levelShape {
	triangle,
	square,
	pantagone
};

constexpr enum gameState {
	MainMenu,
	Game,
	GameOver,
	LevelTransition
};

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
	int scoreNextLvl = 150;
	//Init Effect
	Effect effect;

	//Init Player
	Player player;
	player.InitializeGraphic();
	
	//Init Bullet List
	std::list<BulletBehaviour> bulletList;

	//Init Map
	sf::ConvexShape map;

	//Init player position list
	sf::Vector3f TrianglePositionList[9] = {
	{1090,330,55},
	{1220,500, 60},
	{1360,730,55},
	{1250,890,180},
	{960,890,180},
	{690,890,180},
	{560,730,-50},
	{690,510,-55},
	{830,330,-55}
	};
	sf::Vector3f SquarePositionList[8] = {
	{1100,195,0},
	{1300,400,90},
	{1300,650,90},
	{1100,875,180},
	{800,875,180},
	{620,650,-90},
	{620,400,-90},
	{820,195,0}
	};
	sf::Vector3f PantagonePositionList[5] = {
	{1150,370,54},
	{0,0,108},
	{0,0,162},
	{0,0,-108},
	{0,0,-54}
	};

	std::vector<sf::Vector3f> positionVector;
	levelShape currentlevel = triangle;
	positionVector.clear();
	switch (currentlevel)
	{
	case triangle:
		map = InitializeTriangle();
		for (int i = 0; i < 9; i++) {
			positionVector.push_back(TrianglePositionList[i]);
		}
		break;

	case square:
		map = InitializeSquare();
		for (int i = 0; i < 8; i++) {
			positionVector.push_back(SquarePositionList[i]);
		}
		break;

	case pantagone:
		map = InitializePantagone();
		for (int i = 0; i < 5; i++) {
			positionVector.push_back(PantagonePositionList[i]);
		}
		break;

	default:
		break;
	}


	//Init Ennemy List
	std::list<Monster> monsterList;
	int newCorridor = rand() % positionVector.size();
	monsterList.push_back(Monster(windowCenter, positionVector[newCorridor], newCorridor));

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
			
			if (score >= scoreNeeded) 
			{
				scoreNeeded = scoreNeeded + scoreNextLvl;
			}

			break;

		case GameOver:
			break;
		case LevelTransition:

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
				if (monsterListIt->ProcessMonster(deltaTime))
				{
					if (monsterListIt->progression > 100)
					{
						if (!player.isInvincible())
							if (player.Hit())
								currentGameState = GameOver;
							else
							{
								effect.ChangeFlashScreen(1.0f, false, sf::Color::Red);
							}
					}

					monsterListIt = monsterList.erase(monsterListIt);

					int newCorridor = rand() % positionVector.size();
					monsterList.push_back(Monster(windowCenter, positionVector[newCorridor], newCorridor));
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

							monsterListIt = monsterList.erase(monsterListIt);
							bulletCollisionListIt = bulletList.erase(bulletCollisionListIt);

							int newCorridor = rand() % positionVector.size();
							monsterList.push_back(Monster(windowCenter, positionVector[newCorridor], newCorridor));

							bulletCollisionListIt = bulletList.end();
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
					bulletListIt = bulletList.erase(bulletListIt);
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
			DrawLevel(window, map, windowCenter, 5, 30, effect.RandomColor());
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

		}
		break;

		}


		window.display();
	}
}

void changeLevel(sf::ConvexShape map, std::vector<sf::Vector3f> positionList) {

}

/*
Main Menu - F

Game :
	Effect : - F
		when dead 
		when kill monster
	Types of ennemies :
		2 hit
		3 hit + Fire back
	UI :
		Score - F
Game Over - F
	Logic -> goto Main Menu
	Display Score
	Animation

LevelTransition :
	Transition - F
	Change Level - V

Sound :
	Player shoot
	Player Hit
	Monster Hit
	Transition
Music :
	Title screen
	Game
	GameOver
*/