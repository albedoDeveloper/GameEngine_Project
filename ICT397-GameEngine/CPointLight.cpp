#include "CPointLight.h"

CPointLight::CPointLight(Transform* parent, GameObject* parentObj)
	:Component{ parent, parentObj }, m_colour(1, 0, 0)
{
}

void CPointLight::Start()
{
}

void CPointLight::Update()
{
}

void CPointLight::Render()
{
}

void CPointLight::LateRender()
{
}

void CPointLight::AssignColour(float r, float g, float b)
{
	m_colour = Vector3f(r, g, b);
}
