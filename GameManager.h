#pragma once
#include "deathParticle.h"
#include "audio.h"
#include "SaveManager.h"

constexpr enum gameState {
	MainMenu,
	LevelIntro,
	Game,
	GameOver,
	LevelTransition
};

class GameManager
{
private:
	int defaultHighScore = 1000;

public:
	gameState currentGameState = MainMenu;
	int score = 0;
	int scoreNeeded = 100;
	int scoreNextLvl = 300;
	int level = 1;
	int highScore = 1000;

	//Init Transition level & Game Over Timer
	float transitionTime = 1.0f;

	void Reset();
	void LoadHighscore();
	void ChkNextLevel(Audio& audioSystem, ParticleSystem& particles);
};

