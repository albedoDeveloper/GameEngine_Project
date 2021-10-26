/*****************************************************************//**
 * \file   MyTime.h
 * \brief  Elapsed time since last update
 *
 * \date   September 2021
 *********************************************************************/
#pragma once

#include <SDL2/SDL.h>

/** @brief The elapsed time between frames */
class MyTime
{
public:
		/**
		 * @brief get singleton instance
		*/
	static MyTime *Instance();

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
	MyTime();

		/** @brief the current time */
	Uint64 m_now;
		/** @brief the previous time */
	Uint64 m_last;
		/** @brief delta time */
	double m_deltaTime;
};

#define TIME MyTime::Instance()