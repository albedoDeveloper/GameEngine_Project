#pragma once
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL.h>
#include <unordered_map>
#include <memory>
#include <vector>
#include "CComponent.h"

class CSound : public CComponent
{
public:
	CSound(Transform *parent, GameObject *parentObj);
	void LoadSound(std::string soundName);
	void PlaySound(std::string soundName, int length, bool positional);

	/**
	 * @brief updates ongoing behaviour each frame
	*/
	virtual void Update();

private:
	struct SoundInfo
	{
		std::string soundName;
		bool isPositional = false;
		int channel = -1;
	};

	std::unordered_map<std::string, Mix_Chunk *> soundList;
	std::vector<SoundInfo> soundinfo;
};
