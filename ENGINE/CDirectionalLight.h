/*****************************************************************//**
 * \file   CDirectionalLight.h
 * \brief  Directional Light Component
 *
 * \date   November 2021
 *********************************************************************/
#pragma once

#include "CComponent.h"

	/**
	* @brief Directional light component class
	*/
class CDirectionalLight : public CComponent
{
public:
		/**
		 * Constructor.
		 *
		 * \param parentTrans parent transform
		 * \param parentObject parent object
		 */
	CDirectionalLight(Transform *parentTrans, GameObject *parentObject);

		/**
		 * Assign colour, value should be between 0 and 1.
		 *
		 * \param r red
		 * \param g green
		 * \param b blue
		 */
	void AssignColour(float r, float g, float b);

		/**
		 * Assign ambient strength.
		 */
	void AssignAmbientStrength(float strength);

		/**
		 * Assign light direction vector.
		 */
	void AssignDirection(float x, float y, float z);

		/**
		 * get colour of light.
		 */
	const Vector3f &GetColour() const;

		/**
		 * Get ambient strength
		 */
	float GetAmbientStrength() const;

		/**
		 * get direction vector of light.
		 */
	const Vector3f &GetDirection() const;

private:
		/// @brief light colour
	Vector3f m_colour;

		/// @brief ambient strength multiplier
	float m_ambientStrength;

		/// @brief light direction vector
	Vector3f m_direction;

		/// @brief enforce only one direcitonal light in scene
	static bool m_constructed;
};
