#include "Engine.h"
#include "ScriptingEngine.h"
#include <iostream>
#include "GameObject.h"
#include "GraphicsEngine.h"
#include "InputManager.h"
#include "GameObjectFactory.h"
#include "DeltaTime.h"
#include "./ThirdParty/imgui/imgui_impl_sdl.h"
#include "./ThirdParty/imgui/imgui_impl_opengl3.h"
#include <glm/glm/gtc/matrix_transform.hpp>

Engine::Engine()
	:m_isRunning{ true }, m_saveState{ false }, m_loadState{ false }, levelLoader{ LevelLoader() }, levelEditor{ LevelEditor() },
	m_debugMenu{ false }, m_editMenu{ true }, m_drawColliders{ false }
{
}

Engine *Engine::Instance()
{
	static Engine engine;
	return &engine;
}

int Engine::Execute(GraphicsLibrary renderer, int windowWidth, int windowHeight)
{
	if (OnInit(renderer, windowWidth, windowHeight) == false)
	{
		return -1;
	}

	SDL_Event event;

	while (m_isRunning)
	{
		//must reset inputs before polling next event, otherwise previous events are retained
		INPUT->ResetInputValues();
		TIME->UpdateDeltaTime();

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_WINDOWEVENT)
			{
				switch (event.window.event)
				{
				case SDL_WINDOWEVENT_MOVED:
					TIME->CatchupDeltaTime();
					break;
				case SDL_WINDOWEVENT_RESIZED:
					GRAPHICS->SetViewportToWindowSize();
					break;
				}
			}

			if (m_debugMenu)
			{
				ImGui_ImplSDL2_ProcessEvent(&event);
			}
			OnEvent(&event);
		}

		Update();
		Render();
	}

	Cleanup();

	return 0;
}

void Engine::QuitGame()
{
	m_isRunning = false;
	std::cout << "Hope you enjoyed your stay...\n";
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
	COLLISION->Init();

	if (!GRAPHICS->Init(renderer, windowWidth, windowHeight))
	{
		return false;
	}

	SCRIPT->Initialise();
	SCRIPT->RunInitScript();

	// temporarily creating player controller here
	// TODO move to init
	GAMEOBJECT->GetGameObject("player")->AddCSound()->LoadSound("milkyway.wav");
	GAMEOBJECT->GetGameObject("player")->GetCSound()->PlaySound("milkyway.wav", -1, false);

	GAMEOBJECT->Start();
	INPUT->LockCursor(true);

	return true;
}

void Engine::OnEvent(SDL_Event *e)
{
	switch (e->type)
	{
	case SDL_QUIT:
		m_isRunning = false;
		break;
	}

	INPUT->CheckKey(e);
}

void Engine::Update()
{
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

	if (m_drawColliders)
	{
		// only used to update collider triangles/lines for debugging. deltaTime irrelevant
		COLLISION->physicsWorld->update(1);
	}
}

void Engine::Render()
{
	ShadowMapRenderPass();
	CameraRenderPass();

	if (m_debugMenu) // TEST WINDOW
	{
		ImGui::ShowDemoWindow();

		levelEditor.DrawEditor();

		ImGui::Begin("Debug Menu");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Checkbox("Draw Colliders", &m_drawColliders);      // Edit bools storing our window open/close state
		GRAPHICS->m_drawDebug = m_drawColliders;

		//if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
		//	counter++;
		//ImGui::SameLine();
		//ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		m_saveState = ImGui::Button("Save", ImVec2(100, 30));
		m_loadState = ImGui::Button("Load", ImVec2(100, 30));

		ImGui::End();
	}

	GRAPHICS->endFrame(m_debugMenu);
}

void Engine::Cleanup()
{
	SCRIPT->Close();
	GRAPHICS->Close();
}

void Engine::ShadowMapRenderPass()
{
	GRAPHICS->SetupShadowMapFBO();
	GRAPHICS->m_shadowMapShader->SetMat4Uniform("lightSpaceMatrix", GRAPHICS->GetShadowMapperMatrix());
	GRAPHICS->RenderObjects(*GRAPHICS->m_shadowMapShader);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Engine::CameraRenderPass()
{
	GRAPHICS->m_litShader->Use();
	GRAPHICS->m_litShader->SetMat4Uniform("projection", GRAPHICS->GetCameraProjection());
	GRAPHICS->m_litShader->SetMat4Uniform("view", GRAPHICS->GetCameraView());
	GRAPHICS->m_litShader->SetMat4Uniform("lightSpaceMatrix", GRAPHICS->GetShadowMapperMatrix());
	GRAPHICS->m_litShader->SetFloatUniform("material.shininess", 16); // TODO move somewhere else

	GRAPHICS->m_unlitShader->Use();
	GRAPHICS->m_unlitShader->SetMat4Uniform("projection", GRAPHICS->GetCameraProjection());
	GRAPHICS->m_unlitShader->SetMat4Uniform("view", GRAPHICS->GetCameraView());

	GRAPHICS->m_debugShader->Use();
	GRAPHICS->m_debugShader->SetMat4Uniform("projection", GRAPHICS->GetCameraProjection());
	GRAPHICS->m_debugShader->SetMat4Uniform("view", GRAPHICS->GetCameraView());

	GRAPHICS->UpdateCamViewPos();

	GRAPHICS->SetViewportToWindowSize();
	GRAPHICS->NewFrame(m_debugMenu);
	GRAPHICS->BindDepthMapTexture();
	GRAPHICS->RenderObjects();
}
