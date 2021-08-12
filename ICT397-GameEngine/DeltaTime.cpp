#include "DeltaTime.h"
#include <iostream>

DeltaTime::DeltaTime()
{
    NOW = SDL_GetPerformanceCounter();
    LAST = 0;
    deltaTime = 0;
}

DeltaTime* DeltaTime::Instance()
{
    static DeltaTime instance;
    return &instance; 
}


void DeltaTime::UpdateDeltaTime()
{
    LAST = NOW;
    NOW = SDL_GetPerformanceCounter();

    deltaTime = ((double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency()));
}

double DeltaTime::GetDeltaTime()
{
    return deltaTime;
}
