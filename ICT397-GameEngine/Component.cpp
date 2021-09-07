#include "Component.h"
#include "GameObject.h"

#include <iostream>

Component::Component() 
	:m_parent{ nullptr }
{
	transform = new Transform();
}

Component::Component(Transform* parentTrans, GameObject* parentObject)
	:m_transform{ parentTrans }, m_parent{ parentObject }
{
}

Transform& Component::GetTransform()
{
	return m_transform;
}

const Transform& Component::GetTransformConst() const
{
	return m_transform;
}

GameObject* Component::GetParentObject()
{
	return m_parent;
}

void Component::Save(nlohmann::json& j)
{
	GameObject* g = GetParentObject();
	j[g->getFactoryKey()]["Components"]["Component"] = "Component";
 
	//m_transform.ToJson(j, g->getFactoryKey());
}

void Component::Load(nlohmann::json& j)
{
	GameObject* g = GetParentObject();
	//m_transform.FromJson(j, g->getFactoryKey());
}

void Component::DrawToImGui()
{
	//ImGui::Indent();
	ImGui::Text("Default Component");


}