#include "GameAssetFactory.h"
#include <iostream>

GameAssetFactory *GameAssetFactory::Instance()
{
	static GameAssetFactory instance;
	return &instance;
}

void GameAssetFactory::LoadModel(const std::string &key, const std::string &filePath)
{
	if (CheckName(key, AssetType::MODEL))
	{
		std::cout << "[Error] Cannot load model, model name already exists\n";
		return;
	}

	m_modelAssets.emplace(key, AModel(filePath, key));
}

void GameAssetFactory::LoadScript(const std::string &key, const std::string &filePath)
{
	if (CheckName(key, AssetType::SCRIPT))
	{
		std::cout << "Error: Cannot load script, script name already exists\n";
		return;
	}

	m_scriptAssets.emplace(key, AScript(key, filePath));
}

void GameAssetFactory::UnloadTexture(std::string key)
{
	GRAPHICS->DeleteTexture(key);
}

bool GameAssetFactory::CheckName(const std::string &key, AssetType type)
{
	switch (type)
	{
	case AssetType::MODEL:
		return !(m_modelAssets.find(key) == m_modelAssets.end());
		break;
	case AssetType::SCRIPT:
		return !(m_scriptAssets.find(key) == m_scriptAssets.end());
		break;
	}
}

void GameAssetFactory::LoadLuaFile(const std::string &key, const std::string &path)
{
	std::ifstream inFile(path);
	if (!inFile.is_open())
	{
		std::cout << "Could not open the file: '" << path << "'" << std::endl;
	}

	AScript script(key, std::string((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>()));
}

AModel *GameAssetFactory::GetModelAsset(const std::string &key)
{
	try
	{
		return &(m_modelAssets.at(key));
	}
	catch (std::out_of_range e)
	{
		std::cout << "[Error] Cannot find AModel with key: " << key << std::endl;
		return nullptr;
	}
}

AScript *GameAssetFactory::GetScriptAsset(const std::string &key)
{
	try
	{
		return &(m_scriptAssets.at(key));
	}
	catch (std::out_of_range e)
	{
		std::cout << "[Error] Cannot find AScript with key: " << key << std::endl;
		return nullptr;
	}
}
