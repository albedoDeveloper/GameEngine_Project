/*****************************************************************//**
 * \file   CSound.h
 * \brief  Sound Component for audio sources
 *
 * \date   September 2021
 *********************************************************************/
#pragma once
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <SDL2/SDL_audio.h>
#include <unordered_map>
#include <memory>
#include <vector>
#include "CComponent.h"

/** @brief Sound Component Class */
class CSound : public CComponent
{
public:

		/**
		* @brief Constructor based on parent GameObject
		* @param parent the parent transform for this component
		* @param parentObj the parent object of this component
		*/
	CSound(Transform *parent, GameObject *parentObj);

		/**
		* @brief Loads sound
		*
		* \param soundName name of the sound
		*/
	void LoadSound(std::string soundName);

		/**
		* @brief Play Sound
		*
		* \param soundName name of the sound
		* \param length length to play
		* \param positional is sound positional?
		*/
	void PlaySound(std::string soundName, int length, bool positional);

	/// @brief Stop a sound from playing
	/// @param soundName 
	void StopPlaying(std::string soundName);

		/**
		* @brief updates ongoing behaviour each frame
		*/
	virtual void Update();

	/// @brief Change the volume of a sound
	/// @param soundName 
	/// @param volume 
	void ChangeVolume(std::string soundName, int volume);

private:
		/**
		* @brief Sound variables struct
		*/
	struct SoundInfo
	{
			/** @brief name of the sound */
		std::string soundName;

			/** @brief is sound positional */
		bool isPositional = false;

			/** @brief sound channel */
		int channel = -1;
	};

		/** @brief sound information */
	std::unordered_map<std::string,SoundInfo> soundinfo;


};
