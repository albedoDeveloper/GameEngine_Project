/*****************************************************************//**
*\file   CNavMesh.h
*\brief  Navigation Mesh Component
*
*\date   September 2021
* ********************************************************************/
#pragma once

#include "CComponent.h"
#include "NavNode.h"
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>



struct Graph
{
	double cost;
	std::unordered_map<NavNode*, std::vector<NavNode*> > edges;

	std::vector<NavNode*> neighbors(NavNode* id)
	{
		return edges[id];
	}

	/*std::unordered_set<GridLocation> forests;

	double cost(GridLocation from_node, GridLocation to_node) const
	{
		return forests.find(to_node) != forests.end() ? 5 : 1;
	}*/

	
};

template<typename T, typename priority_t>
struct PriorityQueue
{
	typedef std::pair<priority_t, T> PQElement;
	std::priority_queue<PQElement, std::vector<PQElement>,
		std::greater<PQElement>> elements;

	inline bool empty() const
	{
		return elements.empty();
	}

	inline void put(T item, priority_t priority)
	{
		elements.emplace(priority, item);
	}

	T get()
	{
		T best_item = elements.top().second;
		elements.pop();
		return best_item;
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

		/**
		 * @brief Retrieves a specific navNode
		*/
	NavNode* FetchNode(int x, int z);

	NavNode* FindNearest(Vector3f pos);

	void Scan(int i);

	std::unordered_map<NavNode* , NavNode* > breadth_first_search(Graph graph, NavNode* start, NavNode* goal);

	void DijkstraSearch(
	Graph graph, NavNode* start, NavNode* goal,
	std::unordered_map<NavNode*, NavNode*>& came_from,
	std::unordered_map<NavNode*, double>& cost_so_far
	);

	std::vector<NavNode* > reconstruct_path(
   NavNode* start, NavNode *goal,
   std::unordered_map<NavNode*, NavNode*> came_from
	);

	//public vars because i'm lazy and time is short
public:
	GridLocation dirs[4] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };


private:
		/**
		 * @brief The vars for this comp
		*/
		std::vector<NavNode*> m_navNodes;

		

		Graph nodeGraph;

		std::unordered_map<NavNode *, NavNode *> came_from;
		std::unordered_map<NavNode *, double> cost_so_far;

		std::vector<NavNode *> path;


		int increment = 0;
	
};
