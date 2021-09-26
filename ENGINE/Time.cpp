#include "Time.h"
#include <iostream>
#include <algorithm>

Time::Time()
{
	m_now = SDL_GetPerformanceCounter();
	m_last = 0;
	m_deltaTime = 0;
}

Time *Time::Instance()
{
	static Time instance;
	return &instance;
}

void Time::UpdateDeltaTime()
{
	m_last = m_now;
	m_now = SDL_GetPerformanceCounter();

	m_deltaTime = (m_now - m_last) / (double)SDL_GetPerformanceFrequency();
}

void Time::CatchupDeltaTime()
{
	m_now = SDL_GetPerformanceCounter();
}

double Time::GetDeltaTime()
{
	return m_deltaTime;
}

float Time::GetTimeElapsed() const
{
	return SDL_GetPerformanceCounter();
}
