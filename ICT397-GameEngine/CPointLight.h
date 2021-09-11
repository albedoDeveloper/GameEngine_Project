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

	/**
	 * @brief called at start of game
	*/
	virtual void Start();

	/**
	 * @brief To be called every frame to process the component's behaviour, if any
	*/
	virtual void Update();

	/**
	 * @brief To be called every frame to display the component on the screen, if visible
	*/
	virtual void Render();

	/**
	 * @brief Displays the component after others are displayed
	*/
	virtual void LateRender();

	PointLight LightInfo;

private:

};

