#pragma once

#include "Camera.h"
#include "ModernOpenGL/Model.h"
#include "AModel.h"
#include "Color.h"
#include "CSpotlight.h"

#include <SDL2/SDL.h>
#include "GraphicsLibraryEnum.h"
#include <string>
#include <map>
#include "MultiTexture.h"

class CCamera;
class CBaseTerrain;

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


public:
	/**
	 * @brief default constructor
	*/
	GraphicsEngine();
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
	 * @brief camera mutator
	 * @param camera the camera to use
	*/
	//void SetCamera(Camera camera);
	/**
	 * @brief camera accessor
	 * @return the camera in use
	*/
	//Camera GetCamera();

	/**
	 * @brief Function to be called at the start of every frame for rendering
	*/
	void newFrame();
	/**
	 * @brief Renders all visible objects
	*/
	void renderObjects();
	/**
	 * @brief Function to be called at the end of every frame for rendering
	*/
	void endFrame();
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
	 * @brief sets up a spotlight within the scene
	 * @param light the spotlight to set up
	*/
	void UpdateSpotlight(const CSpotlight* light);
	/**
	 * @brief Draws a model asset on the screen
	 * @param model The model to draw
	 * @param trans Transform of the model
	*/
	void DrawModel(Model* model, const Transform& trans);

	void DrawModelMovingTexture(Model* model, const Transform& trans, const float texOffset) const;
	/**
	 * @brief Draws a model asset on the screen with lighting
	 * @param model The model to draw
	 * @param trans Transform of the model
	*/
	void DrawIlluminatedModel(const AModel* model, const Transform& trans) const;
	/**
	 * @brief Renders a heightmap on the screen
	 * @param terrain The terrain to render
	 * @param withTexture Whether the terrain's texture should be used
	*/
	void renderHeightMap(CBaseTerrain* terrain, bool withTexture);
	/**
	 * @brief Renders an image to the screen
	 * @param textureKey the key of the image to draw
	*/
	void DrawImage(std::string textureKey, int width, int height, int posX, int posY);
	/**
	 * @brief Renders a section of terrain
	 * @param terrain the terrain to display
	 * @param withTexture whether it should be displayed with a texture or not
	*/
	void DrawTerrain();

	/**
	 * @brief generate display list for a terrain. using brute force method
	*/
	void GenDisplayListTerrain(CBaseTerrain* terrain, bool withTexture, bool asWirefram);

	/**
	 * @brief draw a collider
	*/
	void DrawCollider(float maxX, float maxY, float maxZ, float minX, float minY, float minZ, const Transform& worldT);

	/**
	 * @brief Renders a square grid floor on the screen
	 * @param gridHeight, the height the grid will be drawn at
	 * @param lineThickness the thickness of the grid lines
	 * @param gridWidth the width of the grid (number of cells)
	 * @param cellWidth the size of the grid squares
	*/
	void DrawGrid(float gridHeight, float lineThickness, float gridWidth, float cellWidth);
	/**
	 * @brief retrieves the ID by which a texture is stored in the graphics library
	 * @param key the key by which it's stored by the asset factory
	 * @return the key of the texture
	*/
	unsigned GetTexID(std::string key) const;
	
	unsigned char* GetTextureArray(std::string key, int &w, int &h);

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

	Shader* shader = nullptr;
	
	Shader* debugShader = nullptr;

	bool firstFrameDebug = false;

	bool drawDebug = false;

private:
	/**
	 * @brief initialises openGL
	 * @return whether operation succeeded
	*/
	bool InitOpenGL(int windowWidth, int windowHeight);
	/**
	 * @brief initialises lighting for openGL
	 * @return whether operation succeeded
	*/
	bool InitOpenGLlighting();
	/**
	 * @brief initialises directX
	 * @return whether operation succeeded
	*/
	bool InitDirectX();
	/**
	 * @brief generates an opengl texture
	 * @param image the image data to send in
	 * @param width width of the image in pixels
	 * @param height height of the image in pixels
	 * @param key key at which the texture should be stored
	*/
	void GenOpenGLTexture(unsigned char* image, int width, int height, std::string key);
	/**
	 * @brief Sends a transformation to openGL
	 * @param t the transformation to use
	*/
	void OpenGLTransformation(const Transform& t) const;

	
	/**
	 * @brief Setups the debug rendering of collider boxes
	*/
	void InitDebug(std::vector <float>& tempVector);
	
	/**
	 * @brief Renders debug colliders
	*/
	void DrawDebug(glm::mat4 projection, glm::mat4 view, glm::mat4 trans);

	unsigned int VAODebug = 0;
	unsigned int VBODebug = 0;
	bool initDebug = true;

};

#define GRAPHICS GraphicsEngine::instance()
