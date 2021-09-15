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
	static GameAssetFactory* Instance();
	/**
	 * @brief loads in a model
	 * @param key the storage key for the mode
	 * @param filePath the location of the file to load
	*/
	void LoadModel(std::string key, std::string filePath);
	/**
	 * @brief loads in a script
	 * @param key the storage key for the script
	 * @param filePath the location of the file to load
	*/
	void LoadScript(std::string key, std::string filePath);

	/**
	 * @brief unload a texture from memory
	*/
	bool UnloadTexture(std::string key);

	/**
	 * @brief loads in a heightmap
	 * @param key the storage key for the heightmap
	 * @param filePath the location of the file to load
	*/
	bool LoadHeightMap(std::string key, std::string filePath);
	/**
	 * @brief cheks whether a storage key already has an asset
	 * @param name the key to check
	 * @return whether the key is free
	*/
	bool CheckName(std::string key); // check if name/id already taken
	/**
	 * @brief asset accessor
	 * @param key the key at which the asset is stored
	 * @return pointer to the asset
	*/
	//AModel* GetAsset(std::string key);
	AAsset* GetAsset(std::string key);
	/**
	 * @brief closes the factory
	*/
	void Close();

private:
	/**
	 * @brief loads in a lua file
	 * @param path location of the file
	 * @param script script asset to load it into
	 * @return whether operation succeeded
	*/
	bool LoadLuaFile(std::string path, AScript* script);
	/**
	 * @brief map of assets, stored by string key
	*/
	std::map<std::string, AAsset*> m_assets;
	//std::map <std::string, Amodel*> m_assets;
		
	bool oneTimeShader = false;
};

#define ASSET GameAssetFactory::Instance()
