#pragma once

#include <SDL2/SDL.h>

class DeltaTime
{
public:
	/**
	 * @brief get singleton instance
	*/
	static DeltaTime* Instance();

	/**
	 * @brief call once a frame to update delta time value
	*/
	void UpdateDeltaTime();

	/**
	 * @brief get current delta time
	*/
	double GetDeltaTime();

	float GetTimeElapsed() const;


	/**
	 * @brief default constructor
	*/
	DeltaTime();

private:
	Uint64 NOW;
	Uint64 LAST;
	double deltaTime;
};

#define TIME DeltaTime::Instance()