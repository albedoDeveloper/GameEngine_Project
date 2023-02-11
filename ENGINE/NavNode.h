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

/**
	* @brief The x,z grid location of the node
*/
struct GridLocation
{
	int x;
	int z;
};

class NavNode
{
	public:
		
		/**
		 * @brief Default constructor
		 * @param the parent NavMesh
		 * @param the x position of the node
		 * @param the z position of the node
		 * @param whether the node is active(blue) or inactive(green)
		 * @param whether the node is a barrier(red) or not
		*/
		NavNode(CNavMesh *parentMeshIn, int x, int z, bool isActive, bool isBarrier);
		
		/**
		 * @brief Transform Updater
		 * @param the parentTransform
		*/
		void UpdateTransform(Transform parentTransform);

		/**
		 * @brief X position getter
		 * @return the node X position
		*/
		int GetXPos();

		/**
		 * @brief Z position getter
		 * @return the node Z position
		*/
		int GetZPos();

		/**
		 * @brief Grid Location Getter
		 * @return the node gridLocation position
		*/
		GridLocation GetLocation();

		/**
		 * @brief transform getter
		 * @return the current transform
		*/
		Transform* GetTransform();

		/**
		 * @brief Check if active or not
		 * @return the current active state
		*/
		bool GetActive();

		/**
		 * @brief Change the active state
		 * @param the new active state
		*/
		void SetActive(bool isActive);

		/**
		 * @brief get the current barrier state
		 * @return the current active state
		*/
		bool GetBarrier();

		/**
		 * @brief Check if active or not
		 * @return the current active state
		*/
		void SetBarrier(bool isBarrier);

		/**
		 * @brief Check which nodes are our neighbours
		*/
		void PopulateNeighbours();

		/**
		 * @brief Get the adjacent neighbour nodes
		 * @return the adjacent nodes
		*/
		std::vector<NavNode *> GetNeighbours();

		/**
		 * @brief Update the neighbour nodes
		 * @param active status
		*/
		void UpdateNeighbours(bool isActive);

		//Grid location helpers

	/**
	 * @brief comparator override
	 * @param first nav Node
	 * @param second nav Node
	*/
	friend bool operator == (NavNode a, NavNode b)
	{
		return a.nodeLocation.x == b.nodeLocation.x && a.nodeLocation.z == b.nodeLocation.z;
	}

	/**
	 * @brief not override
	 * @param first nav Node
	 * @param second nav Node
	*/
	friend bool operator != (NavNode a, NavNode b)
	{
		return !(a == b);
	}

	/**
	 * @brief less than override
	 * @param first nav Node
	 * @param second nav Node
	*/
	friend bool operator < (NavNode a, NavNode b)
	{
		return std::tie(a.nodeLocation.x, a.nodeLocation.z) < std::tie(b.nodeLocation.x, b.nodeLocation.z);
	}

	/**
	 * @brief output override
	 * @param first nav Node
	 * @param second nav Node
	*/
	friend std::basic_iostream<char>::basic_ostream &operator<<(std::basic_iostream<char>::basic_ostream &out, const NavNode &loc)
	{
		out << '(' << loc.nodeLocation.x << ',' << loc.nodeLocation.z << ')';
		return out;
	}

	private:

		/**
		 * @brief pointer to the parentMesh
		*/
		CNavMesh *parentMesh;

		/**
		 * @brief the node's location in the grid
		*/
		GridLocation nodeLocation;

		/**
		 * @brief the nodes transform
		*/
		Transform transform;

		/**
		 * @brief active state of the node
		*/
		bool active;

		/**
		 * @brief barrier state of the node
		*/
		bool barrier;

		//float dirs[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
		//GridLocation dirs[4] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

		/**
		 * @brief vector of neighbouring nodes
		*/
		std::vector<NavNode*> m_neighbourNodes;

};





