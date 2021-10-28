#include "CNavMesh.h"
#include "GameObjectFactory.h"
#include "InputManager.h"



CNavMesh::CNavMesh(Transform *parent, GameObject *parentObj)
	:CComponent{ parent, parentObj }
{
	GenerateNavMesh();

	width = 24;
	length = 10;
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

	if (INPUT->GetKeyDown('x'))
	{
		if (increment < 240)
		{
			increment++;
		}
		else
		{
			increment = 0;
		}
		Scan(increment);
	}

}

void CNavMesh::Render()
{

	//btVector3 vec1 = btVector3(m_navNodes[0]->GetTransform()->GetWorldTransform().GetRelativePosition().GetX(), m_navNodes[0]->GetTransform()->GetRelativePosition().GetY(), m_navNodes[0]->GetTransform()->GetRelativePosition().GetZ());
	//btVector3 vec2 = btVector3(m_navNodes[50]->GetTransform()->GetRelativePosition().GetX(), m_navNodes[50]->GetTransform()->GetRelativePosition().GetY(), m_navNodes[50]->GetTransform()->GetRelativePosition().GetZ());

	Vector3f vec1 = Vector3f(1, 2, 3);
	Vector3f vec2 = Vector3f(3, 2, 1);

	if (GRAPHICS->m_drawDebug)
	{
		GRAPHICS->DrawDebugNavMesh(this, m_transform.GetWorldTransform());

		//GRAPHICS->DrawLine(vec1, vec2, Vector3f(1.0f, 0.5f, 0.5f));

	}

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
	for (int x = -12; x < 12; x++)
	{
		for (int z = -5; z < 5; z++)
		{
			i++;
			bool active = !AssignBarriers(x, z);
			bool barrier = AssignBarriers(x, z);

			//assign barriers


			NavNode *newNode = new NavNode(this, x, z, active, barrier);
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
		if (!m_navNodes[i]->GetBarrier())
			nodeGraph.edges.insert({ m_navNodes[i],{m_navNodes[i]->GetNeighbours()} });
	}

}

bool CNavMesh::AssignBarriers(int x, int z)
{
	bool returnBool = false;

	//COLLISION.

	/*if (z == 0 && (x == -1 || x == -2 || x == -3 || x == -4 || x == -5 || x == 0 || x == 1 || x == 2 || x == 3 || x == 4 || x == 5))
	{
		returnBool = true;
	}*/

	//pool table
	if ((x == -9 || x == -8) && (z == 1 || z == 0 || z == -1))
	{
		returnBool = true;
	}

	//barrel1
	if ((x == 4 || x == 5) && (z == -1 || z == 0))
	{
		returnBool = true;
	}

	//barrel2
	if ((x >= -9) && (z == -5))
	{
		returnBool = true;
	}

	if ((x == -4 || x == -5) && (z == 3 || z == 4))
	{
		returnBool = true;
	}

	//jukebox
	if ((x == -3 || x == -2) && (z == -2 || z == -3))
	{
		returnBool = true;
	}

	//table
	if ((x == 7) && (z == -2 || z == -3))
	{
		returnBool = true;
	}

	//wall
	if ((x == -5 || x == -4 || x == -3 || x == -2 || x == -1 || x == 0 || x == 1) && (z == -5 || z == -4 || z == -3))
	{
		returnBool = true;
	}

	//bar
	if ((x == 6 || x == 7 || x == 8 || x == 9 || x == 10) && (z == 4 || z == 5))
	{
		returnBool = true;
	}

	if (x == 11)
	{
		returnBool = true;
	}

	return returnBool;
}

std::vector<NavNode *> CNavMesh::GetNavNodes()
{
	return m_navNodes;
}


Graph CNavMesh::GetNodeGraph()
{
	return nodeGraph;
}

NavNode *CNavMesh::FetchNode(int x, int z)
{
	NavNode *returnNode = NULL;

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

NavNode *CNavMesh::FindNearest(Vector3f pos)
{
	float shortestDst = 100;
	int nodeIndex = 0;

	for (int i = 0; i < m_navNodes.size(); i++)
	{
		if (!m_navNodes[i]->GetBarrier())
		{
			Vector3f diff = pos - m_navNodes[i]->GetTransform()->GetWorldTransform().GetRelativePosition();
			float curDst = diff.Magnitude();



			if (curDst < shortestDst)
			{
				shortestDst = curDst;
				nodeIndex = i;
			}

		}


	}

	return m_navNodes[nodeIndex];

}

void CNavMesh::Scan(int i)
{


	Vector3f positionVec{ 0,1,0 };
	//std::cout << "dst at x =" << FindNearest(positionVec)->GetXPos() << " z = " << FindNearest(positionVec)->GetZPos() << std::endl;



	//clear prior
	came_from.clear();
	cost_so_far.clear();
	//generates graph
	for (size_t i = 0; i < m_navNodes.size() - 1; i++)
	{

		m_navNodes[i]->SetActive(true);
	}

	std::cout << "node at x =" << m_navNodes[i]->GetXPos() << " z = " << m_navNodes[i]->GetZPos() << std::endl;


	//Print out graph
	/*for (size_t i = 0; i < nodeGraph.edges.size(); i++)
	{
		for (size_t j = 0; j < nodeGraph.neighbors(m_navNodes[i]).size(); j++)
		{
			std::cout << "at node i = " << i << ", neighbours j =" << j << " node value x = " << nodeGraph.neighbors(m_navNodes[i])[j]->GetXPos() <<
			 "node value z = " << nodeGraph.neighbors(m_navNodes[i])[j]->GetZPos() << std::endl;
		}
	}*/

	//breadth_first_search(nodeGraph, m_navNodes[0], m_navNodes[i]);

	if (m_navNodes[i] != NULL)
	{
		DijkstraSearch(m_navNodes[0], m_navNodes[i], came_from, cost_so_far);

		//reconstruct_path(m_navNodes[0], m_navNodes[i], came_from);
	}



}

std::unordered_map<NavNode *, NavNode * > CNavMesh::breadth_first_search(Graph graph, NavNode *start, NavNode *goal)
{
	std::queue<NavNode *> frontier;
	frontier.push(start);

	std::unordered_map<NavNode *, NavNode * > came_from;
	came_from[start] = start;

	while (!frontier.empty())
	{
		NavNode *current = frontier.front();
		frontier.pop();

		current->SetActive(false);

		if (current == goal)
		{
			break;
		}

		for (NavNode *next : graph.neighbors(current))
		{
			if (came_from.find(next) == came_from.end())
			{
				frontier.push(next);
				came_from[next] = current;



			}
		}
	}
	return came_from;
}

std::vector<NavNode *> CNavMesh::DijkstraSearch(
	NavNode *start, NavNode *goal,
	std::unordered_map<NavNode *, NavNode *> &came_from,
	std::unordered_map<NavNode *, double> &cost_so_far)
{

	std::vector<NavNode *> path;

	PriorityQueue<NavNode *, double> frontier;
	frontier.put(start, 0);

	came_from[start] = start;
	cost_so_far[start] = 0;


	bool isEmpty = frontier.empty();

	while (!frontier.empty())
	{


		NavNode *current = frontier.get();

	//current->SetActive(false);
		//std::cout << "frontier size = " << frontier.elements.size() << std::endl;

		if (current == goal)
		{
			break;
		}

		for (NavNode *next : nodeGraph.neighbors(current))
		{
			double new_cost = cost_so_far[current] + 1;
			//double new_cost = cost_so_far[current] + graph.cost(current, next);

			if (cost_so_far.find(next) == cost_so_far.end()
				|| new_cost < cost_so_far[next])
			{
				cost_so_far[next] = new_cost;
				came_from[next] = current;
				frontier.put(next, new_cost);
			}
		}


		if (frontier.elements.size() == 0)
		{
			isEmpty = true;
		}
	}

	if (!isEmpty)
	{
		path = reconstruct_path(start, goal, came_from);
	}

	return path;
}

std::vector<NavNode *> CNavMesh::reconstruct_path(
   NavNode *start, NavNode *goal,
   std::unordered_map<NavNode *, NavNode *> came_from
)
{
	std::vector<NavNode *> path;
	NavNode *current = goal;

	current->SetActive(false);
	while (current != start)
	{
		path.push_back(current);
		current = came_from[current];

		if (current != NULL)
		{
			current->SetActive(false);
			//std::cout << "current x = " << current->GetXPos() << ": z = " << current->GetZPos() << std::endl;
		}
	}

	current->SetActive(false);

	path.push_back(start); // optional
	std::reverse(path.begin(), path.end());
	return path;
}

