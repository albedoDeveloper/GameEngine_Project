#pragma once

#include "Component.h"
#include "Camera.h"
#include "GraphicsEngine.h"

/**
 * @brief A component holding and managing a camera
*/
class CCamera : public Component
{
private:
    /**
     * @brief The actual camera object
    */
    Camera m_camera;

public:
    /**
     * @brief constructor
     * @param pointer to parent transform for this component's transform
	 * @param parentObj pointer to parent object of this component
    */
    CCamera(Transform* parent, GameObject* parentObj);

    /**
     * @brief initialises component at program start
    */
    virtual void Start();
    /**
     * @brief Draws to imgui
    */
    virtual void DrawToImGui();

    /**
     * @brief camera mutator
     * @param camera the camera for the component to use
    */
    void SetCamera(Camera camera);
    /**
     * @brief camera accessor
     * @return the camera the component is using
    */
    Camera GetCamera();

    /**
     * @brief makes this component's camera the current one to be used by the engine and display the screen
    */
    void SetAsCurrentCamera(); 
};

