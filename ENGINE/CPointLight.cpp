#include "CPointLight.h"
#include "GraphicsEngine.h"
#include "Vector3f.h"

CPointLight::CPointLight(Transform *parent, GameObject *parentObj)
	:CComponent{ parent, parentObj }, m_litShaderIndex{}, m_attenConstant{ 1 }, m_attenLinear{ 0.09f }, m_attenQuad{ 0.032f },
	m_colour{ 0.8f,0.8f,0.8f }, m_ambientStrength{ 0.2f }
{
	m_litShaderIndex = GRAPHICS->AddPointLight(this) - 1;
	GRAPHICS->m_litShader->SetFloatUniform("pointLights[" + std::to_string(m_litShaderIndex) + "].ambientStrength", m_ambientStrength);
	GRAPHICS->m_litShader->SetFloatUniform("pointLights[" + std::to_string(m_litShaderIndex) + "].constant", m_attenConstant);
	GRAPHICS->m_litShader->SetFloatUniform("pointLights[" + std::to_string(m_litShaderIndex) + "].linear", m_attenLinear);
	GRAPHICS->m_litShader->SetFloatUniform("pointLights[" + std::to_string(m_litShaderIndex) + "].quadratic", m_attenQuad);
	GRAPHICS->m_litShader->SetVec3Uniform("pointLights[" + std::to_string(m_litShaderIndex) + "].colour", m_colour);
	GRAPHICS->m_litShader->SetVec3Uniform("pointLights[" + std::to_string(m_litShaderIndex) + "].position", m_transform.GetWorldTransform().GetRelativePosition());
}

void CPointLight::Update()
{
	Vector3f worldPos = m_transform.GetWorldTransform().GetRelativePosition();
	GRAPHICS->m_litShader->SetVec3Uniform("pointLights[" + std::to_string(m_litShaderIndex) + "].position", Vector3f(
		worldPos.GetX(),
		worldPos.GetY(),
		worldPos.GetZ()
	));
}

void CPointLight::AssignColour(float r, float g, float b)
{
	m_colour = Vector3f(r, g, b);
	GRAPHICS->m_litShader->SetVec3Uniform("pointLights[" + std::to_string(m_litShaderIndex) + "].colour", Vector3f(
		r,
		g,
		b
	));
}

void CPointLight::AssignAmbientStrength(float strength)
{
	m_ambientStrength = strength;
	GRAPHICS->m_litShader->SetFloatUniform("pointLights[" + std::to_string(m_litShaderIndex) + "].ambientStrength", m_ambientStrength);
}

const Vector3f &CPointLight::GetColour() const
{
	return m_colour;
}

float CPointLight::GetAmbientStrength() const
{
	return m_ambientStrength;
}

float CPointLight::GetAttenConstant() const
{
	return m_attenConstant;
}

float CPointLight::GetLinearAttenutation() const
{
	return m_attenLinear;
}

float CPointLight::GetQuadraticAttenuation() const
{
	return m_attenQuad;
}
