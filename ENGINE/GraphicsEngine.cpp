#include "GraphicsEngine.h"
#include "GameObjectFactory.h"
#include <iostream>
#include "Color.h"
#include "InputManager.h"
#include "./ThirdParty/imgui/imgui.h"
#include "./ThirdParty/imgui/imgui_impl_sdl.h"
#include "./ThirdParty/imgui/imgui_impl_opengl3.h"
#include "Vector3f.h"
#include "Matrix4f.h"
#include "MiscMath.h"
#include "Utility.h"

extern "C"
{
	__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
}

extern "C"
{
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

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
	m_windowHeight{},
	m_litShader{ nullptr },
	m_debugShader{ nullptr },
	m_unlitShader{ nullptr },
	m_dirShadowMapShader{ nullptr },
	m_pointShadowMapShader{ nullptr }
{
}

GraphicsEngine::~GraphicsEngine()
{
	delete m_camera;
	delete m_debugShader;
	delete m_litShader;
	delete m_renderer;
	delete m_unlitShader;
	delete m_window;
}

GraphicsEngine *GraphicsEngine::instance()
{
	static GraphicsEngine *engine = new GraphicsEngine();
	return engine;
}

bool GraphicsEngine::Init(GraphicsLibrary renderer, int windowWidth, int windowHeight)
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

void GraphicsEngine::NewFrame(bool debugMenu)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); CHECK_GL_ERROR();

	if (debugMenu)
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
	}
}

void GraphicsEngine::UpdateCamViewPos() const
{
	Vector3f viewPosVec = m_camera->GetTransform().GetWorldTransform().GetRelativePosition();
	GRAPHICS->m_litShader->SetVec3Uniform(
		"viewPos",
		Vector3f(
			viewPosVec.GetX(),
			viewPosVec.GetY(),
			viewPosVec.GetZ()
		)
	);
}

int GraphicsEngine::AddPointLight(CPointLight *light)
{
	if (!m_shadowMapper.IsInitialised())
	{
		std::cout << "[Error] Cannot add point light because shadow mapper is not initialised\n";
		return m_lightManager.NumPointLights();
	}

	m_shadowMapper.AddPointLight(light);

	int numpointLights = m_lightManager.AddPointLight(light);

	return numpointLights;
}

void GraphicsEngine::AddDirectionalLight(const CDirectionalLight &light)
{
	if (!m_shadowMapper.IsInitialised())
	{
		std::cout << "[Error] Cannot add directional light because shadow mapper is not initialised\n";
		return;
	}

	m_shadowMapper.AssignDirLight(&light);
}

void GraphicsEngine::WarpMouseCentreWindow() const
{
	SDL_WarpMouseInWindow(m_window, m_windowWidth / 2, m_windowHeight / 2);
}

void GraphicsEngine::RenderObjects(Shader &shader, bool noTexture)
{
	GAMEOBJECT->Render(shader, noTexture);
}

void GraphicsEngine::RenderObjects()
{
	skybox.DrawSkybox(GetCameraProjection(), GetCameraView());
	GAMEOBJECT->Render();

	if (m_drawDebug)
	{
		DrawDebug();
	}
}

void GraphicsEngine::SetViewportToWindowSize() const
{
	glViewport(0, 0, m_windowWidth, m_windowHeight); CHECK_GL_ERROR();
}

void GraphicsEngine::endFrame(bool debugMenu)
{
	if (debugMenu)
	{
		ImGui::Render();
		glViewport(0, 0, (int)m_imgui_io.DisplaySize.x, (int)m_imgui_io.DisplaySize.y); CHECK_GL_ERROR();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
	SDL_GL_SwapWindow(m_window);
}

void GraphicsEngine::SetDisplayCamera(CCamera *camera)
{
	m_camera = camera;
	m_litShader->SetMat4Uniform("projection", GRAPHICS->GetCameraProjection());
}

CCamera *GraphicsEngine::GetDisplayCamera()
{
	return m_camera;
}

void GraphicsEngine::GenerateTexture(std::string key, unsigned char *image, int width, int height)
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
	glDeleteTextures(1, texId); CHECK_GL_ERROR();
}

