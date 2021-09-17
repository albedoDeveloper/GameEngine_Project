#pragma once
#include "./ThirdParty/imgui/imgui_impl_sdl.h"
#include "./ThirdParty/imgui/imgui_impl_opengl3.h"
#include "GameObject.h"
#include <SDL2/SDL.h>
#include <string> 


class LevelEditor
{
private:

public:
	/**
	* @brief default constructor
	*/
	LevelEditor();

	void DrawEditor();

	void ObjectList();

	void ObjectHeader(GameObject *g);

	void TransformHeader(GameObject *g);

	void PositionManipulators(GameObject *g);

	void RotationManipulators(GameObject *g);

	void ScaleManipulators(GameObject *g);

	void ComponentTree(GameObject *g);
};
