#pragma once
#include <map>
#include "GameObject.h"

class LevelLoader
{
	//Member variables
	private:
		
		/**
		 * @brief The list of all GameObjects, stored in a map with a string as the key. Objects can be inserted with a chosen key or an automatic key
		*/
		std::map<std::string, GameObject*>* objectList;

	public:

		/**
		* @brief default constructor
		*/
		LevelLoader();


		/**
		* @brief test function
		*/
		void Test();

};

