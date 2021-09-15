#pragma once

#include "CComponent.h"

struct PointLight
{
	float ambientStrength;
	Vector3f colour;

	// attenuation
	float constant;
	float linear;
	float quadratic;
};

class CPointLight : public CComponent
{
public:
	CPointLight(Transform* parent, GameObject* parentObj);

	void Update();

	void AssignColour(float r, float g, float b);

	// 0 to 1
	void AssignAmbientStrength(float strength);

	PointLight LightInfo;

	int m_litShaderIndex; // index in the shader array of point lights. TODO make this more robust later
};
