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
	//CNavMesh* parentMesh;

	private:
	int xPos;
	int zPos;
	Transform transform;

	//bool active;

	public:
		NavNode( Transform parentTransform, int x, int z)
		{
			xPos = x;
			zPos = z;
			transform.SetRelativePosition(x,0,z);
			
			//active = true;
		}

		int GetXPos()
		{
			return xPos;
		}

		int GetZPos()
		{
			return zPos;
		}

		Transform* GetTransform()
		{
			return &transform;
		}


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

		/**
		 * @brief Retrieves the Navigation Nodes vector
		*/
	std::vector<NavNode*> GetNavNodes();

private:
		/**
		 * @brief The vars for this comp
		*/
		std::vector<NavNode*> m_navNodes;
	
};
