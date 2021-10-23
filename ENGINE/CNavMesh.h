/*****************************************************************//**
*\file   CNavMesh.h
*\brief  Navigation Mesh Component
*
*\date   September 2021
* ********************************************************************/
#pragma once

#include "CComponent.h"
#include <iostream>



class NavNode
{
	int id;
	Transform transform;
};

	/**

	 * @brief A navigation mesh for pathfinding
	*/
class CNavMesh : public CComponent
{
	public:
	/**
	 * @brief Constructor based on parent GameObject
	 * @param parent the parent transform for this component
	 * @param parentObj the parent object of this component
	*/
		CNavMesh(Transform *parent, GameObject *parentObj);

		/**
		 * @brief Initiates the script at program start
		*/
	virtual void Start();

		/**
		 * @brief Updates ongoing behaviour each frame
		*/
	virtual void Update();

		/**
		 * @brief renders the navmesh
		*/
	virtual void Render();

		/**
		 * @brief saves the component
		*/
	virtual void Save(nlohmann::json &j);

		/**
		 * @brief loads the component from saved state
		*/
	virtual void Load(nlohmann::json &j);

		/**
		 * @brief Draws to imgui
		*/
	virtual void DrawToImGui();

		/**
		 * @brief Creates teh nave mesh nodes
		*/
	void GenerateNavMesh();

private:
		/**
		 * @brief The vars for this comp
		*/
		std::vector<NavNode> navNodes;
	
};