void GraphicsEngine::DrawModel(AModel *model, const Transform &worldTrans, const Shader *shader, bool noTexture)
{
	if (!model)
	{
		return;
	}

	glUseProgram(shader->GetID());
	Matrix4f modelTrans;

	modelTrans.Translate(worldTrans.GetRelativePosition());
	modelTrans *= worldTrans.GetRelativeOrientation().Conjugate().Mat4Cast();
	modelTrans.Scale(worldTrans.GetRelativeScale());

	shader->SetMat4Uniform("model", modelTrans);

	glEnable(GL_CULL_FACE); CHECK_GL_ERROR();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); CHECK_GL_ERROR();

	/*if (noTexture)
	{
		model->DrawNoTexture();
	}*/
	//else
	{
		model->Draw(shader);
	}
}

unsigned GraphicsEngine::GetTexID(std::string key) const
{
	return m_textureIDs.at(key);
}

void GraphicsEngine::GetScreenSize(int &w, int &h)
{
	int wBuf, hBuf;
	SDL_GetWindowSize(m_window, &wBuf, &hBuf);
	w = wBuf;
	h = hBuf;
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
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO) < 0)
	{
		std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

	if ((m_window = SDL_CreateWindow(
		"ICT398 - FrankEngine",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		windowWidth, windowHeight,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS | SDL_WINDOW_ALLOW_HIGHDPI |
		SDL_WINDOW_MOUSE_CAPTURE)) == nullptr)
	{
		std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}

	if ((m_glContext = SDL_GL_CreateContext(m_window)) == nullptr)
	{
		std::cout << "OpenGL Context could not be created! SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}

	gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);

	//SDL_WarpMouseInWindow(m_window, windowWidth / 2, windowHeight / 2);
	SDL_GL_MakeCurrent(m_window, m_glContext);
	SDL_GL_SetSwapInterval(0);

	// init imgui
	InitImGui();

	glEnable(GL_MULTISAMPLE); CHECK_GL_ERROR();
	glEnable(GL_DEPTH_TEST); CHECK_GL_ERROR();
	glEnable(GL_CULL_FACE); CHECK_GL_ERROR();
	glEnable(GL_BLEND); CHECK_GL_ERROR();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); CHECK_GL_ERROR();
	//glEnable(GL_FRAMEBUFFER_SRGB); // gamma correction. looks too washed out
	glClearColor(0.4, 0.2, 0.7, 1); CHECK_GL_ERROR();
	std::cout << glGetString(GL_VENDOR) << " : " << glGetString(GL_RENDERER) << std::endl; CHECK_GL_ERROR();
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl; CHECK_GL_ERROR();
	std::cout << "GLSL Version: " << glGetString(GL_VERSION) << std::endl; CHECK_GL_ERROR();
	//int numUniforms = 0;
	//glGetIntegerv(GL_MAX_UNIFORM_LOCATIONS, &numUniforms); CHECK_GL_ERROR(); // Why is GL_MAX_UNIFORM_LOCATIONS undefined??
	//std::cout << "Max Uniforms: " << numUniforms << std::endl; CHECK_GL_ERROR();

	m_litShader = new Shader("../Assets/Shaders/lit.vert", "../Assets/Shaders/lit.frag");
	m_litShader->SetBoolUniform("pointLights[0].isActive", false);
	m_litShader->SetBoolUniform("pointLights[1].isActive", false);
	m_litShader->SetBoolUniform("dirLight.isActive", false);
	m_litShader->SetFloatUniform("material.shininess", 16);



	m_unlitShader = new Shader("../Assets/Shaders/unlit.vert", "../Assets/Shaders/unlit.frag");
	m_debugShader = new Shader("../Assets/Shaders/debug.vert", "../Assets/Shaders/debug.frag");
	m_dirShadowMapShader = new Shader("../Assets/Shaders/dirShadowMap.vert", "../Assets/Shaders/dirShadowMap.frag");
	m_pointShadowMapShader = new Shader("../Assets/Shaders/pointShadowMap.vert", "../Assets/Shaders/pointShadowMap.geom", "../Assets/Shaders/pointShadowMap.frag");
	m_pointShadowMapShader->SetFloatUniform("far_plane", m_shadowMapper.GetPointLightFarPlane());

	skybox.CreateSkybox(std::vector<std::string>{
		"../Assets/skybox/right.png",
			"../Assets/skybox/left.png",
			"../Assets/skybox/top.png",
			"../Assets/skybox/bottom.png",
			"../Assets/skybox/front.png",
			"../Assets/skybox/back.png"}
	);

	m_shadowMapper.Init();

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
	// out of scope for ICT398
	return false;
}

