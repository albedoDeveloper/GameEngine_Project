#pragma once

#include "CPointLight.h"
#include <vector>

class LightManager
{
public:
	LightManager();
	int AddPointLight(CPointLight* light);
	void Update();

private:
	std::vector<CPointLight*> m_pointLights;
};
