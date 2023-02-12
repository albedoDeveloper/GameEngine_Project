#include "SoundManager.h"
#include <iostream>
SoundManager::SoundManager()
{

	gSoloud.init();

}

SoundManager *SoundManager::Instance()
{
	static SoundManager instance;
	return &instance;
}



void SoundManager::LoadSound(std::string soundName)
{
	SoLoud::Soloud gSoloud; // SoLoud engine
	SoLoud::Wav* sound = new SoLoud::Wav();      // One wave file
	
	auto soundNameFull = "../Assets/Sounds/" + soundName;

	sound->load(soundNameFull.data());


	soundList.insert(std::make_pair(soundName, sound));
}

SoLoud::Wav * SoundManager::GetSound(std::string soundName)
{
	if (soundList.count(soundName) != 0)
		return soundList[soundName];
	else
		return nullptr;
}
