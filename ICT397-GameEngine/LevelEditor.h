#pragma once
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl3.h"
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

		void ObjectHeader(GameObject* g);

		void TransformHeader(GameObject* g);



};

