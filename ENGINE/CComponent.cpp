#include "CComponent.h"
#include "GameObject.h"

#include <iostream>

CComponent::CComponent(Transform *parentTrans, GameObject *parentObject)
	: m_transform{ parentTrans }, m_parent{ parentObject }, m_isActive{ true }
{
	m_transform.SetGameObject(m_parent);
}

Transform &CComponent::GetTransform()
{
	return m_transform;
}

const Transform &CComponent::GetTransformConst() const
{
	return m_transform;
}

GameObject *CComponent::GetParentObject()
{
	return m_parent;
}

void CComponent::SetIsActive(bool isActive)
{
	m_isActive = isActive;
}

void CComponent::Save(nlohmann::json &j)
{
	GameObject *g = GetParentObject();
	j[g->GetFactoryKey()]["Components"]["CComponent"] = "CComponent";
}

void CComponent::Load(nlohmann::json &j)
{
	GameObject *g = GetParentObject();
}

void CComponent::DrawToImGui()
{
	ImGui::Text("Default CComponent");
}
