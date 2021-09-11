#include "GraphicsEngine.h"
#include "GameObjectFactory.h"
#include <iostream>
#include "Color.h"
#include "CCameraComponent.h"
#include "SkyboxVerts.h"
#include "InputManager.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl3.h"


GraphicsEngine::GraphicsEngine()
	:m_window{ nullptr },
	m_renderer{ nullptr },
	m_glContext{ nullptr },
	m_camera{ nullptr },
	m_graphLib{ GraphicsLibrary::OPENGL },
	m_textureIDs{},
	m_skyboxInitialized{ false },
	m_skyboxTextures{},
	m_clear_color{ 0.45f, 0.55f, 0.60f, 1.00f },
	m_imgui_io{},
	m_windowWidth{},
	m_windowHeight{}
{
}

GraphicsEngine* GraphicsEngine::instance() 
{
	static GraphicsEngine* engine = new GraphicsEngine();
	return engine;
}

bool GraphicsEngine::initialise(GraphicsLibrary renderer, int windowWidth, int windowHeight) 
{
	m_windowWidth = windowWidth;
	m_windowHeight = windowHeight;

	switch (renderer)
	{
	case GraphicsLibrary::OPENGL:
		return InitOpenGL(windowWidth, windowHeight);
	case GraphicsLibrary::DIRECTX:
		return InitDirectX();
	default:
		return false;
	}
}

bool GraphicsEngine::initLighting()
{
	glDisable(GL_LIGHTING);
	return true;
}

void GraphicsEngine::newFrame(bool debugMenu) 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	m_firstFrameDebug = true;

	if (debugMenu)
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
	}
}

void GraphicsEngine::UpdateViewPos() const
{
	Vector3f viewPosVec = m_camera->GetTransform().GetWorldTransform().GetPosition();
	GRAPHICS->shader->setVec3(
		"viewPos",
		glm::vec3(
			viewPosVec.GetX(),
			viewPosVec.GetY(),
			viewPosVec.GetZ()
		)
	);
}

int GraphicsEngine::AddPointLight(CPointLight* light)
{
	int numpointLights = m_lightManager.AddPointLight(light);

	shader->useShaderForLoop();
	shader->setShaderInt("numOfPointLights", numpointLights);
	GRAPHICS->shader->setShaderFloat("pointLights[" + std::to_string(numpointLights - 1) + "].ambientStrength", light->LightInfo.ambientStrength);
	GRAPHICS->shader->setVec3("pointLights[" + std::to_string(numpointLights - 1) + "].diffuse", glm::vec3(
		light->LightInfo.diffuseColour.GetX(),
		light->LightInfo.diffuseColour.GetY(),
		light->LightInfo.diffuseColour.GetZ()
	));
	GRAPHICS->shader->setVec3("pointLights[" + std::to_string(numpointLights - 1) + "].specular", glm::vec3(
		light->LightInfo.specularColour.GetX(),
		light->LightInfo.specularColour.GetY(),
		light->LightInfo.specularColour.GetZ()
	));
	GRAPHICS->shader->SetFloat("pointLights[" + std::to_string(numpointLights-1) + "].constant", light->LightInfo.constant);
	GRAPHICS->shader->SetFloat("pointLights[" + std::to_string(numpointLights-1) + "].linear", light->LightInfo.linear);
	GRAPHICS->shader->SetFloat("pointLights[" + std::to_string(numpointLights-1) + "].quadratic", light->LightInfo.quadratic);

	return numpointLights;
}

void GraphicsEngine::renderObjects() 
{
	skybox.DrawSkybox(GetProjection(), GetView());
	GAMEOBJECT->render();

	if (m_drawDebug)
	{
		DrawDebug(GetProjection(), GetView());
	}
}

