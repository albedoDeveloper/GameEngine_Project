#include "SoundManager.h"
#include <SDL2/SDL.h>
SoundManager::SoundManager()
{
	int flags = MIX_INIT_MP3;
	int initted = Mix_Init(flags);

	if (initted & flags != flags)
		std::cout << "Mix_Init: Failed to intialize mp3" << std::endl;

	if (SDL_Init(SDL_INIT_AUDIO) == -1)
	{
		printf("SDL_Init: %s\n", SDL_GetError());
		exit(1);
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
	{
		printf("Mix_OpenAudio: %s\n", Mix_GetError());
		exit(2);
	}
}

SoundManager *SoundManager::Instance()
{
	static SoundManager instance;
	return &instance;
}


void SoundManager::LoadSound(std::string soundName)
{
	auto soundNameFull = "../Assets/Sounds/" + soundName;

	Mix_Chunk* sound = Mix_LoadWAV(soundNameFull.data());

	if (!sound)
		std::cout << "ERROR Mix_LoadWAV: " << Mix_GetError() << std::endl;

	soundList.insert(std::make_pair(soundName, sound));
}

Mix_Chunk* SoundManager::GetSound(std::string soundName)
{
	if (soundList.count(soundName) != 0)
		return soundList[soundName];
	else
		return nullptr;
}
