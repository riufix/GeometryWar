#include "GameManager.h"

void GameManager::Reset()
{
	score = 0;
	scoreNeeded = 100;
	scoreNextLvl = 300;
	level = 1;
}

void GameManager::ChkNextLevel(Audio& audioSystem, ParticleSystem& particles)
{
	if (score >= scoreNeeded)
	{
		scoreNeeded = scoreNeeded + scoreNextLvl * level;
		particles.ClearParticles();

		currentGameState = LevelTransition;
		audioSystem.soundList["levelEnd"].play();
		transitionTime = 1.0f;
	}
}
void GameManager::LoadHighscore()
{
	int highScoreLoaded = readHighscore();

	if (highScoreLoaded > defaultHighScore)
		highScore = highScoreLoaded;
	else
		highScore = defaultHighScore;
}