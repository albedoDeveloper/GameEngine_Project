#pragma once

#include "Component.h"

struct PointLight
{
	Vector3f ambientColour;
	Vector3f diffuseColour;
	Vector3f specularColour;

	// attenuation
	float constant;
	float linear;
	float quadratic;
};

class CPointLight : public Component
{
public:
	CPointLight(Transform* parent, GameObject* parentObj);

	void Update();

	PointLight LightInfo;

	int m_shaderIndex; // index in the shader array of point lights. TODO make this more robust later
};
