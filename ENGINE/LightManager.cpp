#include "LightManager.h"
#include "GraphicsEngine.h"

LightManager::LightManager()
	:m_pointLights{}
{}

int LightManager::AddPointLight(CPointLight *light)
{
	m_pointLights.push_back(light);
	return (int)m_pointLights.size();
}

unsigned LightManager::NumPointLights() const
{
	return m_pointLights.size();
}

CPointLight &LightManager::GetPointLight(unsigned index)
{
	assert(index < m_pointLights.size());
	return *(m_pointLights[index]);
}