void GraphicsEngine::endFrame(bool debugMenu) 
{
	if (debugMenu)
	{
		ImGui::Render();
		glViewport(0, 0, (int)m_imgui_io.DisplaySize.x, (int)m_imgui_io.DisplaySize.y);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
	SDL_GL_SwapWindow(m_window);
}

void GraphicsEngine::SetDisplayCamera(CCamera* camera) 
{
	m_camera = camera;
}

CCamera* GraphicsEngine::GetDisplayCamera() 
{
	return m_camera;
}

void GraphicsEngine::GenerateTexture(std::string key, unsigned char* image, int width, int height)
{
	switch (m_graphLib)
	{
	case GraphicsLibrary::OPENGL:
		break;
	case GraphicsLibrary::DIRECTX:
		// out of scope for ICT397
		break;
	}
}

void GraphicsEngine::DeleteTexture(std::string key)
{
	if (m_textureIDs.find(key) == m_textureIDs.end())
	{
		return;
	}

	unsigned int texId[] = { m_textureIDs.at(key) };
	glDeleteTextures(1, texId);
}

void GraphicsEngine::DrawModel(Model* model, const Transform& worldTrans) // NOTE keep these commented out statements, we will need them for texturing
{
	if (!model)
	{
		return;
	}
	
	shader->useShaderForLoop();

	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(worldTrans.GetPosition().GetX(), worldTrans.GetPosition().GetY(), worldTrans.GetPosition().GetZ()));

	trans = trans * glm::mat4_cast(glm::conjugate(
		glm::quat(worldTrans.GetRotation().GetW(), worldTrans.GetRotation().GetX(), worldTrans.GetRotation().GetY(), worldTrans.GetRotation().GetZ())
	));

	trans = glm::scale(trans, glm::vec3(worldTrans.GetScale().GetX(), worldTrans.GetScale().GetY(), worldTrans.GetScale().GetZ()));
	GRAPHICS->shader->setMat4("model", trans);

	model->Draw(*shader);
}

void GraphicsEngine::DrawTerrain()
{
	glCallList(1);
}

void GraphicsEngine::DrawGrid(float gridHeight, float lineThickness, float gridWidth, float cellWidth)
{

}

void GraphicsEngine::DrawImage(std::string key, int width, int height, int posX, int posY)
{

}

unsigned GraphicsEngine::GetTexID(std::string key) const
{
	return m_textureIDs.at(key);
}


void GraphicsEngine::GetScreenSize(int& w, int& h)
{
	int wBuf, hBuf;
	SDL_GetWindowSize(m_window, &wBuf, &hBuf);
	w = wBuf;
	h = hBuf;
}

void GraphicsEngine::InitSkybox(std::string negx, std::string negy, std::string negz, std::string posx, std::string posy, std::string posz)
{

}

void GraphicsEngine::RenderSkybox()
{
}

void GraphicsEngine::Close()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

bool GraphicsEngine::InitOpenGL(int windowWidth, int windowHeight)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

	if ((m_window = SDL_CreateWindow(
		"ICT398 - Game Engine", 
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, 
		windowWidth, windowHeight, 
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN)) == nullptr)
	{
		std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}

	if ((m_glContext = SDL_GL_CreateContext(m_window)) == nullptr)
	{
		std::cout << "OpenGL Context could not be created! SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}

	SDL_WarpMouseInWindow(m_window, windowWidth / 2, windowHeight / 2);
	SDL_GL_MakeCurrent(m_window, m_glContext);
	SDL_GL_SetSwapInterval(0);

	// init imgui
	InitImGui();

	glEnable(GL_MULTISAMPLE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.4, 0.2, 0.7, 1);

	shader = new Shader("../ICT397-GameEngine/ModernOpenGL/vertexShader.vert", "../ICT397-GameEngine/ModernOpenGL/lit.frag");
	debugShader = new Shader("../ICT397-GameEngine/ModernOpenGL/vertexShader.vert", "../ICT397-GameEngine/ModernOpenGL/unlit.frag");
	
	skybox.CreateSkybox(std::vector<std::string>{
		"../Assets/skybox/right.jpg",
		"../Assets/skybox/left.jpg",
		"../Assets/skybox/top.jpg",
		"../Assets/skybox/bottom.jpg",
		"../Assets/skybox/front.jpg",
		"../Assets/skybox/back.jpg"}
	);

	return true;
}

void GraphicsEngine::InitImGui()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	m_imgui_io = ImGui::GetIO(); 
	(void)m_imgui_io;
	ImGui::StyleColorsDark();
	ImGui_ImplSDL2_InitForOpenGL(m_window, m_glContext);
	ImGui_ImplOpenGL3_Init("#version 330 core");
}

bool GraphicsEngine::InitDirectX()
{
	// out of scope for ICT397
	return false;
}

