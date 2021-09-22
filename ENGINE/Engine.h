/*****************************************************************//**
 * \file   Engine.h
 * \brief  brief the Engine backend
 * \date   September 2021
 *********************************************************************/

#pragma once

#include <SDL2/SDL_events.h>
#include "GraphicsLibraryEnum.h"
#include "LevelLoader.h"
#include "LevelEditor.h"
#include <reactphysics3d/reactphysics3d.h>

	/**
	 * @brief A game engine that handles all the backend of a video game and allows for creation of video games with a client program
	*/
class Engine
{
public:
	static Engine *Instance();

		/**
		 * @brief The main function to execute all behaviour of the game engine
		 * @param renderer - which graphics library you want to be used to render
		 * @return An integer representing program completion status
		*/
	int Execute(GraphicsLibrary renderer, int windowWidth, int windowHeight);

		/**
		 * @brief ends the game
		*/
	void QuitGame();

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
	Engine();

		/**
		 * @brief Intialisation function to set all parts of the engine up
		 * @param renderer - which graphics api you want to be used to render
		 * @return Whether intialisation succeeded
		*/
	bool OnInit(GraphicsLibrary renderer, int windowWidth, int windowHeight);

		/**
		 * @brief Event handler to be called when an SDL event occurs
		 * @param event The event that occurred
		*/
	void OnEvent(SDL_Event *event);

		/**
		 * @brief Function to be called every iteration of the program and handle ongoing behaviour
		*/
	void Update();

		/**
		 * @brief Function to render all of the visible objects in the program
		*/
	void Render();

		/**
		 * @brief Cleans up the program on its conclusion before quitting
		*/
	void Cleanup();

	void CameraRenderPass() const;

		/**
		 * @brief Whether the engine is running
		*/
	bool m_isRunning;

		/**
		 * @brief whether the game has been saved
		*/
	bool m_saveState;

		/**
		 * @brief whether the game needs to be laoded
		*/
	bool m_loadState;

		/**
		* @brief the level loader class
		*/
	LevelLoader levelLoader;

		/**
		* @brief the level editor class
		*/
	LevelEditor levelEditor;


		/** Is the debug menu displayed? */
	bool m_debugMenu;

		/** is edit menu displayed? */
	bool m_editMenu;

		/** are collider boxes being drawn? */
	bool m_drawColliders;
};

#define ENGINE Engine::Instance()
