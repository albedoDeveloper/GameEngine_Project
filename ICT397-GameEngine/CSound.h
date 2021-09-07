#pragma once
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL.h>
#include <unordered_map>
#include <memory>
class CSound
{
public:
	void LoadSound(std::string soundName);
	void PlaySound();

private:
	std::unordered_map<std::string, std::unique_ptr<Mix_Chunk>> soundList;
};

