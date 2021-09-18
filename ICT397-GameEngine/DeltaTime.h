/*****************************************************************//**
 * \file   DeltaTime.h
 * \brief  Elapsed time since last update
 *
 * \date   September 2021
 *********************************************************************/
#pragma once

#include <SDL2/SDL.h>

/** @brief The elapsed time between frames */
class DeltaTime
{
public:
		/**
		 * @brief get singleton instance
		*/
	static DeltaTime *Instance();

		/**
		 * @brief call once a frame to update delta time value
		*/
	void UpdateDeltaTime();

		/**
		 * @brief returns the current time if we are lagging behind
		*/
	void CatchupDeltaTime();

		/**
		* @brief get current delta time
		*/
	double GetDeltaTime();

		/**
		 * @brief Gets elapsed time since last frame
		 *
		 * \return the elapsed time as a float
		 */
	float GetTimeElapsed() const;

private:

		/**
		 * @Initialize constructor
		 */
	DeltaTime();

		/** @brief the current time */
	Uint64 NOW;
		/** @brief the previous time */
	Uint64 LAST;
		/** @brief delta time */
	double deltaTime;
};

#define TIME DeltaTime::Instance()