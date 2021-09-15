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
	static GameObjectFactory* instance();
	/**
	 * @brief closes the factory
	*/
	void Close();

	/**
	 * @brief Accessor for the map of objects created by the factory
	 * @return A pointer to the object Map
	*/
	std::map<std::string, GameObject*>* GetObjectMap();

	/**
	 * @brief Accessor for objects created by the factory
	 * @param key String holding the object's place in the storage map
	 * @return A pointer to the object
	*/
	GameObject* GetGameObject(std::string key);
	/**
	 * @brief searches for the closest object to a given transform with a key containing a given substring
	 * @param target the point from which to search
	 * @param partialKey the substring the found object must contain
	 * @return the closest object with a matching key
	*/
	GameObject* getClosestObject(Transform* target, std::string partialKey);
	/**
	 * @brief returns the number of objects created
	 * @return the number of objects
	*/
	int getNumObjects();

	/**
	 * @brief Creates an object in the object list using an automatically allocated key
	 * @return A pointer to the spawned object
	*/
	GameObject* SpawnGameObject();
	/**
	 * @brief Create an object in the object list using a manually allocated key
	 * @param key The map key for the object to be stored at
	 * @return A pointer to the spawned object, or null if the key is already in use
	*/
	GameObject* SpawnGameObject(std::string key);

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
	void render();
	/**
	 * @brief saves the game
	*/
	void Save(nlohmann::json& j);
	/**
	 * @brief loads the game from saved state
	*/
	void Load(nlohmann::json& j);

private:
	/**
	 * @brief default constructor
	*/
	GameObjectFactory();

	/**
	 * @brief The list of all GameObjects, stored in a map with a string as the key. Objects can be inserted with a chosen key or an automatic key
	*/
	std::map<std::string, GameObject*> objectList;

	/**
	 * @brief A utility function function designed to increment an alphabetic key through combinations of letters
	 * @param key The key to be incremented. Should only have alphabetic characters
	*/
	void iterateKey(std::string& key);
};

#define GAMEOBJECT GameObjectFactory::instance()
