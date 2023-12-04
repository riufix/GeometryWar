#include "audio.h"

std::string getAppPath() {
	char cExeFilePath[256];
	GetModuleFileNameA(NULL, cExeFilePath, 256);
	std::string exeFilePath = cExeFilePath;
	int exeNamePos = exeFilePath.find_last_of("\\/");
	std::string appPath = exeFilePath.substr(0, exeNamePos + 1);

	return appPath;
}

void Audio::InitializeSoundBuffer() 
{
	playerShootSoundBuffer.loadFromFile(getAppPath() + "sound\\playerShoot.wav");
	playerHitSoundBuffer.loadFromFile(getAppPath() + "sound\\playerHit.wav");
	bulletHitSoundBuffer.loadFromFile(getAppPath() + "sound\\bulletHit.wav");
	monsterHitSoundBuffer.loadFromFile(getAppPath() + "sound\\monsterHit.wav");
	monsterDeathSoundBuffer.loadFromFile(getAppPath() + "sound\\monsterDeath.wav");
	levelIntroSoundBuffer.loadFromFile(getAppPath() + "sound\\levelIntro.wav");
	levelEndSoundBuffer.loadFromFile(getAppPath() + "sound\\levelEnd.wav");
	
	sf::Sound bufferSound;
	bufferSound.setBuffer(playerShootSoundBuffer);
	soundList["playerShoot"] = bufferSound;

	bufferSound.setBuffer(playerHitSoundBuffer);
	soundList["playerHit"] = bufferSound;

	bufferSound.setBuffer(bulletHitSoundBuffer);
	soundList["bulletHit"] = bufferSound;

	bufferSound.setBuffer(monsterHitSoundBuffer);
	soundList["monsterHit"] = bufferSound;	

	bufferSound.setBuffer(monsterDeathSoundBuffer);
	soundList["monsterDeath"] = bufferSound;	
	
	bufferSound.setBuffer(levelIntroSoundBuffer);
	soundList["levelIntro"] = bufferSound;	
	
	bufferSound.setBuffer(levelEndSoundBuffer);
	soundList["levelEnd"] = bufferSound;
}

void Audio::InitializeMusicBuffer() 
{
	musicList["Menu"].openFromFile(getAppPath() + "sound\\menuMusic.wav");
	musicList["Game"].openFromFile(getAppPath() + "sound\\gameMusic.wav");
}