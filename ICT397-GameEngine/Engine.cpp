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
	:m_isRunning{ true }, m_restart{ false }, m_saveState{ false }, m_loadState{false}, levelLoader{ LevelLoader() },
	m_debugMenu{ false }, m_drawColliders{ false }
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
	//GAMEOBJECT->Save();
	levelLoader.SaveLevel();
	//m_saveState = true;
}

void Engine::LoadGame()
{
	//GAMEOBJECT->Load();
	//INPUT->Initialise(this);
	levelLoader.LoadLevel();
}

bool Engine::CheckSaveState()
{
	return m_saveState;
}

bool Engine::OnInit(GraphicsLibrary renderer, int windowWidth, int windowHeight)
{

	COLLISION;
	if (!GRAPHICS->initialise(renderer, windowWidth, windowHeight)) 
	{
		return false;
	}
	

	auto gL_version = glGetString(GL_VERSION);

	std::cout << gL_version << std::endl;

	SCRIPT->Initialise(*this);
	SCRIPT->RunInitScript();

	// temporarily creating player controller here
	// TODO move to level loader class
	GAMEOBJECT->SpawnGameObject("player");
	GAMEOBJECT->GetGameObject("player")->GetTransform()->SetPosition(0, 0, 1);
	GAMEOBJECT->GetGameObject("player")->AddCAABBCollider()->AddBoxCollider(0.2, 0.2, 0.2, false);
	GAMEOBJECT->GetGameObject("player")->AddCCameraComponent()->SetAsCurrentCamera();
	GAMEOBJECT->GetGameObject("player")->AddCCharacter()->SetPlayerControlled(true);

	GAMEOBJECT->Start();
	INPUT->Initialise(this);
	INPUT->LockCursor(true);

	//levelLoader.SaveTest();


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
	if (INPUT->GetKeyDown('`'))
	{
		m_debugMenu = !m_debugMenu;
		if (m_debugMenu)
		{
			INPUT->LockCursor(false);
			GAMEOBJECT->GetGameObject("player")->GetComponent<CCharacter>()->SetMouseEnabled(false);
		}
		else
		{
			INPUT->LockCursor(true);
			GAMEOBJECT->GetGameObject("player")->GetComponent<CCharacter>()->SetMouseEnabled(true);
		}
	}

	if (m_saveState)
		levelLoader.SaveLevel();

	if (m_loadState)
		levelLoader.LoadLevel();

}

void Engine::OnRender()
{
	GRAPHICS->newFrame(m_debugMenu);
	GRAPHICS->renderObjects();

	if (m_debugMenu) // TEST WINDOW
	{
		ImGui::Begin("Debug Menu");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Checkbox("Draw Colliders", &m_drawColliders);      // Edit bools storing our window open/close state
		GRAPHICS->m_drawDebug = m_drawColliders;


		//if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
		//	counter++;
		//ImGui::SameLine();
		//ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		m_saveState = ImGui::Button("Save", ImVec2(100,30));
		m_loadState = ImGui::Button("Load", ImVec2(100,30));


		ImGui::End();
	}

	GRAPHICS->endFrame(m_debugMenu);
}

void Engine::OnCleanup()
{
	SCRIPT->Close();
	GRAPHICS->Close();
}
