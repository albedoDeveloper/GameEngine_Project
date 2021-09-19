/*****************************************************************//**
 * \file   CPointLight.h
 * \brief  Point Light Component
 *
 * \date   September 2021
 *********************************************************************/
#pragma once

#include "CComponent.h"

	/**
	* @brief Point light component class
	*/
class CPointLight : public CComponent
{
public:
	CPointLight(Transform *parentTrans, GameObject *parentObject);

	void Update();

	void AssignColour(float r, float g, float b);

	void AssignAmbientStrength(float strength);

	const Vector3f &GetColour() const;

	float GetAmbientStrength() const;

		/**
		 * \return get the lights attenuation constant.
		 */
	float GetAttenConstant() const;

		/**
		 * \return linear attenuation value
		 */
	float GetLinearAttenutation() const;

		/**
		 * \return quadtraic attenuation value
		 */
	float GetQuadraticAttenuation() const;

private:
	Vector3f m_colour;
	float m_ambientStrength;
	float m_attenConstant;
	float m_attenLinear;
	float m_attenQuad;
	int m_litShaderIndex;
};