void GraphicsEngine::InitDebug(std::vector <float> &tempVector)
{
	if (!tempVector.empty())
	{
		// create buffers/arrays
		glGenVertexArrays(1, &VAODebug); CHECK_GL_ERROR();
		if (VBODebug == 0)
		{
			glGenBuffers(1, &VBODebug); CHECK_GL_ERROR();
		}
		glBindVertexArray(VAODebug); CHECK_GL_ERROR();
		// load data into vertex buffers
		glBindBuffer(GL_ARRAY_BUFFER, VBODebug); CHECK_GL_ERROR();

		glBufferData(GL_ARRAY_BUFFER, sizeof(tempVector.data()[0]) * tempVector.size(), tempVector.data(), GL_DYNAMIC_DRAW); CHECK_GL_ERROR();

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0); CHECK_GL_ERROR();
		glEnableVertexAttribArray(0); CHECK_GL_ERROR();
		glBindVertexArray(0); CHECK_GL_ERROR();

		initDebug = false;
	}
}

void GraphicsEngine::DrawDebug()
{
	m_debugShader->Use();

	m_debugShader->SetMat4Uniform("model", Matrix4f());
	m_debugShader->SetVec3Uniform("ourColour", Vector3f(1, 0, 0));

	glDisable(GL_CULL_FACE); CHECK_GL_ERROR();
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); CHECK_GL_ERROR();

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
		glBufferData(GL_ARRAY_BUFFER, sizeof(tempVector.data()[0]) * tempVector.size(), tempVector.data(), GL_DYNAMIC_DRAW); CHECK_GL_ERROR();
	}

	glBindVertexArray(VAODebug); CHECK_GL_ERROR();
	glDrawArrays(GL_TRIANGLES, 0, COLLISION->physicsWorld->getDebugRenderer().getNbTriangles() * 3); CHECK_GL_ERROR();
	glBindVertexArray(0); CHECK_GL_ERROR();


	//now draw the navmesh
	//DrawDebugNavMesh();
}

void GraphicsEngine::DrawDebugNavMesh(CNavMesh *navMesh,const Transform &worldTrans)
{
	
	

	glDisable(GL_CULL_FACE); CHECK_GL_ERROR();
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); CHECK_GL_ERROR();
	
	std::vector<float> combinedVertices = DrawCube(worldTrans, Colour::blue);
	
	int i = 0;
	for (auto it : navMesh->GetNavNodes())
	{
		i++;


		//colour change here, cache current colour

		std::vector<float> nodeVertices = DrawCube(it->GetTransform()->GetWorldTransform(), Colour::green);

		combinedVertices.insert(combinedVertices.end(), nodeVertices.begin(), nodeVertices.end());



	}

	

	/*for (size_t i = 0; i < combinedVertices.size(); i++)
	{
		std::cout << "Vertice "<< i << " at pos = " << combinedVertices[i] << std::endl;
	}*/
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(combinedVertices.data()[0]) * combinedVertices.size(), combinedVertices.data(), GL_DYNAMIC_DRAW); CHECK_GL_ERROR();

	glBindVertexArray(VAODebug); CHECK_GL_ERROR();
	glDrawArrays(GL_TRIANGLES, 0, 72 * i); CHECK_GL_ERROR();
	glBindVertexArray(0); CHECK_GL_ERROR();
	
}

