#pragma once
#include "MathLibrary.h"
#include "Component.h"

/**
 * @brief a component that creates light in a particular direction
*/
class CSpotlight : public Component
{
private:
	/**
	 * @brief the colour of the light, in RGBA format, from 0-1
	*/
	Vector4f* colour;
	/**
	 * @brief the width of the beam emitted by the spotlight, in degrees
	*/
	int beamWidth;
	/**
	 * @brief the length of the beam, in distance units
	*/
	int beamLength;
public:
	/**
	 * @brief constructor
	 * @param parent the parent transform
	 * @param parentObj the parent object
	*/
	CSpotlight(Transform* parent, GameObject* parentObj);
	/**
	 * @brief colour accessor
	 * @return the light's colour
	*/
	Vector4f* GetColour() const;
	/**
	 * @brief colour mutator
	 * @param colour colour for the light
	*/
	void SetColour(Vector4f* colour);
	/**
	 * @brief beamWidth accessor
	 * @return angle of beam width
	*/
	int GetBeamWidth();
	/**
	 * @brief beamWidth mutator
	 * @param angle angle for beam width
	*/
	void SetBeamWidth(int angle);
	/**
	 * @brief initialises the spotlight at program start
	*/
	virtual void Start();
	/**
	 * @brief updates spotlight behaviour each frame
	*/
	virtual void Update();
	/**
	 * @brief renders component to the screen
	*/
	virtual void Render();
	/**
	 * @brief renders component to the screen after other rendering
	*/
	virtual void LateRender();
};

