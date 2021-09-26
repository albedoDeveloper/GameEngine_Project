#include "Time.h"
#include <iostream>
#include <algorithm>

Time::Time()
{
	NOW = SDL_GetPerformanceCounter();
	LAST = 0;
	deltaTime = 0;
}

Time *Time::Instance()
{
	static Time instance;
	return &instance;
}

void Time::UpdateDeltaTime()
{
	LAST = NOW;
	NOW = SDL_GetPerformanceCounter();

	deltaTime = (NOW - LAST) / (double)SDL_GetPerformanceFrequency();
}

void Time::CatchupDeltaTime()
{
	NOW = SDL_GetPerformanceCounter();
}

double Time::GetDeltaTime()
{
	return deltaTime;
}

float Time::GetTimeElapsed() const
{
	return SDL_GetPerformanceCounter();
}