std::vector<float> GraphicsEngine::DrawCube(const Transform &worldTrans, const double color[3])
{
	m_debugShader->SetVec3Uniform("ourColour", Vector3f(color[0], color[1], color[2]));

	//define the cube
	std::vector<float> vertices = {
		// face one
			worldTrans.GetRelativePosition().GetX() + 1.0f,  worldTrans.GetRelativePosition().GetY() + 1.0f, worldTrans.GetRelativePosition().GetZ() + 1.0f,  // top right
			worldTrans.GetRelativePosition().GetX() + -1.0f,  worldTrans.GetRelativePosition().GetY() + 1.0f, worldTrans.GetRelativePosition().GetZ() + 1.0f,  // top left
			worldTrans.GetRelativePosition().GetX() + -1.0f, worldTrans.GetRelativePosition().GetY() + -1.0f, worldTrans.GetRelativePosition().GetZ() + 1.0f,  // bottom left 
			worldTrans.GetRelativePosition().GetX() + 1.0f, worldTrans.GetRelativePosition().GetY() + -1.0f, worldTrans.GetRelativePosition().GetZ() + 1.0f,  // bottom right 
		// face two
			worldTrans.GetRelativePosition().GetX() + 1.0f,  worldTrans.GetRelativePosition().GetY() + 1.0f, worldTrans.GetRelativePosition().GetZ() + 1.0f,  // top right
			worldTrans.GetRelativePosition().GetX() + 1.0f,  worldTrans.GetRelativePosition().GetY() + -1.0f, worldTrans.GetRelativePosition().GetZ() + 1.0f,  // top left
			worldTrans.GetRelativePosition().GetX() + 1.0f, worldTrans.GetRelativePosition().GetY() + -1.0f, worldTrans.GetRelativePosition().GetZ() + -1.0f,  // bottom left 
			worldTrans.GetRelativePosition().GetX() + 1.0f, worldTrans.GetRelativePosition().GetY() + 1.0f, worldTrans.GetRelativePosition().GetZ() + -1.0f,  // bottom right 
		// face three
			worldTrans.GetRelativePosition().GetX() + 1.0f,  worldTrans.GetRelativePosition().GetY() + 1.0f, worldTrans.GetRelativePosition().GetZ() + 1.0f,  // top right
			worldTrans.GetRelativePosition().GetX() + 1.0f,  worldTrans.GetRelativePosition().GetY() + 1.0f, worldTrans.GetRelativePosition().GetZ() + -1.0f,  // top left
			worldTrans.GetRelativePosition().GetX() + -1.0f, worldTrans.GetRelativePosition().GetY() + 1.0f, worldTrans.GetRelativePosition().GetZ() + -1.0f,  // bottom left 
			worldTrans.GetRelativePosition().GetX() + -1.0f, worldTrans.GetRelativePosition().GetY() + 1.0f, worldTrans.GetRelativePosition().GetZ() + 1.0f,  // bottom right 
		// face four
			worldTrans.GetRelativePosition().GetX() + -1.0f,  worldTrans.GetRelativePosition().GetY() + -1.0f, worldTrans.GetRelativePosition().GetZ() + -1.0f,  // top right
			worldTrans.GetRelativePosition().GetX() + -1.0f,  worldTrans.GetRelativePosition().GetY() + 1.0f, worldTrans.GetRelativePosition().GetZ() + -1.0f,  // top left
			worldTrans.GetRelativePosition().GetX() + 1.0f, worldTrans.GetRelativePosition().GetY() + 1.0f, worldTrans.GetRelativePosition().GetZ() + -1.0f,  // bottom left 
			worldTrans.GetRelativePosition().GetX() + 1.0f, worldTrans.GetRelativePosition().GetY() + -1.0f, worldTrans.GetRelativePosition().GetZ() + -1.0f,  // bottom right 
		// face five
			worldTrans.GetRelativePosition().GetX() + -1.0f,  worldTrans.GetRelativePosition().GetY() + -1.0f, worldTrans.GetRelativePosition().GetZ() + -1.0f,  // top right
			worldTrans.GetRelativePosition().GetX() + -1.0f,  worldTrans.GetRelativePosition().GetY() + -1.0f, worldTrans.GetRelativePosition().GetZ() + 1.0f,  // top left
			worldTrans.GetRelativePosition().GetX() + -1.0f, worldTrans.GetRelativePosition().GetY() + 1.0f, worldTrans.GetRelativePosition().GetZ() + 1.0f,  // bottom left 
			worldTrans.GetRelativePosition().GetX() + -1.0f, worldTrans.GetRelativePosition().GetY() + 1.0f, worldTrans.GetRelativePosition().GetZ() + -1.0f,  // bottom right 
		// face six
			worldTrans.GetRelativePosition().GetX() + -1.0f,  worldTrans.GetRelativePosition().GetY() + -1.0f, worldTrans.GetRelativePosition().GetZ() + -1.0f,  // top right
			worldTrans.GetRelativePosition().GetX() + 1.0f,  worldTrans.GetRelativePosition().GetY() + -1.0f, worldTrans.GetRelativePosition().GetZ() + -1.0f,  // top left
			worldTrans.GetRelativePosition().GetX() + 1.0f, worldTrans.GetRelativePosition().GetY() + -1.0f, worldTrans.GetRelativePosition().GetZ() + 1.0f,  // bottom left 
			worldTrans.GetRelativePosition().GetX() + -1.0f, worldTrans.GetRelativePosition().GetY() + -1.0f, worldTrans.GetRelativePosition().GetZ() + 1.0f,  // bottom right 

	};





	//define the indices (so we dont double up on positions)
	//unsigned int indices[] = {  // note that we start from 0!
	//0, 1, 3,   // first triangle
	//1, 2, 3    // second triangle
	//};

	//unsigned int EBO;
	//glGenBuffers(1, &EBO);


	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices.data()[0]) * vertices.size(), vertices.data(), GL_DYNAMIC_DRAW); CHECK_GL_ERROR();

	return vertices;

}

