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

Model* CStaticMesh::GetModel()
{
	return m_model;
}

Model* CStaticMesh::AssignModelByKey(std::string modelKey)
{
	Model* model = static_cast<Model*>(ASSET->GetAsset(modelKey));
	if (model == nullptr)
	{
		std::cout << "ERROR ASSIGNING MODEL BY KEY : " << modelKey << std::endl;
		exit(-23);
	}
	m_model = model;
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