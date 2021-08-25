#include "Engine.h"
#include "ScriptingEngine.h"
#include <iostream>
#include "GameObject.h"
#include "GraphicsEngine.h"
#include "InputManager.h"
#include "GameObjectFactory.h"
#include "DeltaTime.h"

Engine::Engine()
	:m_isRunning{ true }, m_restart{ false }, m_saveState{ false }
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
	GraphicsEngine::instance()->newFrame();
	GraphicsEngine::instance()->renderObjects();
	GraphicsEngine::instance()->endFrame();
}

void Engine::OnCleanup()
{
	SDL_Quit();
	SCRIPT->Close();
}
