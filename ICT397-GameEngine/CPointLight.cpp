#include "CPointLight.h"
#include "GraphicsEngine.h"

CPointLight::CPointLight(Transform* parent, GameObject* parentObj)
	:Component{ parent, parentObj },
	LightInfo{}
{
	LightInfo.ambientStrength = 0.2f;
	LightInfo.colour = Vector3f(0.8f, 0.8f, 0.8f);
	LightInfo.constant = 1;
	LightInfo.linear = 0.09f;
	LightInfo.quadratic = 0.032f;
	m_shaderIndex = GRAPHICS->AddPointLight(this) - 1;
}

void CPointLight::Update()
{
	Vector3f worldPos = m_transform.GetWorldTransform().GetPosition();
	GRAPHICS->m_shader->use();
	GRAPHICS->m_shader->setVec3("pointLights[" + std::to_string(m_shaderIndex) + "].position", glm::vec3(
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
	GRAPHICS->m_shader->use();
	GRAPHICS->m_shader->setVec3("pointLights[" + std::to_string(m_shaderIndex) + "].colour", glm::vec3(
		r,
		g,
		b
	));
}

void CPointLight::AssignAmbientStrength(float strength)
{
	LightInfo.ambientStrength = strength;
	GRAPHICS->m_shader->use();
	GRAPHICS->m_shader->setShaderInt("pointLights[" + std::to_string(m_shaderIndex) + "].ambientStrength", strength);
}
