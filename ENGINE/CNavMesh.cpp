#include "CNavMesh.h"
#include "GameObjectFactory.h"

CNavMesh::CNavMesh(Transform *parent, GameObject *parentObj)
	:CComponent{ parent, parentObj }
{
	
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
	
}
