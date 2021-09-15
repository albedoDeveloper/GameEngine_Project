#include "GameAssetFactory.h"
#include <iostream>

GameAssetFactory* GameAssetFactory::Instance()
{
	static GameAssetFactory instance;
	return &instance;
}

void GameAssetFactory::LoadModel(std::string key, std::string filePath)
{
    if (CheckName(key))
    {
        std::cout << "Error: Cannot load model, model name already exists\n";
        return;
    }

     AModel* model = new AModel(filePath,key);
    
     m_assets.emplace(key, model);
   
}

void GameAssetFactory::LoadScript(std::string key, std::string filePath)
{
    if (CheckName(key))
    {
        std::cout << "Error: Cannot load script, script name already exists\n";
        return;
    }

    AScript* script = new AScript(key);

    if (LoadLuaFile(filePath, script))
    {
        m_assets.emplace(key, script);
    }
    else
    {
        std::cout << "Error: there was an error loading script:" << filePath << std::endl;
        delete(script);
    }
}

bool GameAssetFactory::UnloadTexture(std::string key)
{
    if (CheckName(key))
    {
        return false;
    }

    GRAPHICS->DeleteTexture(key);
}

bool GameAssetFactory::LoadHeightMap(std::string key, std::string filePath)
{
   /* if (CheckName(key))
    {
        return false;
    }

    std::ifstream infile(filePath.c_str(), std::ios_base::binary);
    if (!infile)
    {
#if _DEBUG
        std::cout << "LoadHeightMap: cannot open file!\n";
#endif
        return false;
    }

    AHeightMap* heightMap = new AHeightMap(key);

    infile.seekg(0, std::ios::end);
    unsigned length = (unsigned)infile.tellg();
    heightMap->data = new unsigned char[length];

    if (heightMap->data == NULL)
    {
        delete heightMap;
#if _DEBUG
        std::cout << "Failed to create terrain data array!\n";
#endif
        return false;
    }
    infile.seekg(0, std::ios::beg);
    infile.read(reinterpret_cast<char*>(heightMap->data), length);
    infile.close();

    heightMap->size = (unsigned)sqrt(length);

    m_assets.emplace(key, heightMap);

#if _DEBUG
    std::cout << "Height map loaded in. key:" << key << std::endl;
#endif*/

    return true;

}

bool GameAssetFactory::CheckName(std::string name)
{
	return !( m_assets.find(name) == m_assets.end() );
}

//AModel* GameAssetFactory::GetAsset(std::string key)
AAsset* GameAssetFactory::GetAsset(std::string key)
{
#if _DEBUG
    if (m_assets.find(key) == m_assets.end()) 
    {
        std::cout << "Error: Game asset (Key:" << key << ") not found!\n";
    }
#endif

    if (m_assets.find(key) != m_assets.end()) 
    {
        return m_assets.at(key);
    }
    
    return nullptr;
}

bool GameAssetFactory::LoadLuaFile(std::string path, AScript* script)
{
    std::ifstream inFile(path);
    if (!inFile.is_open()) 
    {
#if _DEBUG
        std::cout << "Could not open the file: '" << path << "'" << std::endl;
#endif
        return false;
    }

    script->Script = std::string((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());

    return true;
}

void GameAssetFactory::Close()
{
    //m_assets = *new std::map<std::string, AModel*>();
    m_assets = *new std::map<std::string, AAsset*>();
}
