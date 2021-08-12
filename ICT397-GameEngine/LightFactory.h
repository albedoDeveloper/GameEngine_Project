#pragma once
#include <map>
#include <string>
#include "Component.h"
#include "CSpotlight.h"

/**
 * @brief A factory storing all light components in the scene for access by the graphics engine
*/
class LightFactory
{
private:
	/**
	 * @brief the list of lights, stored by key
	*/
	std::map<std::string, CSpotlight*> spotlightList;

	/**
	 * @brief A utility function function designed to increment an alphabetic key through combinations of letters
	 * @param key The key to be incremented. Should only have alphabetic characters
	*/
	void iterateKey(std::string& key);
public:
	/**
	 * @brief default constructor
	*/
	LightFactory();
	/**
	 * @brief Returns an instance of this singleton for consistent access across disconnected classes
	 * @return A pointer to the factory
	*/
	static LightFactory* instance();
	/**
	 * @brief Accessor for lights created by the factory
	 * @param key String holding the lights's place in the storage map
	 * @return A pointer to the light
	*/
	CSpotlight* GetSpotlight(std::string key);
	/**
	 * @brief finds the closest spotlight to a given transform
	 * @param position the transform to find a spotlight near
	 * @return pointer to the closest spotlight
	*/
	CSpotlight* GetClosestSpotlight(const Transform* position);

	/**
	 * @brief Creates a light in the light list using an automatically allocated key
	 * @return A pointer to the spawned light
	*/
	CSpotlight* AddSpotlight(CSpotlight* light);
	/**
	 * @brief Creates a light in the light list using a manually allocated key
	 * @param key The map key for the light to be stored at
	 * @return A pointer to the spawned light, or null if the key is already in use
	*/
	CSpotlight* AddSpotlight(CSpotlight* light, std::string key);
};

#define LIGHTS LightFactory::instance()