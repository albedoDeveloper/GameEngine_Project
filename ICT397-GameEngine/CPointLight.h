#pragma once

#include "Component.h"

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

	void AssignColour(float r, float g, float b);

private:

	Vector3f m_colour;
};

