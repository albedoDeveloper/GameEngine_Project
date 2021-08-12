#include "CStaticMesh.h"
#include "GraphicsEngine.h"
#include "GameAssetFactory.h"

#if _DEBUG
#include <iostream>
#endif

CStaticMesh::CStaticMesh(Transform* parent, GameObject* parentObj)
	:Component{ parent, parentObj}, m_model{ nullptr }
{
}

void CStaticMesh::AssignModel(AModel* model)
{
	m_model = model;

#if _DEBUG
	std::cout << "Model assigned to mesh. Model:" << model << std::endl;
#endif
}

AModel* CStaticMesh::GetModel()
{
	return m_model;
}

AModel* CStaticMesh::AssignModelByKey(std::string modelKey)
{
	AModel* model = static_cast<AModel*>(ASSET->GetAsset(modelKey));
	AssignModel(model);
	return model;
}

void CStaticMesh::Start()
{
}

void CStaticMesh::Update()
{
}

void CStaticMesh::Render()
{
	GRAPHICS->DrawModel(m_model, m_transform.GetWorldTransform());
}

void CStaticMesh::LateRender()
{}