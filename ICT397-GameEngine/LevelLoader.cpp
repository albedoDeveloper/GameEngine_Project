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


		//Step 2 retrieve and populate map
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


	//STEP 4 CHANGE
	GAMEOBJECT->Save(j);

	//Step 4 retrieve and populate Gameobject data
	//std::map<std::string, GameObject*>::iterator it;

	//int i = 0;

	//for (it = objectList->begin(); it != objectList->end(); it++)
	//{
	//	//console logs, can delete later but useful for now
	//	std::cout << "Object " << i << " Of " << objectList->size() << "\n" <<
	//		"	 has Key " << it->second->getFactoryKey() << "\n" <<
	//		"	 Is at position x=" << it->second->GetTransform()->GetPosition().GetX() << "\n" <<
	//		"	 Is at position y=" << it->second->GetTransform()->GetPosition().GetY() << "\n" <<
	//		"	 Is at position z=" << it->second->GetTransform()->GetPosition().GetZ() << "\n" <<
	//		": " <<
	//		"	 Is at rotation x = "<< it->second->GetTransform()->GetRotation().GetX() << "\n" <<
	//		"	 Is at rotation y = "<< it->second->GetTransform()->GetRotation().GetY() << "\n" <<
	//		"	 Is at rotation z = "<< it->second->GetTransform()->GetRotation().GetZ() << "\n" <<
	//		"	 Is at rotation w = "<< it->second->GetTransform()->GetRotation().GetW() << "\n" <<
	//		": "
	//		"	 has scale x=" << it->second->GetTransform()->GetRelativeScale().GetX() << "\n" <<
	//		"	 has scale y=" << it->second->GetTransform()->GetRelativeScale().GetY() << "\n" <<
	//		"	 has scale z=" << it->second->GetTransform()->GetRelativeScale().GetZ() << "\n" <<
	//		": " << std::endl;

	//	//Step 5 write each gameobject to JSON
	//	ToJson(j, it->second);

	//	i++;
	//}

	//Step 6 save json to file
	o << std::setw(4) << j << std::endl;

}

