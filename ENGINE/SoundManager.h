#pragma once
#include <unordered_map>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <SDL2/SDL_audio.h>

class SoundManager
{
	public:
		SoundManager();
		/// @brief Contains an instance of the class
		/// @return 
		static SoundManager *Instance();
		
		/// @brief Load a sound into the engine
		/// @param soundName 
		void LoadSound(std::string soundName);
		
		/// @brief Return a sound that is saved in the manager
		/// @param soundName 
		/// @return 
		Mix_Chunk* GetSound(std::string soundName);

	static SoundManager *Instance();
	void LoadSound(std::string soundName);
	Mix_Chunk *GetSound(std::string soundName);

	private:
		/// @brief Contains all the sounds loaded into the engine
		std::unordered_map<std::string, Mix_Chunk*> soundList;


};

#define SOUND SoundManager::Instance()
