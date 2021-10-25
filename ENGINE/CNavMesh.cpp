#include "CNavMesh.h"
#include "GameObjectFactory.h"



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
	//std::unordered_map
	for (NavNode* next : m_navNodes)
	{
		std::cout << "How does this work??" << std::endl;
	}

}

