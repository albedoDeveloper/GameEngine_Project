#include "Engine.h"
#include "ScriptingEngine.h"
#include <iostream>
#include "GameObject.h"
#include "GraphicsEngine.h"
#include "InputManager.h"
#include "GameObjectFactory.h"
#include "DeltaTime.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl3.h"

Engine::Engine()
	:m_isRunning{ true }, m_restart{ false }, m_saveState{ false },
	m_debugMenu{ false }
{
}

int Engine::OnExecute(GraphicsLibrary renderer, int windowWidth, int windowHeight)
{
	if (OnInit(renderer, windowWidth, windowHeight) == false)
	{
		return -1;
	}

	SDL_Event event;
	DeltaTime delta;

	while (m_isRunning)
	{
		//std::cout << delta.GetDeltaTime() << std::endl;
		//must reset inputs before polling next event, otherwise previous events are retained
		INPUT->ResetInputValues();

		while (SDL_PollEvent(&event))
		{
			if (m_debugMenu)
			{
				ImGui_ImplSDL2_ProcessEvent(&event);
			}
			OnEvent(&event);
		}

		OnLoop();
		OnRender();
		if (m_restart)
		{
			OnCleanup();
			OnInit(renderer, windowWidth, windowHeight);
			m_restart = false;
		}
	}

	OnCleanup();

	return 0;
}

void Engine::QuitGame()
{
	m_isRunning = false;
}

void Engine::RestartGame()
{
	GAMEOBJECT->Restart();
	INPUT->Initialise(this);
}

void Engine::SaveGame()
{
	GAMEOBJECT->Save();
	m_saveState = true;
}

void Engine::LoadGame()
{
	GAMEOBJECT->Load();
	INPUT->Initialise(this);
}

bool Engine::CheckSaveState()
{
	return m_saveState;
}

bool Engine::OnInit(GraphicsLibrary renderer, int windowWidth, int windowHeight)
{
	
	if (!GRAPHICS->initialise(renderer, windowWidth, windowHeight)) {
		return false;
	}
	
	SCRIPT->Initialise(*this);
	SCRIPT->RunInitScript();

	// temporarily creating player controller here
	// TODO move to level loader class
	GAMEOBJECT->SpawnGameObject("player");
	GAMEOBJECT->GetGameObject("player")->GetTransform();
	GAMEOBJECT->GetGameObject("player")->AddCCameraComponent()->SetAsCurrentCamera();
	GAMEOBJECT->GetGameObject("player")->AddCCharacter()->SetPlayerControlled(true);

	GAMEOBJECT->Start();
	INPUT->Initialise(this);
	INPUT->LockCursor(true);


	return true;
}

void Engine::OnEvent(SDL_Event* e)
{
	switch (e->type)
	{
	case SDL_QUIT:
		m_isRunning = false;
		break;
	}

	INPUT->CheckKey(e);
}

void Engine::OnLoop()
{
	TIME->UpdateDeltaTime();
	GAMEOBJECT->Update();
}

void Engine::OnRender()
{
	GRAPHICS->newFrame(m_debugMenu);
	GRAPHICS->renderObjects();

	if (m_debugMenu)
	{
		static float f = 0.0f;
		static int counter = 0;
		bool show_demo_window, show_another_window;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
		ImGui::Checkbox("Another Window", &show_another_window);

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	GRAPHICS->endFrame(m_debugMenu);
}

void Engine::OnCleanup()
{
	SCRIPT->Close();
	GRAPHICS->Close();
}

