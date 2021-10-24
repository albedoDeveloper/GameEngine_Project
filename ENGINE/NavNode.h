/*****************************************************************//**
*\file   NavNode.h
*\brief  Nodes belonging to Navigation Mesh
*
*\date   September 2021
* ********************************************************************/
#pragma once
//#include "CNavMesh.h"
#include "Transform.h"

class CNavMesh;


struct NodeDir
{
	int x;
	int z;
};

class NavNode
{

	


	public:
		
		NavNode(CNavMesh *parentMeshIn, int x, int z, bool isActive);
		

		void UpdateTransform(Transform parentTransform);

		int GetXPos();

		int GetZPos();

		Transform* GetTransform();

		bool GetActive();

		void SetActive(bool isActive);

		void PopulateNeighbours();

		void UpdateNeighbours(bool isActive);


	private:

		CNavMesh *parentMesh;

		int xPos;
		int zPos;
		Transform transform;

		bool active;

		//float dirs[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
		NodeDir dirs[4] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

		std::vector<NavNode*> m_neighbourNodes;

};

