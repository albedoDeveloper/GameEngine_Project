#include "CSound.h"

CSound::CSound()
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

void CSound::LoadSound(std::string soundName)
{
	soundList.insert(std::make_pair(soundName, std::unique_ptr<Mix_Chunk>(new Mix_Chunk)));



}