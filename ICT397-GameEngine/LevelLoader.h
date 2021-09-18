/*****************************************************************//**
 * \file   LevelLoader.h
 * \brief  Save and Load Editor to and from JSON
 *
 * \date   17 September 2021
 *********************************************************************/

#pragma once

#include <map>
#include "GameObject.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class LevelLoader
{
public:
		/**
		* @brief default constructor
		*/
	LevelLoader();

		/**
		* @brief test if the filepath works, if not we create a path
		*
		*/
	void JsonFilepath();

		/**
		* @brief write game data to JSON - DEPRECIATED
		*
		* \param j the json file
		* \param g pointer to the current gameobject
		*/
	void ToJson(json &j, GameObject *g);

		/**
		* @brief Read data from JSON - DEPRECIATED
		*
		* \param j the json file
		* \param g pointer to the current gameobject
		*/
	void FromJson(json &j, GameObject *g);

		/**
		* @brief Load Current Level
		*/
	void LoadLevel();

		/**
		* @brief Save Current Level
		*/
	void SaveLevel();

private:

		/**
		* @brief The list of all GameObjects, stored in a map with a string as the key.
		* Objects can be inserted with a chosen key or an automatic key
		*/
	std::map<std::string, GameObject *> *objectList;
};
