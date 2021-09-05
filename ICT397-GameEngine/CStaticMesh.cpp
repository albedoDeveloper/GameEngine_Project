#include "CStaticMesh.h"
#include "GraphicsEngine.h"
#include "GameAssetFactory.h"
#include "GameObject.h"



#if _DEBUG
#include <iostream>
#endif

CStaticMesh::CStaticMesh(Transform* parent, GameObject* parentObj)
	:Component{ parent, parentObj}, m_model{ nullptr }
{
}

void CStaticMesh::AssignModel(Model* model)
{
	//m_model = model;

#if _DEBUG
	std::cout << "Model assigned to mesh. Model:" << model->key << std::endl;
#endif
}

Model* CStaticMesh::GetModel()
{
	return m_model;
}

Model* CStaticMesh::AssignModelByKey(std::string modelKey)
{
	m_model = static_cast<Model*>(ASSET->GetAsset(modelKey));
	AssignModel(m_model);
	return m_model;
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

void CStaticMesh::Save(nlohmann::json& j)
{
	GameObject* g = GetParentObject();
	j[g->getFactoryKey()]["Components"]["StaticMeshComponent"]["Model"] = m_model->key;

	//m_transform.ToJson(j, g->getFactoryKey());
}

void CStaticMesh::Load(nlohmann::json& j)
{
	GameObject* g = GetParentObject();
	//m_transform.FromJson(j, g->getFactoryKey());
}