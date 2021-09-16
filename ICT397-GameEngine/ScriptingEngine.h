#pragma once

#include "GameObject.h"
#include <string>
#include <lua/lua.hpp>
#include <LuaBridge/LuaBridge.h>

class Engine;
class InputManager;

/**
 * @brief A singleton that gets information from and manages lua scripts
*/
class ScriptingEngine
{
public:
	/**
	 * @brief Singleton instance getter
	 * @return A pointer to the scripting engine
	*/
	static ScriptingEngine* Instance();

	void Initialise();

	/**
	 * @brief Sets up the engine with initial processes and variables and exposes engine functionality to lua
	*/
	lua_State* NewState();

	/**
	 * @brief Runs the lua scripts to initialise the engine with assets and objects
	*/
	void RunInitScript();
	/**
	 * @brief runs one of an AI script's state behaviours
	 * @param AIscript the AI script where the state is located
	 * @param state the state to run
	 * @param parent the object to which this AI belongs
	*/
	void RunStateFromScript(lua_State* luaState, std::string AIscript, std::string AIstate, GameObject* parent);

	void DoFile(std::string filePath);

	/**
	 * @brief Shuts down lua at program end
	*/
	void Close();

private:
	friend class CScript;

	ScriptingEngine() {}; // enforce singleton

	/**
	 * @brief The lua state the engine will use for lua functionality
	*/
	lua_State* m_L;

	/**
	 * @brief Loads a model into the game engine's asset manager
	 * @param name The name of the model
	 * @param filePath The location of the model in storage
	*/
	static void LoadModel(std::string name, std::string filePath);

	static void UnloadTexture(std::string key);

	/**
	 * @brief Loads a heightmap into the game engine's asset manager
	 * @param key name of the texture
	 * @param filePath location of the texture in storage
	*/
	static void LoadHeightMap(std::string key, std::string filePath);

	/**
	 * @brief Creates a game object using the game object factory
	 * @param key The key for storing the object. Can be any typed string
	*/
	static GameObject* SpawnGameObject(std::string key);

	/**
	 * @brief Loads a lua script into the engine
	 * @param name The name of the script
	 * @param filePath The location of the file
	*/
	static void LoadScript(std::string key, std::string filePath);

	/**
	 * @brief Retrieves a game object from the game objectfactory
	 * @param objectKey The storage key for the object
	 * @return a pointer to the desired object
	*/
	static GameObject* GetGameObject(std::string objectKey);

	/**
	 * @brief quits the game
	*/
	static void QuitGame();
	/**
	 * @brief saves the game
	*/
	static void SaveGame();
	/**
	 * @brief loads the game from saved state
	*/
	static void LoadGame();
	/**
	 * @brief checks whether there's a saved game
	 * @return save state
	*/
	static bool CheckSaveState();

	static InputManager* GetInputManager();
};

#define SCRIPT ScriptingEngine::Instance()
