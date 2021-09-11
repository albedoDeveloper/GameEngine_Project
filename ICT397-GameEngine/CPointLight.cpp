#include "CPointLight.h"
#include "GraphicsEngine.h"

CPointLight::CPointLight(Transform* parent, GameObject* parentObj)
	:Component{ parent, parentObj },
	LightInfo{}
{
	LightInfo.ambient = 0.2f;
	LightInfo.diffuseColour = Vector3f(0.8f, 0.8f, 0.8f);
	LightInfo.specularColour = Vector3f(1, 1, 1);
	LightInfo.constant = 1;
	LightInfo.linear = 0.09f;
	LightInfo.quadratic = 0.032f;
	m_shaderIndex = GRAPHICS->AddPointLight(this) - 1;
}

void CPointLight::Update()
{
	Vector3f worldPos = m_transform.GetWorldTransform().GetPosition();
	GRAPHICS->shader->setVec3("pointLights[" + std::to_string(m_shaderIndex) + "].position", glm::vec3(
		worldPos.GetX(),
		worldPos.GetY(),
		worldPos.GetZ()
	));
}

void CPointLight::AssignColour(float r, float g, float b)
{
	LightInfo.diffuseColour.SetX(r);
	LightInfo.diffuseColour.SetY(g);
	LightInfo.diffuseColour.SetZ(b);
}

void CPointLight::AssignAmbientStrength(float strength)
{
	LightInfo.ambient = strength;
}
