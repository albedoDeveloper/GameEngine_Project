#include "Component.h"
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

void Component::Save()
{
	m_initTransform = new Transform();
	m_savedTransform.SetPositionV(m_transform.GetPosition());
	m_savedTransform.SetRotation(m_transform.GetRotation());
	m_savedTransform.SetScale(m_transform.GetScale());
}

void Component::Load()
{
	m_transform.SetPositionV(m_savedTransform.GetPosition());
	m_transform.SetRotation(m_savedTransform.GetRotation());
	m_transform.SetScale(m_savedTransform.GetScale());
}