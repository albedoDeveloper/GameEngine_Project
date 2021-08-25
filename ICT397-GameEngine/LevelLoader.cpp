#include "LevelLoader.h"
#include "GameObjectFactory.h"
#include <nlohmann/json.hpp>
#include <filesystem>

#if _DEBUG
#include <iostream>
#endif

using json = nlohmann::json;
namespace fs = std::filesystem;

LevelLoader::LevelLoader() 
{
	objectList = GAMEOBJECT->GetObjectMap();
}

void LevelLoader::Test() 
{

	json j;

	std::cout << j << std::endl;

	std::map<std::string, GameObject*>::iterator it;

	int i = 0;

	for (it = objectList->begin(); it != objectList->end(); it++)
	{
		std::cout << "Object " << i << " Of " << objectList->size() << "\n" <<
			"	 has Key " << it->second->getFactoryKey() << "\n" <<
			"	 Is at position x=" << it->second->GetTransform()->GetPosition().GetX() << "\n" <<
			"	 Is at position y=" << it->second->GetTransform()->GetPosition().GetY() << "\n" <<
			"	 Is at position z=" << it->second->GetTransform()->GetPosition().GetZ() << "\n" <<
			": "<< std::endl;



		i++;
	}

	


	/// FIle pathing and tests
	
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

	///now we need to generate teh JSON

	

	//we need to make this easier
	std::ofstream o("../Assets/SaveFiles/tavern.json");
	o << std::setw(4) << j << std::endl;
	

	

}
