#pragma once

#include "Camera.h"
#include "ModernOpenGL/Model.h"
#include "AModel.h"
#include "Color.h"

#include <SDL2/SDL.h>
#include "GraphicsLibraryEnum.h"
#include <string>
#include <map>
#include "imgui/imgui.h"
#include "SkyBox.h"
#include "LightManager.h"

class CCamera;

#define CHECK_GL_ERROR \
	if (glGetError() == GL_NO_ERROR){printf("GL_NO_ERROR\n");} \
	else if(glGetError() == GL_INVALID_ENUM){printf("GL_INVALID_ENUM\n");} \
	else if(glGetError() == GL_INVALID_VALUE){printf("GL_INVALID_VALUE\n");} \
	else if(glGetError() == GL_INVALID_OPERATION){printf("GL_INVALID_OPERATION\n");} \
	else if(glGetError() == GL_INVALID_FRAMEBUFFER_OPERATION){printf("GL_INVALID_FRAMEBUFFER_OPERATION\n");} \
	else if(glGetError() == GL_OUT_OF_MEMORY){printf("GL_OUT_OF_MEMORY\n");} \
	else if(glGetError() == GL_STACK_UNDERFLOW){printf("GL_STACK_UNDERFLOW\n");} \
	else if(glGetError() == GL_STACK_OVERFLOW){printf("GL_STACK_OVERFLOW\n");}

/**
 * @brief A singleton that handles all of the engine graphics
*/
class GraphicsEngine
{
private:
	/**
	 * @brief The SDL window
	*/
	SDL_Window* m_window;
	/**
	 * @brief The SDL renderer
	*/
	SDL_Renderer* m_renderer;

	/**
	 * @brief The openGL context used for SDL
	*/
	SDL_GLContext m_glContext;

	/**
	 * @brief the camera in use
	*/
	CCamera* m_camera;

	/**
	 * @brief The graphics library in use
	*/
	GraphicsLibrary m_graphLib;

	/**
	 * @brief list of texture IDs registered with openGL
	*/
	std::map<std::string, unsigned> m_textureIDs;

	/**
	 * @brief texture id's of skybox textures
	*/
	std::string m_skyboxTextures[6];

	/**
	 * @brief if the skybox has been initialised
	*/
	bool m_skyboxInitialized;

	int m_windowWidth;

	int m_windowHeight;

	ImGuiIO m_imgui_io;

	ImVec4 m_clear_color;

	unsigned int VAODebug = 0;
	unsigned int VBODebug = 0;
	bool initDebug = true;

	SkyBox skybox;

public:
	/**
	 * @brief default constructor
	*/
	GraphicsEngine();

	~GraphicsEngine();

	/**
	 * @brief Generates pointer to instance of singleton
	 * @return Pointer to the graphics engine
	*/
	static GraphicsEngine* instance();

	/**
	 * @brief Initialises the graphics
	 * @param renderer - which graphics api to use
	 * @return Whether initialisation succeeded
	*/
	bool initialise(GraphicsLibrary renderer, int windowWidth, int windowHeight);
	/**
	 * @brief initialises lighting
	 * @return whether operation succeeded
	*/
	bool initLighting();

	/**
	 * @brief Function to be called at the start of every frame for rendering
	*/
	void newFrame(bool debugMenu);

	void UpdateViewPos() const;

	int AddPointLight(CPointLight* light);

	/**
	 * @brief Renders all visible objects
	*/
	void renderObjects();
	/**
	 * @brief Function to be called at the end of every frame for rendering
	*/
	void endFrame(bool debugMenu);
	/**
	 * @brief generates a texture for the graphics library
	 * @param key the texture key
	 * @param image the texture image data
	 * @param width the width of the texture
	 * @param height the height of the texture
	*/
	void GenerateTexture(std::string key, unsigned char* image, int width, int height);
	/**
	 * @brief deletes a texture from the graphics library
	 * @param key factory storage key of the texture
	*/
	void DeleteTexture(std::string key);
	/**
	 * @brief changes the current camera displaying to the screen
	 * @param camera the camera to use
	*/
	void SetDisplayCamera(CCamera* camera);
	/**
	 * @brief current camera accessor
	 * @return the camerca currently in use
	*/
	CCamera* GetDisplayCamera();
	/**
	 * @brief Draws a model asset on the screen
	 * @param model The model to draw
	 * @param trans Transform of the model
	*/
	void DrawModel(Model* model, const Transform& trans);
	/**
	 * @brief retrieves the ID by which a texture is stored in the graphics library
	 * @param key the key by which it's stored by the asset factory
	 * @return the key of the texture
	*/
	unsigned GetTexID(std::string key) const;

	void GetScreenSize(int&w, int&h);

	void InitSkybox(
		std::string negx,
		std::string negy,
		std::string negz,
		std::string posx,
		std::string posy,
		std::string posz
	);

	void RenderSkybox();

	void Close();

	void GoFullscreen() const
	{
		SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN);
		SDL_Surface* surface = SDL_GetWindowSurface(m_window);
		SDL_UpdateWindowSurface(m_window);
	}

	glm::mat4 GetProjection();

	glm::mat4 GetView();

	Shader* m_litShader;

	Shader* m_unlitShader;
	
	Shader* m_debugShader;

	bool m_drawDebug = false;

private:
	/**
	 * @brief initialises openGL
	 * @return whether operation succeeded
	*/
	bool InitOpenGL(int windowWidth, int windowHeight);

	void InitImGui();

	/**
	 * @brief initialises directX
	 * @return whether operation succeeded
	*/
	bool InitDirectX();

	
	/**
	 * @brief Setups the debug rendering of collider boxes
	*/
	void InitDebug(std::vector <float>& tempVector);
	
	/*
	 * @brief Renders debug colliders
	*/
	void DrawDebug();

	LightManager m_lightManager;
};

#define GRAPHICS GraphicsEngine::instance()
