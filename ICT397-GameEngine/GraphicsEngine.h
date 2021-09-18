/*****************************************************************//**
 * \file   GraphicsEngine.h
 * \brief  Graphics and Rendering
 * \date   September 2021
 *********************************************************************/

#pragma once

#include "Camera.h"
#include "ModernOpenGL/AModel.h"
#include "Color.h"
#include <SDL2/SDL.h>
#include "GraphicsLibraryEnum.h"
#include <string>
#include <map>
#include "./ThirdParty/imgui/imgui.h"
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
public:
		/**
		 * @brief Generates pointer to instance of singleton
		 * @return Pointer to the graphics engine
		*/
	static GraphicsEngine *instance();

		/**
		 * @brief Initialises the graphics
		 * @param renderer - which graphics api to use
		 * @return Whether initialisation succeeded
		*/
	bool Init(GraphicsLibrary renderer, int windowWidth, int windowHeight);

		/**
		 * @brief initialises lighting
		 * @return whether operation succeeded
		*/
	bool initLighting();

		/**
		 * @brief Function to be called at the start of every frame for rendering
		*/
	void newFrame(bool debugMenu);

		/**
		 * @brief Updates view based on camera transform
		 */
	void UpdateViewPos() const;

		/**
		 * @brief creates a point light
		 * \param light pointer to the light to be generated
		 * \return
		 */
	int AddPointLight(CPointLight *light);

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
	void GenerateTexture(std::string key, unsigned char *image, int width, int height);

		/**
		 * @brief deletes a texture from the graphics library
		 * @param key factory storage key of the texture
		*/
	void DeleteTexture(std::string key);

		/**
		 * @brief changes the current camera displaying to the screen
		 * @param camera the camera to use
		*/
	void SetDisplayCamera(CCamera *camera);

		/**
		 * @brief current camera accessor
		 * @return the camerca currently in use
		*/
	CCamera *GetDisplayCamera();

		/**
		 * @brief Draws a model asset on the screen
		 * @param model The model to draw
		 * @param trans Transform of the model
		*/
	void DrawModel(AModel *model, const Transform &trans, const Shader *m_shader);

		/**
		 * @brief retrieves the ID by which a texture is stored in the graphics library
		 * @param key the key by which it's stored by the asset factory
		 * @return the key of the texture
		*/
	unsigned GetTexID(std::string key) const;

		/**
		 * @brief Accesses the current screen width and height
		 * \param w window width
		 * \param h window height
		 */
	void GetScreenSize(int &w, int &h);

		/**
		 * @brief closes the game
		 */
	void Close();

		/**
		 * Enables fullscreen mode
		 */
	void GoFullscreen() const
	{
		SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN);
		SDL_Surface *surface = SDL_GetWindowSurface(m_window);
		SDL_UpdateWindowSurface(m_window);
	}

		/**
		 * @brief Accessor for the projection matrix
		 * \return 4f projection matrix
		 */
	Matrix4f GetProjection();

		/**
		 * @brief returns the current camera view position/direction
		 * \return 4f view matrix
		 */
	Matrix4f GetView();

		/** @brief pointer to lit shader */
	Shader *m_litShader;

		/** @brief pointer to unlit shader*/
	Shader *m_unlitShader;

		/** @brief pointer to debug shader */
	Shader *m_debugShader;

		/** @brief draw debug colliders */
	bool m_drawDebug = false;

private:
		/**
		 * @brief default constructor
		*/
	GraphicsEngine();

		/** @brief default destructor */
	~GraphicsEngine();

		/**
		 * @brief The SDL window
		*/
	SDL_Window *m_window;

		/**
		 * @brief The SDL renderer
		*/
	SDL_Renderer *m_renderer;

		/**
		 * @brief The openGL context used for SDL
		*/
	SDL_GLContext m_glContext;

		/**
		 * @brief the camera in use
		*/
	CCamera *m_camera;

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

		/** @brief window Width */
	int m_windowWidth;

		/** @brief window Height */
	int m_windowHeight;

		/** @brief ImGui Input output handler */
	ImGuiIO m_imgui_io;

		/** @brief clears current colour */
	ImVec4 m_clear_color;

		/** @brief VertexArrayObject */
	unsigned int VAODebug = 0;

		/** @brief VertexBufferObject debug */
	unsigned int VBODebug = 0;

		/** @brief are debug colliders being drawn*/
	bool initDebug = true;

		/** @brief the ingame Skybox */
	SkyBox skybox;

		/**
		 * @brief initialises openGL
		 * @return whether operation succeeded
		*/
	bool InitOpenGL(int windowWidth, int windowHeight);

		/** @brief initialises ImGui */
	void InitImGui();

		/**
		 * @brief initialises directX
		 * @return whether operation succeeded
		*/
	bool InitDirectX();

		/**
		 * @brief Setups the debug rendering of collider boxes
		*/
	void InitDebug(std::vector <float> &tempVector);

		/*
		 * @brief Renders debug colliders
		*/
	void DrawDebug();

		/** @brief lighManager reference */
	LightManager m_lightManager;
};

#define GRAPHICS GraphicsEngine::instance()
