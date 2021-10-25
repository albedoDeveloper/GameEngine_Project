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


struct GridLocation
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

		GridLocation GetLocation();

		Transform* GetTransform();

		bool GetActive();

		void SetActive(bool isActive);

		void PopulateNeighbours();

		std::vector<NavNode *> GetNeighbours();

		void UpdateNeighbours(bool isActive);

		//Grid location helpers

	friend bool operator == (NavNode a, NavNode b)
	{
		return a.nodeLocation.x == b.nodeLocation.x && a.nodeLocation.z == b.nodeLocation.z;
	}

	friend bool operator != (NavNode a, NavNode b)
	{
		return !(a == b);
	}

	friend bool operator < (NavNode a, NavNode b)
	{
		return std::tie(a.nodeLocation.x, a.nodeLocation.z) < std::tie(b.nodeLocation.x, b.nodeLocation.z);
	}

	friend std::basic_iostream<char>::basic_ostream &operator<<(std::basic_iostream<char>::basic_ostream &out, const NavNode &loc)
	{
		out << '(' << loc.nodeLocation.x << ',' << loc.nodeLocation.z << ')';
		return out;
	}

	private:

		CNavMesh *parentMesh;

		GridLocation nodeLocation;

		//int xPos;
		//int zPos;
		Transform transform;

		bool active;

		//float dirs[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
		//GridLocation dirs[4] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

		std::vector<NavNode*> m_neighbourNodes;

};





