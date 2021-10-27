/*****************************************************************//**
 * \file   GraphicsEngine.h
 * \brief  Graphics and Rendering
 * \date   September 2021
 *********************************************************************/

#pragma once

#include "Camera.h"
#include "ModernOpenGL/AModel.h"
#include "Color.h"
#include "GraphicsLibraryEnum.h"
#include <string>
#include <map>
#include "./ThirdParty/imgui/imgui.h"
#include "SkyBox.h"
#include "LightManager.h"
#include "ShadowMapper.h"
#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <bulletphysics/btBulletCollisionCommon.h>

class CCamera;

	/**
	 * @brief A singleton that handles all of the engine graphics
	*/
class GraphicsEngine : public btIDebugDraw
{
	friend class Mesh;
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
		 * @brief Function to be called at the start of every frame for rendering
		*/
	void NewFrame(bool debugMenu);

		/**
		 * @brief Updates view based on camera transform
		 */
	void UpdateCamViewPos() const;

		/**
		 * @brief creates a point light
		 * \param light pointer to the light to be generated
		 * \return
		 */
	int AddPointLight(CPointLight *light);

	void AddDirectionalLight(const CDirectionalLight &light);

	void WarpMouseCentreWindow() const;

		/**
		 * @brief Renders all visible objects
		*/
	void RenderObjects(Shader &shader, bool noTexture);

	void RenderObjects();

	void SetViewportToWindowSize() const;

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
	void DrawModel(AModel *model, const Transform &trans, const Shader *m_shader, bool noTexture);

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

	void SetupDirLightFBO();
	void SetupPointLightFBO(unsigned lightIndex);

	void BindDirShadowDepthMapTexture() const;

	void BindPointDepthCubeMapTexture(unsigned lightIndex) const;

		/**
		 * Enables fullscreen mode
		 */
	void GoFullscreen() const;

		/**
		 * @brief Accessor for the projection matrix of the active camera
		 * \return 4f projection matrix
		 */
	Matrix4f GetCameraProjection();

	Matrix4f GetDirProjViewMat() const;

	std::vector<Matrix4f> GetPointProjViewMat(unsigned lightIndex) const;

		/**
		 * @brief returns the current camera view position/direction
		 * \return 4f view matrix
		 */
	Matrix4f GetCameraView();

	unsigned NumPointLights() const;

	void DirLightShadowPass();

	void PointLightShadowPass();

	void CameraRenderPass(bool debugMenu) const;

	CPointLight &GetPointLight(unsigned index);

	float GetPointLightFarPlane() const;

	void DrawLine(const Vector3f &from, const Vector3f &to, const Vector3f &color);

	void DrawPoint(const Vector3f &pos, const Vector3f &colour);

	virtual void drawLine(const btVector3 &from, const btVector3 &to, const btVector3 &color);

	virtual void drawContactPoint(const btVector3 &PointOnB, const btVector3 &normalOnB, btScalar distance, int lifeTime, const btVector3 &color);

	virtual void reportErrorWarning(const char *warningString);

	virtual void draw3dText(const btVector3 &location, const char *textString);

	virtual void setDebugMode(int debugMode);

	virtual int getDebugMode() const;

		/** @brief pointer to lit shader */
	Shader *m_litShader;

		/** @brief pointer to unlit shader*/
	Shader *m_unlitShader;

		/** @brief pointer to debug shader */
	Shader *m_debugShader;

	Shader *m_dirShadowMapShader;

	Shader *m_pointShadowMapShader;


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

	ShadowMapper m_shadowMapper;
};

#define GRAPHICS GraphicsEngine::instance()
