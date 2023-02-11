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
		/**
		 * Constructor.
		 */
	CPointLight(Transform *parentTrans, GameObject *parentObject);

		/**
		 * Update shader with light position.
		 */
	void Update();

		/**
		 * set light colour, values from 0 to 1.
		 */
	void AssignColour(float r, float g, float b);

		/**
		 * Assign ambient strength multiplier.
		 *
		 * \param strength
		 */
	void AssignAmbientStrength(float strength);

		/**
		 * Get light colour.
		 */
	const Vector3f &GetColour() const;

		/**
		 * get ambient strength multiplier.
		 */
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
		/// @brief light colour
	Vector3f m_colour;

		/// @brief ambient strength multiplier
	float m_ambientStrength;

		/// @brief attenuation constant
	float m_attenConstant;

		/// @brief linear attenuation value
	float m_attenLinear;

		/// @brief quadratic attenuation value
	float m_attenQuad;

		/// @brief lit shader index
	int m_litShaderIndex;
};
