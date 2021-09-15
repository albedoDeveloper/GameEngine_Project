#include "CStaticMesh.h"
#include "GraphicsEngine.h"
#include "GameAssetFactory.h"
#include "GameObject.h"
#include <iostream>
#include "InputManager.h" // debug

CStaticMesh::CStaticMesh(Transform* parent, GameObject* parentObj)
	:CComponent{ parent, parentObj}, 
	m_model{ nullptr },
	m_shader{ GRAPHICS->m_litShader }
{
}

CStaticMesh::~CStaticMesh()
{
	delete m_model;
}

AModel* CStaticMesh::GetModel()
{
	return m_model;
}

AModel* CStaticMesh::AssignModelByKey(std::string modelKey)
{
	AModel* model = static_cast<AModel*>(ASSET->GetAsset(modelKey));
	if (model == nullptr)
	{
		std::cout << "ERROR ASSIGNING MODEL BY KEY : " << modelKey << std::endl;
		exit(-23);
	}
	m_model = model;
	return m_model;
}

void CStaticMesh::AssignShader(std::string shader)
{
	if (!shader.compare("lit"))
	{
		m_shader = GRAPHICS->m_litShader;
	}
	else if (!shader.compare("unlit"))
	{
		m_shader = GRAPHICS->m_unlitShader;
	}
	else if (!shader.compare("debug"))
	{
		m_shader = GRAPHICS->m_debugShader;
	}
	else
	{
		std::cout << "ERROR: CStaticMesh::AssignShader ... invalid shader string entered\n";
	}
}

void CStaticMesh::Render()
{
	if (INPUT->GetKeyDownByCode(KeyCode::T) && m_shader == GRAPHICS->m_unlitShader)
	{
		m_shader = GRAPHICS->m_litShader;
	}
	else if (INPUT->GetKeyDownByCode(KeyCode::T) && m_shader == GRAPHICS->m_litShader)
	{
		m_shader = GRAPHICS->m_unlitShader;
	}

	GRAPHICS->DrawModel(m_model, m_transform.GetWorldTransform(), m_shader);
}

void CStaticMesh::Save(nlohmann::json& j)
{
	GameObject* g = GetParentObject();
	j[g->getFactoryKey()]["Components"]["StaticMeshComponent"]["AModel"] = m_model->key;

	//m_transform.ToJson(j, g->getFactoryKey());
}

void CStaticMesh::Load(nlohmann::json& j)
{
	GameObject* g = GetParentObject();
	//m_transform.FromJson(j, g->getFactoryKey());
}

void CStaticMesh::DrawToImGui()
{
	//ImGui::Text("staticMesh TREE");
	if (ImGui::TreeNode("StaticMesh CComponent"))
	{
		ImGui::Text("AModel Name : "); ImGui::SameLine(); ImGui::Text(m_model->key.c_str());
		ImGui::TreePop();
	}
}