void GraphicsEngine::SetupDirLightFBO()
{
	m_shadowMapper.SetupDirLightFBO();
}

void GraphicsEngine::SetupPointLightFBO(unsigned lightIndex)
{
	m_shadowMapper.SetupPointLightFBO(lightIndex);
}

void GraphicsEngine::BindDirShadowDepthMapTexture() const
{
	m_shadowMapper.BindDirShadowDepthMapTexture();
}

void GraphicsEngine::BindPointDepthCubeMapTexture(unsigned lightIndex) const
{
	m_shadowMapper.BindPointDepthCubeMapTexture(lightIndex);
}

void GraphicsEngine::GoFullscreen() const
{
	SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN);
	SDL_Surface *surface = SDL_GetWindowSurface(m_window);
	SDL_UpdateWindowSurface(m_window);
}

Matrix4f GraphicsEngine::GetCameraProjection()
{
	return Perspective(
		m_camera->GetCamera().FOV,
		((float)GRAPHICS->m_windowWidth / GRAPHICS->m_windowHeight),
		m_camera->GetCamera().NearClip,
		m_camera->GetCamera().FarClip
	);
}

Matrix4f GraphicsEngine::GetDirProjViewMat() const
{
	return m_shadowMapper.GetDirProjViewMat();
}

std::vector<Matrix4f> GraphicsEngine::GetPointProjViewMat(unsigned lightIndex) const
{
	return m_shadowMapper.GetPointProjViewMat(lightIndex);
}

