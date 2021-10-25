#include "CNavMesh.h"
#include "GameObjectFactory.h"
#include "InputManager.h"



CNavMesh::CNavMesh(Transform *parent, GameObject *parentObj)
	:CComponent{ parent, parentObj }
{
	GenerateNavMesh();
}

void CNavMesh::Start()
{
	
}

void CNavMesh::Update()
{
	for (auto it : m_navNodes)
	{
		it->UpdateTransform(this->m_transform);

	}

	if (INPUT->GetKeyDown('s'))
	{
		Scan();
	}
	
}

void CNavMesh::Render()
{
	if(GRAPHICS->m_drawDebug)
		GRAPHICS->DrawDebugNavMesh(this , m_transform.GetWorldTransform());
}

void CNavMesh::Save(nlohmann::json &j)
{
	
}

void CNavMesh::Load(nlohmann::json &j)
{
	
}

void CNavMesh::DrawToImGui()
{
	
}

void CNavMesh::GenerateNavMesh()
{
	int i = 0;
	for (int x = -5; x < 5; x++)
	{
		for (int z = -5; z < 5; z++)
		{
			i++;
			bool active = true;
			if(z==2 && x == 2)
			{
				active = false;
			}

			NavNode *newNode = new NavNode(this, x, z,active);
			m_navNodes.emplace_back(newNode);
			//std::cout << "Nav node is of size " << i << std::endl;
		}
		
	}


	int loopCounter = 0;

	for (auto it : m_navNodes)
	{
		loopCounter++;
		it->PopulateNeighbours();
	}


	//after we have generated the nodes and the neighbours we need to populate into the graph
	for (size_t i = 0; i < m_navNodes.size() - 1; i++)
	{

		nodeGraph.edges.insert({ m_navNodes[i],{m_navNodes[i]->GetNeighbours()} });
	}
	
}

std::vector<NavNode *> CNavMesh::GetNavNodes()
{
	return m_navNodes;
}

NavNode* CNavMesh::FetchNode(int x, int z)
{
	NavNode* returnNode = NULL;

	for (auto it : m_navNodes)
	{
		if (it->GetXPos() == x && it->GetZPos() == z)
		{
			returnNode = it;
		}
	}

	if (returnNode == NULL)
	{
		//std::cout << "Output x = " << x << " z = " << z << std::endl;

	}

	return returnNode;
}

void CNavMesh::Scan()
{
	//generates graph
	/*for (size_t i = 0; i < m_navNodes.size() - 1; i++)
	{
		
		nodeGraph.edges.insert(  {m_navNodes[i],{m_navNodes[i]->GetNeighbours()} } );
	}*/

	std::cout << "graph size  = " << nodeGraph.edges.size() << std::endl;

	for (size_t i = 0; i < nodeGraph.edges.size(); i++)
	{
		for (size_t j = 0; j < nodeGraph.neighbors(m_navNodes[i]).size(); j++)
		{
			std::cout << "at node i = " << i << ", neighbours j =" << j << " node value x = " << nodeGraph.neighbors(m_navNodes[i])[j]->GetXPos() <<
			 "node value z = " << nodeGraph.neighbors(m_navNodes[i])[j]->GetZPos() << std::endl;
		}
	}
	


}

void CNavMesh::DijkstraSearch(
	Graph graph, NavNode* start, NavNode* goal,
	std::unordered_map<NavNode*, NavNode *> &came_from,
	std::unordered_map<NavNode*, double> &cost_so_far)
{
	PriorityQueue<NavNode*, double> frontier;
	frontier.put(start, 0);

	came_from[start] = start;
	cost_so_far[start] = 0;

	Scan();

	/*while (!frontier.empty())
	{
		GridLocation current = frontier.get();

		if (current == goal)
		{
			break;
		}

		for (GridLocation next : graph.neighbors(current))
		{
			double new_cost = cost_so_far[current] + graph.cost(current, next);
			if (cost_so_far.find(next) == cost_so_far.end()
				|| new_cost < cost_so_far[next])
			{
				cost_so_far[next] = new_cost;
				came_from[next] = current;
				frontier.put(next, new_cost);
			}
		}
	}*/
}

