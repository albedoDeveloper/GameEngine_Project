#pragma once
#include <SDL2/SDL.h>
#include "GraphicsLibraryEnum.h"

/**
 * @brief A game engine that handles all the backend of a video game and allows for creation of video games with a client program
*/
class Engine
{
private:
	/**
	 * @brief Whether the engine is running
	*/
	bool m_isRunning;
	/**
	 * @brief whether the engine is currently restarting
	*/
	bool m_restart;
	/**
	 * @brief whether the game has been saved
	*/
	bool m_saveState;
public:
	/**
	 * @brief default constructor
	*/
	Engine();

	/**
	 * @brief The main function to execute all behaviour of the game engine
	 * @param renderer - which graphics library you want to be used to render
	 * @return An integer representing program completion status
	*/
	int OnExecute(GraphicsLibrary renderer);
	/**
	 * @brief ends the game
	*/
	void QuitGame();
	/**
	 * @brief starts the game over
	*/
	void RestartGame();
	/**
	 * @brief saves the game
	*/
	void SaveGame();
	/**
	 * @brief loads the game from saved state
	*/
	void LoadGame();
	/**
	 * @brief checks whether there's a saved game
	 * @return save state
	*/
	bool CheckSaveState();

private:
	/**
	 * @brief Intialisation function to set all parts of the engine up
	 * @param renderer - which graphics api you want to be used to render
	 * @return Whether intialisation succeeded
	*/
	bool OnInit(GraphicsLibrary renderer);

	/**
	 * @brief Event handler to be called when an SDL event occurs
	 * @param event The event that occurred
	*/
	void OnEvent(SDL_Event* event);

	/**
	 * @brief Function to be called every iteration of the program and handle ongoing behaviour
	*/
	void OnLoop();

	/**
	 * @brief Function to render all of the visible objects in the program
	*/
	void OnRender();

	/**
	 * @brief Cleans up the program on its conclusion before quitting
	*/
	void OnCleanup();
};
