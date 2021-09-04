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
	m_initTransform = new Transform();
	m_initTransform.SetPositionV(m_transform.GetPosition());
	m_initTransform.SetRotation(m_transform.GetRotation());
	m_initTransform.SetScale(m_transform.GetScale());
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

void Component::Restart()
{
	m_transform.SetPositionV(m_initTransform.GetPosition());
	m_transform.SetRotation(m_initTransform.GetRotation());
	m_transform.SetScale(m_initTransform.GetScale());

	Start();
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