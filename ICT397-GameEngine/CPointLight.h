/*****************************************************************//**
 * \file   CPointLight.h
 * \brief  Creates a point light over the parent gameObject
 *
 * \date   September 2021
 *********************************************************************/
#pragma once

#include "CComponent.h"

	/**
	 * @brief This struct is made to be used only by this poitn light
	*/
struct PointLight
{
	/** @brief light strength */
	float ambientStrength;

	/** @brief colour RGB values */
	Vector3f colour;

	// attenuation
	/** @brief constant attentuation */
	float constant;
	/** @brief linear attentuation */
	float linear;
	/** @brief quadratic attentuation */
	float quadratic;
};

	/**
	* @brief Point light component class
	*/
class CPointLight : public CComponent
{
public:
		/**
		* @brief default constructor taking parent as argument
		* @param parent pointer to parent transform for this component's transform
		* @param parentObj pointer to parent object of this component
		*/
	CPointLight(Transform *parent, GameObject *parentObj);

		/**
		* @brief updates ongoing behaviour for the component
		*
		*/
	void Update();

		/**
		* @brief Assigns RGB colour values
		*
		* \param r red
		* \param g green
		* \param b blue
		*/
	void AssignColour(float r, float g, float b);

		/**
		* @brief Changes light strength 0-1
		*
		* \param strength 0 to 1
		*/
	void AssignAmbientStrength(float strength);

		/** @brief Light Struct */
	PointLight LightInfo;

		/**
		* @brief index in the shader array of point lights. TODO make this more robust later
		*/
	int m_litShaderIndex; // index in the shader array of point lights. TODO make this more robust later
};
