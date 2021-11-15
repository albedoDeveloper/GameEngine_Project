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


	/**
	 * @brief A graph of nodes and their respective neighbours
	*/
struct Graph
{
	double cost;
	std::unordered_map<NavNode *, std::vector<NavNode *> > edges;

	std::vector<NavNode *> neighbors(NavNode *id)
	{
		return edges[id];
	}
};

	/**
	 * @brief A priority queue to order nodes by cost
	*/
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
		 * @param json save file
		*/
	virtual void Save(nlohmann::json &j);

		/**
		 * @brief loads the component from saved state
		 * @param json save file
		*/
	virtual void Load(nlohmann::json &j);

		/**
		 * @brief Draws to imgui
		*/
	virtual void DrawToImGui();

		/**
		 * @brief Creates the nave mesh nodes
		*/
	void GenerateNavMesh();

		/**
		 * @brief Assigns barriers to the nave mesh nodes
		 * @param the x position of the node
		 * @param the z position of the node
		 * @return the bool whether the barrier is on or off
		*/
	bool AssignBarriers(int x, int z);

		/**
		 * @brief Retrieves the Navigation Nodes vector
		 * @return the vector of navigation nodes
		*/
	std::vector<NavNode *> GetNavNodes();

		/**
		 * @brief Retrieves the NodeGraph (list of nodes & their connected neighbour nodes)
		 * @return the graph of navigation nodes
		*/
	Graph GetNodeGraph();


	GridLocation* GetDirs();

		/**
		 * @brief Retrieves a specific navNode
		 * @param the x position of the node
		 * @param the z position of the node
		 * @return the NavNode at position x & y
		*/
	NavNode *FetchNode(int x, int z);

		/**
		 * @brief Retrieves the nearest navNode 
		 * @param the position of the node
		 * @return the NavNode nearest to position
		*/
	NavNode* FindNearest(Vector3f pos);

		/**
		 * @brief runs a dijkstra scan from the first node to the node on the current index
		 * @param the node index
		*/
	void Scan(int i);

		/**
		 * @brief Runs a breadth first search
		 * @param the node graph
		 * @param the beginning node
		 * @param the destnation node
		 * @return Navnode map, this is the calculated path
		*/
	std::unordered_map<NavNode* , NavNode* > breadth_first_search(Graph graph, NavNode* start, NavNode* goal);

		/**
		 * @brief Runs a Dijkstra Search, note: we dont need to pass the graph
		 * @param the node graph
		 * @param the beginning node
		 * @param the destnation node
		 * @return Navnode map, this is the calculated path
		*/
	
	std::vector<NavNode* > DijkstraSearch(
	NavNode* start, NavNode* goal,
	std::unordered_map<NavNode*, NavNode*>& came_from,
	std::unordered_map<NavNode*, double>& cost_so_far
	);

		/**
		 * @brief Reconstructs the calculated path
		 * @param the node graph
		 * @param the beginning node
		 * @param the destnation node
		 * @return Navnode map, this is the calculated path
		*/
	std::vector<NavNode* > reconstruct_path(
   NavNode* start, NavNode *goal,
   std::unordered_map<NavNode*, NavNode*> came_from
	);


public:

	

private:

		/**
		 * @brief The directions of each neighbour forward, backward, left, right
		*/
		GridLocation dirs[4] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

		/**
		 * @brief The directions of each neighbour forward, backward, left, right
		*/
		Graph nodeGraph;

		/**
		 * @brief The list of nav nodes
		*/
		std::vector<NavNode*> m_navNodes;

		/**
		 * @brief The navMesh width
		*/
		int width;

		/**
		 * @brief The navMesh length
		*/
		int length;

		/**
		 * @brief Where the calculated path last came from
		*/
		std::unordered_map<NavNode *, NavNode *> came_from;

		/**
		 * @brief The cost of the path so far
		*/
		std::unordered_map<NavNode *, double> cost_so_far;

		/**
		 * @brief The currently calculated path
		*/
		std::vector<NavNode *> path;

		/**
		 * @brief The current increment (used for debugging with x)
		*/
		int increment = 0;
	
};
