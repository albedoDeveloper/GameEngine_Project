#pragma once
#include "./ThirdParty/imgui/imgui_impl_sdl.h"
#include "./ThirdParty/imgui/imgui_impl_opengl3.h"
#include "GameObject.h"
#include <SDL2/SDL.h>
#include <string> 

class LevelEditor
{
public:

		/**
		* @brief default constructor
		*/
	LevelEditor();

		/**
		 * @brief Draws the editor to screen
		 *
		 */
	void DrawEditor();

		/**
		 * @brief fills in the object list
		 *
		 */
	void ObjectList();

		/**
		 * @brief Creates the objects header using the current gameobject in the iterator
		 *
		 * \param g pointer to the current gameobject in the iterator
		 */
	void ObjectHeader(GameObject *g);

		/**
		 * @brief displays the gameobjects transform editor
		 *
		 * \param g pointer to the current gameobject in the iterator
		 */
	void TransformHeader(GameObject *g);

		/**
		 * @brief displays the position fields in the transform editor
		 *
		 * \param g pointer to the current gameobject in the iterator
		 */
	void PositionManipulators(GameObject *g);

		/**
		 * @brief displays the (Euler) rotation fields in the transform editor
		 *
		 * \param g pointer to the current gameobject in the iterator
		 */
	void RotationManipulators(GameObject *g);

		/**
		 * @brief displays the scale fields in the transform editor
		 *
		 * \param g pointer to the current gameobject in the iterator
		 */
	void ScaleManipulators(GameObject *g);

		/**
		 * @brief displays the components of the gameobject
		 *
		 * \param g pointer to the current gameobject in the iterator
		 */
	void ComponentTree(GameObject *g);

private:

};
