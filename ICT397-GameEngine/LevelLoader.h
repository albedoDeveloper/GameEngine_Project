#pragma once
#include <map>
#include "GameObject.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;


class LevelLoader
{

private:

	/**
	 * @brief The list of all GameObjects, stored in a map with a string as the key. Objects can be inserted with a chosen key or an automatic key
	*/
	std::map<std::string, GameObject *> *objectList;

public:

	/**
	* @brief default constructor
	*/
	LevelLoader();

	void JsonFilepath();

	void ToJson(json &j, GameObject *g);

	void FromJson(json &j, GameObject *g);



	/**
	* @brief loading test
	*/
	void LoadLevel();

	/**
	* @brief test function
	*/
	void SaveLevel();

};

