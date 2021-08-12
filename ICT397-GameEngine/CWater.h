#pragma once

#include "Component.h"
#include "CStaticMesh.h"

#include <iostream>

class CWater : public CStaticMesh
{
public:

	/**
	 * @brief standard component constructor
	*/
	CWater(Transform* parent, GameObject* parentObj);

	/**
	 * @brief initialises the component at start of program
	*/
	void Start();

	/**
	 * @brief updates ongoing behaviour each frame
	*/
	void Update();

	/**
	 * @brief randers the component if visible
	*/
	void Render();

	/**
	 * @brief a render called after the first render
	*/
	void LateRender();

private:
	float texOffset;
	bool directionForward;
};
