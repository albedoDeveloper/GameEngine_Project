#include "LevelLoader.h"
#include "GameObjectFactory.h"
#include <nlohmann/json.hpp>
#include <filesystem>

#if _DEBUG
#include <iostream>
#include "Transform.h"
#endif

using json = nlohmann::json;
namespace fs = std::filesystem;


struct testGameObject 
{
	std::string key;
	Transform transform;

};


void LevelLoader::ToJson(json& j, GameObject* g) 
{
	j[g->getFactoryKey()] = json({ { "key",g->getFactoryKey() },
										{"position x",g->GetTransform()->GetPosition().GetX()},
										{"position y",g->GetTransform()->GetPosition().GetY()},
										{"position z",g->GetTransform()->GetPosition().GetZ()}, });
}

LevelLoader::LevelLoader() 
{
	objectList = GAMEOBJECT->GetObjectMap();
}


void LevelLoader::Test() 
{
	// Step 1 make json
	json j;

	//std::cout << j << std::endl;


	/// Step 2 FIle pathing and tests
	
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

	///Step 3 now we need to generate teh JSON
	//we need to make this easier
	std::ofstream o("../Assets/SaveFiles/tavern.json");
	


	//Step 4 populate the json with gameobject data

	

	// retrieve and populate map
	std::map<std::string, GameObject*>::iterator it;

	int i = 0;

	for (it = objectList->begin(); it != objectList->end(); it++)
	{
		std::cout << "Object " << i << " Of " << objectList->size() << "\n" <<
			"	 has Key " << it->second->getFactoryKey() << "\n" <<
			"	 Is at position x=" << it->second->GetTransform()->GetPosition().GetX() << "\n" <<
			"	 Is at position y=" << it->second->GetTransform()->GetPosition().GetY() << "\n" <<
			"	 Is at position z=" << it->second->GetTransform()->GetPosition().GetZ() << "\n" <<
			": " << std::endl;

		//we write each gameobject to JSON
		ToJson(j, it->second);

		i++;
	}

	//Step 5 save json to file
	o << std::setw(4) << j << std::endl;
	

	
	

	

}
