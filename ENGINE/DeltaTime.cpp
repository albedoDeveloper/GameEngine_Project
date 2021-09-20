#include "DeltaTime.h"
#include <iostream>
#include <algorithm>

DeltaTime::DeltaTime()
{
	NOW = SDL_GetPerformanceCounter();
	LAST = 0;
	deltaTime = 0;
}

DeltaTime *DeltaTime::Instance()
{
	static DeltaTime instance;
	return &instance;
}

void DeltaTime::UpdateDeltaTime()
{
	LAST = NOW;
	NOW = SDL_GetPerformanceCounter();

	deltaTime = (NOW - LAST) / (double)SDL_GetPerformanceFrequency();
}

void DeltaTime::CatchupDeltaTime()
{
	NOW = SDL_GetPerformanceCounter();
}

double DeltaTime::GetDeltaTime()
{
	return deltaTime;
}

float DeltaTime::GetTimeElapsed() const
{
	return SDL_GetPerformanceCounter();
}
