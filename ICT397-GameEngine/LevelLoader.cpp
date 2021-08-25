#include "LevelLoader.h"
#include "GameObjectFactory.h"

#if _DEBUG
#include <iostream>
#endif

LevelLoader::LevelLoader() 
{
	objectList = GAMEOBJECT->GetObjectMap();
}

void LevelLoader::Test() 
{

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
	

	

}
