/*****************************************************************//**
 * \file   CSound.h
 * \brief  Sound Component for audio sources
 *
 * \date   September 2021
 *********************************************************************/
#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include "CComponent.h"
#include "SoundManager.h"
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
		SoLoud::handle handler;
	};

		/** @brief sound information */
	std::unordered_map<std::string, SoundInfo> soundinfo;


};
