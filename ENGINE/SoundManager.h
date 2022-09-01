#pragma once
#include <unordered_map>
#include "../ENGINE/ThirdParty/soLoud/include/soloud.h"
#include "../ENGINE/ThirdParty/soLoud/include/soloud_wav.h"

class SoundManager
{
	public:
		SoundManager();
		/// @brief Contains an instance of the class
		/// @return 
		static SoundManager *Instance();
		

		//~SoundManager();

		/// @brief Load a sound into the engine
		/// @param soundName 
		void LoadSound(std::string soundName);
		
		/// @brief Return a sound that is saved in the manager
		/// @param soundName 
		/// @return 
		SoLoud::Wav* GetSound(std::string soundName);


		/// @brief Return a sound that is saved in the manager
		/// @param soundName 
		/// @return 
		SoLoud::Soloud gSoloud;

	private:
		/// @brief Contains all the sounds loaded into the engine
		std::unordered_map<std::string, SoLoud::Wav*> soundList;


};

#define SOUND SoundManager::Instance()
