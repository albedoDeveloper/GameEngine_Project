/*****************************************************************//**
 * \file   CDirectionalLight.h
 * \brief  Directional Light Component
 *
 * \date   September 2021
 *********************************************************************/
#pragma once

#include "CComponent.h"

	/**
	* @brief Directional light component class
	*/
class CDirectionalLight : public CComponent
{
public:
	CDirectionalLight(Transform *parentTrans, GameObject *parentObject);

	void AssignColour(float r, float g, float b);

	void AssignAmbientStrength(float strength);

	void AssignDirection(float x, float y, float z);

	const Vector3f &GetColour() const;

	float GetAmbientStrength() const;

	const Vector3f &GetDirection() const;

private:
	Vector3f m_colour;
	float m_ambientStrength;
	Vector3f m_direction;
	static bool m_constructed;
};
