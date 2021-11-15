#pragma once
#include <unordered_map>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <SDL2/SDL_audio.h>

class SoundManager
{
public:
	SoundManager();

	static SoundManager *Instance();
	void LoadSound(std::string soundName);
	Mix_Chunk *GetSound(std::string soundName);


private:
	std::unordered_map<std::string, Mix_Chunk *> soundList;


};

#define SOUND SoundManager::Instance()
