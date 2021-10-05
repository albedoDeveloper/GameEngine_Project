#include "LevelLoader.h"
#include "GameObjectFactory.h"
#include <nlohmann/json.hpp>
#include <filesystem>
#include <iostream>
#if _DEBUG
#include "Transform.h"
#endif

using json = nlohmann::json;
namespace fs = std::filesystem;


LevelLoader::LevelLoader()
{
	m_objects = GAMEOBJECT->GetObjectMap();
}

void LevelLoader::JsonFilepath()
{

	fs::path myPath = fs::current_path();

	fs::path newPath = (myPath /= "../Assets//SaveFiles");

	std::cout << newPath << std::endl;

	if (fs::create_directories(newPath))
	{
		std::cout << "SUCCESS" << std::endl;
	}

	if (!fs::is_directory("../Assets//SaveFiles") || !fs::exists("../Assets//SaveFiles"))
	{
		std::cout << "File doesn't exist" << std::endl;
	}

	//////end file pathing

}

void LevelLoader::LoadLevel()
{
	//Step 1 read filestream into json object
		//first we check if files exists
	if (!fs::exists("../Assets//SaveFiles/tavern.json"))
	{
		std::cout << "FAILURE TO READ FILE" << std::endl;
	}
	else
	{

		std::ifstream ifs("../Assets/SaveFiles/tavern.json");
		json j = json::parse(ifs);

		//std::cout << j << std::endl;

		//Step 1.5 Delete Current level

		GAMEOBJECT->ClearCurrentLevel();


		//Step 2 generate and populate map
		std::map<std::string, GameObject *>::iterator it;

		int i = 0;

		std::cout << "Loading level" << std::endl;

		//Step 3
		//This is the more robust method
		//We test for how many objects there are 
		int numOfObjects = j.size();
		std::cout << "NUM OF OBJECT == " << numOfObjects << std::endl;

		for (auto it : j.items())
		{
			//std::cout << "TEST " << j.at(el.key()).at("key") << std::endl;
			//std::cout << "TEST " << j.at(el.key()).at("Position").at("x") << std::endl;

			GameObject *go = GAMEOBJECT->SpawnGameObject(j.at(it.key()).at("key"));

			//go->Load(j);
		}

		//this iterator only works if we already have all objects in GO factory
			//need a more robust method
		for (it = m_objects->begin(); it != m_objects->end(); it++)
		{
			//we read each gameobject from JSON
			it->second->Load(j);
			//FromJson(j, it->second);

		}
	}
}

void LevelLoader::SaveLevel()
{
	// Step 1 make json
	json j;

	/// Step 2 File pathing and tests
	JsonFilepath();


	///Step 3 now we need to generate the JSON
	//we need to make this universally accessible
	std::ofstream o("../Assets/SaveFiles/tavern.json");


	//Step 4 retrieve and populate Gameobject data
	GAMEOBJECT->Save(j);




	//Step 6 save json to file
	o << std::setw(4) << j << std::endl;

}
