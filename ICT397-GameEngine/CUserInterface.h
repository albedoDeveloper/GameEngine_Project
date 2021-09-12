#pragma once
#include "Component.h"
#include <string>

/**
 * @brief Stores information on an element of the user interface, displayed on the screen
*/
class CUserInterface : public Component
{
private:
	/**
	 * @brief The image to be displayed
	*/
	std::string textureKey;

	/**
	 * @brief Whether the image is to be displayed
	*/
	bool isVisible;
	/**
	 * @brief whether the image is displayed at program start
	*/
	bool m_initialVisibility;

	/**
	 * @brief width of image in pixels
	*/
	int m_width;

	/**
	 * @brief height of image in pixels
	*/
	int m_height;

	/**
	 * @brief x position of image. Origin top left, x goes to the right
	*/
	int m_xPos;

	/**
	 * @brief y position of image. Origin top left, y goes down
	*/
	int m_yPos;

	/**
	 * @brief if the left mouse button was clicked this frame
	*/
	bool m_mouseDown;
public:
	/**
	 * @brief constructor taking information on parent
	 * @param parent The parent transform
	 * @param parentObj The parent game object
	*/
	CUserInterface(Transform* parent, GameObject* parentObj);

	/**
	 * @brief image mutator using storage key for asset factory
	 * @param key The key the image is stored at
	 * @return the image
	*/
	void AssignTexture(std::string key);
	/**
	 * @brief isVisible mutator
	 * @param visibility whether the component should be visible
	*/
	void SetVisibility(bool visibility);

	/**
	 * @brief set size of image in terms of pixels
	*/
	void SetSize(unsigned width, unsigned height);

	/**
	 * @brief height of image in pixels
	*/
	void SetPosition(int x, int y);

	/**
	 * @brief set the image to take up the whole view
	*/
	void SetFullscreen();

	/**
	 * @brief check if left mouse button was clicked this frame
	*/
	bool MouseClicked() const;

	/**
	 * @brief Initiates the UI component so it can begin
	*/
	virtual void Start();
	/**
	 * @brief Updates with ongoing behaviour
	*/
	virtual void Update();
	/**
	 * @brief Renders the image
	*/
	virtual void Render();
	/**
	 * @brief Renders the image after other components render
	*/
	virtual void LateRender();
};

