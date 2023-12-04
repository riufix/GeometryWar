#pragma once
#include <Windows.h>
#include <SFML/Audio.hpp>
#include <map>

class Audio
{
private :
	sf::SoundBuffer playerShootSoundBuffer;
	sf::SoundBuffer playerHitSoundBuffer;
	sf::SoundBuffer bulletHitSoundBuffer;
	sf::SoundBuffer monsterHitSoundBuffer;
	sf::SoundBuffer monsterDeathSoundBuffer;
	sf::SoundBuffer levelIntroSoundBuffer;
	sf::SoundBuffer levelEndSoundBuffer;

public :
	std::map<std::string, sf::Sound> soundList;
	void InitializeBuffer();
};