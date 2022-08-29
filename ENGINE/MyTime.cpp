#include "MyTime.h"
#include <iostream>
#include <algorithm>

MyTime::MyTime()
{
	m_now = SDL_GetPerformanceCounter();
	m_last = 0;
	m_deltaTime = 0;
}

MyTime *MyTime::Instance()
{
	static MyTime instance;
	return &instance;
}

void MyTime::UpdateDeltaTime()
{
	m_last = m_now;
	m_now = SDL_GetPerformanceCounter();

	m_deltaTime = (m_now - m_last) / (double)SDL_GetPerformanceFrequency();
}

void MyTime::CatchupDeltaTime()
{
	m_now = SDL_GetPerformanceCounter();
}

double MyTime::GetDeltaTime()
{
	return m_deltaTime;
}

float MyTime::GetTimeElapsed() const
{
	return SDL_GetPerformanceCounter();
}
