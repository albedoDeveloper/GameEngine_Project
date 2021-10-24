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
	
}

void CNavMesh::Render()
{
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
			NavNode *newNode = new NavNode(&this->m_transform, x, z);
			m_navNodes.emplace_back(newNode);
			i++;
			std::cout << "Nav node is of size " << i << std::endl;
		}
		
		
	}


	int loopCounter = 0;

	for (auto it : m_navNodes)
	{
		loopCounter++;
		std::cout << "Nav node "<< loopCounter <<" is at position x ="<< it->GetTransform()->GetRelativePosition().GetX() <<" and z = " << it->GetTransform()->GetRelativePosition().GetZ() << std::endl;

	}
	
}
std::vector<NavNode *> CNavMesh::GetNavNodes()
{
	return m_navNodes;
}

