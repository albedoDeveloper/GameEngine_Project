#include "CDirectionalLight.h"
#include "GraphicsEngine.h"

bool CDirectionalLight::m_constructed = false;

CDirectionalLight::CDirectionalLight(Transform *parentTrans, GameObject *parentObject)
	:CComponent{ parentTrans, parentObject },
	m_ambientStrength{ 0.2f },
	m_colour{ 0.8f,0.8f,0.8f },
	m_direction{ -0.2f, -1.0f, -0.3f }
{
	if (m_constructed)
	{
		std::cout << "[Error] CDirectionalLight already exists, there can only be one. This new one will not be used for lighting calculations\n";
	}
	else
	{
		GRAPHICS->AddDirectionalLight(*this);
		m_constructed = true;
		GRAPHICS->m_litShader->SetFloatUniform("dirLight.ambientStrength", m_ambientStrength);
		GRAPHICS->m_litShader->SetVec3Uniform("dirLight.colour", m_colour);
		GRAPHICS->m_litShader->SetVec3Uniform("dirLight.direction", m_direction);
		GRAPHICS->m_litShader->SetBoolUniform("dirLight.isActive", true);
	}
}

void CDirectionalLight::AssignColour(float r, float g, float b)
{
	m_colour = Vector3f(r, g, b);
	GRAPHICS->m_litShader->SetVec3Uniform("dirLight.colour", m_colour);
}

void CDirectionalLight::AssignAmbientStrength(float strength)
{
	m_ambientStrength = strength;
	GRAPHICS->m_litShader->SetFloatUniform("dirLight.ambientStrength", strength);
}

void CDirectionalLight::AssignDirection(float x, float y, float z)
{
	m_direction = Vector3f(x, y, z);
	GRAPHICS->m_litShader->SetVec3Uniform("dirLight.direction", m_direction);
}

const Vector3f &CDirectionalLight::GetColour() const
{
	return m_colour;
}

float CDirectionalLight::GetAmbientStrength() const
{
	return m_ambientStrength;
}

const Vector3f &CDirectionalLight::GetDirection() const
{
	return m_direction;
}
