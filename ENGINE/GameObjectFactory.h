/*****************************************************************//**
 * \file   GameObjectFactory.h
 * \brief  A singleton factory class to produce all GameObjects, store them in memory, and allow access to them
 * \date   September 2021
 *********************************************************************/
#pragma once
#include "GameObject.h"
#include <map>
#include <string>
#include <nlohmann/json.hpp>


	/**
	 * @brief A singleton factory class to produce all GameObjects, store them in memory, and allow access to them
	*/
class GameObjectFactory
{
public:

		/**
		 * @brief Returns an instance of this singleton for consistent access across disconnected classes
		 * @return A pointer to the factory
		*/
	static GameObjectFactory *instance();

		/**
		 * @brief closes the factory
		*/
	void Close();

		/**
		 * @brief deletes all gameobjects in level
		 */
	void ClearCurrentLevel();

		/**
		 * @brief Accessor for the map of objects created by the factory
		 * @return A pointer to the object Map
		*/
	std::map<std::string, GameObject *> *GetObjectMap();

		/**
		 * @brief Accessor for objects created by the factory
		 * @param key String holding the object's place in the storage map
		 * @return A pointer to the object
		*/
	GameObject *GetGameObject(std::string key);

		/**
		 * @brief returns the number of objects created
		 * @return the number of objects
		*/
	int getNumObjects();

		/**
		 * @brief searches for gameobject with key
		 *
		 * \param key to search for
		 * \return if key exists
		 */
	bool CheckKey(const std::string &key);

		/**
		 * @brief Creates an object in the object list using an automatically allocated key
		 * @return A pointer to the spawned object
		*/
	GameObject *SpawnGameObject();

		/**
		 * @brief Create an object in the object list using a manually allocated key
		 * @param key The map key for the object to be stored at
		 * @return A pointer to the spawned object, or null if the key is already in use
		*/
	GameObject *SpawnGameObject(std::string key);

		/**
		 * @brief calls the start function of each object in storage
		*/
	void Start();

		/**
		 * @brief Calls the update function of each object in storage
		*/
	void Update();

		/**
		 * @brief Calls the render function of each GameObject in storage
		*/
	void Render();

	void Render(Shader &shaderOveride);

		/**
		 * @brief saves the game
		*/
	void Save(nlohmann::json &j);

		/**
		 * @brief loads the game from saved state
		*/
	void Load(nlohmann::json &j);

private:
		/**
		 * @brief default constructor
		*/
	GameObjectFactory();

		/**
		 * @brief The list of all GameObjects, stored in a map with a string as the key. Objects can be inserted with a chosen key or an automatic key
		*/
	std::map<std::string, GameObject *> m_objects;

		/**
		 * @brief A utility function function designed to increment an alphabetic key through combinations of letters
		 * @param key The key to be incremented. Should only have alphabetic characters
		*/
	void iterateKey(std::string &key);
};

#define GAMEOBJECT GameObjectFactory::instance()