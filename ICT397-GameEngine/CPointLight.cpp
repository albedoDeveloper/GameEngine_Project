#include "CPointLight.h"
#include "GraphicsEngine.h"
#include "Vector3f.h"

CPointLight::CPointLight(Transform *parent, GameObject *parentObj)
	:CComponent{ parent, parentObj },
	LightInfo{}
{
	LightInfo.ambientStrength = 0.2f;
	LightInfo.colour = Vector3f(0.8f, 0.8f, 0.8f);
	LightInfo.constant = 1;
	LightInfo.linear = 0.09f;
	LightInfo.quadratic = 0.032f;
	m_litShaderIndex = GRAPHICS->AddPointLight(this) - 1;
}

void CPointLight::Update()
{
	Vector3f worldPos = m_transform.GetWorldTransform().GetRelativePosition();
	GRAPHICS->m_litShader->Use();
	GRAPHICS->m_litShader->SetVec3("pointLights[" + std::to_string(m_litShaderIndex) + "].position", Vector3f(
		worldPos.GetX(),
		worldPos.GetY(),
		worldPos.GetZ()
	));
}

void CPointLight::AssignColour(float r, float g, float b)
{
	LightInfo.colour.SetX(r);
	LightInfo.colour.SetY(g);
	LightInfo.colour.SetZ(b);
	GRAPHICS->m_litShader->Use();
	GRAPHICS->m_litShader->SetVec3("pointLights[" + std::to_string(m_litShaderIndex) + "].colour", Vector3f(
		r,
		g,
		b
	));
}

void CPointLight::AssignAmbientStrength(float strength)
{
	LightInfo.ambientStrength = strength;
	GRAPHICS->m_litShader->Use();
	GRAPHICS->m_litShader->SetInt("pointLights[" + std::to_string(m_litShaderIndex) + "].ambientStrength", strength);
}
