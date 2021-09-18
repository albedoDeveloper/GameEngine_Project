/*****************************************************************//**
 * \file   GameAssetFactory.h
 * \brief  Creates and handles GameObjects using a map
 * \date   September 2021
 *********************************************************************/
 
#pragma once

#include "ModernOpenGL/AModel.h"
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <sstream>
#include "GraphicsEngine.h"
#include <map>
#include <string>
#include "AScript.h"

/** @brief defines the type of asset */
enum class AssetType
{
	MODEL,
	SCRIPT
};

	/**
	* @brief singleton factory for game assets
	*/
class GameAssetFactory
{
public:
		/**
		* @brief singleton instance generator
		* @return pointer to the instance of the factory
		*/
	static GameAssetFactory *Instance();
		/**
		* @brief loads in a model
		* @param key the storage key for the mode
		* @param filePath the location of the file to load
		*/
	void LoadModel(const std::string &key, const std::string &filePath);
		/**
		* @brief loads in a script
		* @param key the storage key for the script
		* @param filePath the location of the file to load
		*/
	void LoadScript(const std::string &key, const std::string &filePath);

		/**
		* @brief unload a texture from memory
		*/
	void UnloadTexture(std::string key);

		/**
		* @brief cheks whether a storage key already has an asset
		* @param name the key to check
		* @return whether the key is free
		*/
	bool CheckName(const std::string &key, AssetType type);

		/**
		* @brief retrieves a specified model
		*
		* \param key The key to retrieve the model
		* \return
		*/
	AModel *GetModelAsset(const std::string &key);

		/**
		* @brief retrieves a specified script
		*
		* \param key The key to retrieve the script
		* \return
		*/
	AScript *GetScriptAsset(const std::string &key);

private:
		/**
		* enforce singleton
		*/
	GameAssetFactory()
	{};

		/**
		 * @brief loads in a lua file
		 * @param path location of the file
		 * @param script script asset to load it into
		 * @return whether operation succeeded
		*/
	void LoadLuaFile(const std::string &key, const std::string &path);

		/** @brief map of Scripts stored by key */
	std::map<std::string, AScript> m_scriptAssets;
		/** @brief map of models stored by key */
	std::map<std::string, AModel> m_modelAssets;
};

#define ASSET GameAssetFactory::Instance()
