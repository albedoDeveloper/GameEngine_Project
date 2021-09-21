/*****************************************************************//**
 * \file   LightManager.h
 *
 * \date   September 2021
 *********************************************************************/

#pragma once

#include "CPointLight.h"
#include <vector>

	/**
	 * this class doesnt seem to make much sense atm, but its planned to be expanded upon, and reduce the complexity of the graphics engine class.
	 */
class LightManager
{
public:
		/**
		 * constructs the light manager with 0 lights.
		 */
	LightManager();

		/**
		 * Add a point light and count the total amount.
		 *
		 * \param light new light to add
		 * \return total number of lights after adding
		 */
	int AddPointLight(CPointLight *light);

	unsigned NumPointLights() const;

private:
		/** list of all lights */
	std::vector<CPointLight *> m_pointLights;
};