void GraphicsEngine::InitDebug(std::vector <float> &tempVector)
{
	if (!tempVector.empty())
	{
		// create buffers/arrays
		glGenVertexArrays(1, &VAODebug);
		if(VBODebug == 0)
			glGenBuffers(1, &VBODebug);
		glBindVertexArray(VAODebug);
		// load data into vertex buffers
		glBindBuffer(GL_ARRAY_BUFFER, VBODebug);

		glBufferData(GL_ARRAY_BUFFER, sizeof(tempVector.data()[0]) * tempVector.size(), tempVector.data(), GL_DYNAMIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glBindVertexArray(0);

		initDebug = false;
	}
}

void GraphicsEngine::DrawDebug(glm::mat4 projection, glm::mat4 view)
{
	glDisable(GL_CULL_FACE);

	std::vector <float> tempVector;
	
	for (int i = 0; i < COLLISION->debugRender->getNbTriangles(); i++)
	{
		tempVector.emplace_back(COLLISION->debugRender->getTrianglesArray()[i].point1.x);
		tempVector.emplace_back(COLLISION->debugRender->getTrianglesArray()[i].point1.y);
		tempVector.emplace_back(COLLISION->debugRender->getTrianglesArray()[i].point1.z);

		tempVector.emplace_back(COLLISION->debugRender->getTrianglesArray()[i].point2.x);
		tempVector.emplace_back(COLLISION->debugRender->getTrianglesArray()[i].point2.y);
		tempVector.emplace_back(COLLISION->debugRender->getTrianglesArray()[i].point2.z);
					
		tempVector.emplace_back(COLLISION->debugRender->getTrianglesArray()[i].point3.x);
		tempVector.emplace_back(COLLISION->debugRender->getTrianglesArray()[i].point3.y);
		tempVector.emplace_back(COLLISION->debugRender->getTrianglesArray()[i].point3.z);
	}

	if (initDebug)
	{
		InitDebug(tempVector);
	}
	else
	{
		glBufferData(GL_ARRAY_BUFFER, sizeof(tempVector.data()[0]) * tempVector.size(), tempVector.data(), GL_DYNAMIC_DRAW);
	}

	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_BACK, GL_LINE);

	debugShader->useShaderForLoop();

	debugShader->setMat4("projection", projection);

	debugShader->setMat4("view", view);
	
	debugShader->setMat4("model", glm::mat4(1.0f));
	debugShader->setVec4("ourColour", glm::vec4(1, 0, 0, 1));
		
	glBindVertexArray(0);

	glBindVertexArray(VAODebug);
	glDrawArrays(GL_TRIANGLES, 0, COLLISION->physicsWorld->getDebugRenderer().getNbTriangles()*3);
	glBindVertexArray(0);

	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);
	glEnable(GL_CULL_FACE);
	m_firstFrameDebug = false;
}

glm::mat4 GraphicsEngine::GetProjection()
{
	return glm::perspective(
		m_camera->GetCamera().FOV, 
		((float)GRAPHICS->m_windowWidth / GRAPHICS->m_windowHeight), 
		m_camera->GetCamera().NearClip, 
		m_camera->GetCamera().FarClip
	);
}

glm::mat4 GraphicsEngine::GetView()
{
	return glm::lookAt(
		glm::vec3(
			m_camera->GetTransform().GetWorldTransform().GetPosition().GetX(), 
			m_camera->GetTransform().GetWorldTransform().GetPosition().GetY(), 
			m_camera->GetTransform().GetWorldTransform().GetPosition().GetZ()
		),
		glm::vec3(
			m_camera->GetTransform().GetWorldTransform().GetPosition().GetX(), 
			m_camera->GetTransform().GetWorldTransform().GetPosition().GetY(), 
			m_camera->GetTransform().GetWorldTransform().GetPosition().GetZ()) +
				glm::vec3(
					m_camera->GetTransform().GetWorldTransform().GetForward().GetX(), 
					m_camera->GetTransform().GetWorldTransform().GetForward().GetY(), 
					m_camera->GetTransform().GetWorldTransform().GetForward().GetZ()
				),
		glm::vec3(
			m_camera->GetTransform().GetWorldTransform().GetUp().GetX(), 
			m_camera->GetTransform().GetWorldTransform().GetUp().GetY(), 
			m_camera->GetTransform().GetWorldTransform().GetUp().GetZ()
		)
	);
}