Matrix4f GraphicsEngine::GetCameraView()
{
	return LookAt(
		m_camera->GetTransform().GetWorldTransform().GetRelativePosition(),
		m_camera->GetTransform().GetWorldTransform().GetRelativePosition() + m_camera->GetTransform().GetWorldTransform().GetRelativeForward(),
		m_camera->GetTransform().GetWorldTransform().GetRelativeUp()
	);
}

unsigned GraphicsEngine::NumPointLights() const
{
	return m_lightManager.NumPointLights();
}

void GraphicsEngine::DirLightShadowPass()
{
	if (!m_shadowMapper.DirLightAcive())
	{
		return;
	}
	m_shadowMapper.SetupDirLightFBO();
	m_dirShadowMapShader->SetMat4Uniform("dirLightSpaceMatrix", GetDirProjViewMat());
	RenderObjects(*m_dirShadowMapShader, true);
	glBindFramebuffer(GL_FRAMEBUFFER, 0); CHECK_GL_ERROR();
}

void GraphicsEngine::PointLightShadowPass()
{
	unsigned numLights = m_lightManager.NumPointLights();
	if (numLights < 1)
	{
		return;
	}

	for (int lightIndex = 0; lightIndex < numLights; lightIndex++)
	{
		std::vector<Matrix4f> mats = GetPointProjViewMat(lightIndex);
		assert(mats.size() == 6);
		m_shadowMapper.SetupPointLightFBO(lightIndex);
		for (int matIndex = 0; matIndex < mats.size(); matIndex++)
		{
			m_pointShadowMapShader->SetMat4Uniform("shadowMatrices[" + std::to_string(matIndex) + "]", mats[matIndex]);
		}
		m_pointShadowMapShader->SetVec3Uniform(
			"lightPos",
			m_lightManager.GetPointLight(lightIndex).GetTransform().GetWorldTransform().GetRelativePosition()
		);
		RenderObjects(*m_pointShadowMapShader, true);
		glBindFramebuffer(GL_FRAMEBUFFER, 0); CHECK_GL_ERROR();
	}
}

void GraphicsEngine::CameraRenderPass(bool debugMenu) const
{
	GRAPHICS->m_litShader->SetMat4Uniform("view", GRAPHICS->GetCameraView());
	if (m_shadowMapper.DirLightAcive())
	{
		GRAPHICS->m_litShader->SetMat4Uniform("dirLight.dirLightSpaceMatrix", GRAPHICS->GetDirProjViewMat());
	}
	GRAPHICS->UpdateCamViewPos();
	unsigned numPointLights = GRAPHICS->NumPointLights();
	for (int i = 0; i < numPointLights; i++)
	{
		const CPointLight &light = GRAPHICS->GetPointLight(i);
		GRAPHICS->m_litShader->SetVec3Uniform(
			"pointLights[" + std::to_string(i) + "].position",
			light.GetTransformConst().GetWorldTransform().GetRelativePosition()
		);
	}

	GRAPHICS->m_unlitShader->Use();
	GRAPHICS->m_unlitShader->SetMat4Uniform("projection", GRAPHICS->GetCameraProjection());
	GRAPHICS->m_unlitShader->SetMat4Uniform("view", GRAPHICS->GetCameraView());

	GRAPHICS->m_debugShader->Use();
	GRAPHICS->m_debugShader->SetMat4Uniform("projection", GRAPHICS->GetCameraProjection());
	GRAPHICS->m_debugShader->SetMat4Uniform("view", GRAPHICS->GetCameraView());

	GRAPHICS->SetViewportToWindowSize();
	GRAPHICS->NewFrame(debugMenu);
	GRAPHICS->RenderObjects();
}

CPointLight &GraphicsEngine::GetPointLight(unsigned index)
{
	assert(index < m_lightManager.NumPointLights());
	return m_lightManager.GetPointLight(index);
}

float GraphicsEngine::GetPointLightFarPlane() const
{
	return m_shadowMapper.GetPointLightFarPlane();
}
