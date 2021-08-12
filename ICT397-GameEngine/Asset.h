#pragma once

#include <string>

/**
 * @brief A game asset storing information on a piece of imported game data
*/
struct Asset
{
	/**
	 * @brief The key with which this asset is stored by the asset factory
	*/
	std::string key;

	/**
	 * @brief constructor
	 * @param newKey asset factory storage key
	*/
	Asset(std::string newKey)
		:key{ newKey }
	{
	}
};
