#include "LightManager.h"
#include "GraphicsEngine.h"

LightManager::LightManager()
	:m_pointLights{}
{
}

int LightManager::AddPointLight(CPointLight* light)
{
	m_pointLights.push_back(light);
	return (int)m_pointLights.size();
}
	

void LightManager::Update()
{

}
