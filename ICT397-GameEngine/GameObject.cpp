#include "GameObject.h"
#include "GameObjectFactory.h"

GameObject::GameObject()
	:m_components{}, m_factoryKey{}, m_isActive{ true }
{
}

CStaticMesh* GameObject::AddCStaticMesh()
{
	return AddComponent<CStaticMesh>();
}

CScript* GameObject::AddCScript()
{
	return AddComponent<CScript>();
}

CStateMachineAI* GameObject::AddCStateMachineAI()
{
	return AddComponent<CStateMachineAI>();
}

CStateMachineAI* GameObject::GetCStateMachineAI()
{
	return GetComponent<CStateMachineAI>();
}

CUserInterface* GameObject::AddCUserInterface()
{
	return AddComponent<CUserInterface>();
}

CUserInterface* GameObject::GetCUserInterface()
{
	return GetComponent<CUserInterface>();
}

CStaticMesh* GameObject::GetCStaticMesh()
{
	return GetComponent<CStaticMesh>();
}

CCharacter* GameObject::AddCCharacter()
{
	return AddComponent<CCharacter>();
}

CCamera* GameObject::AddCCameraComponent()
{
	return AddComponent<CCamera>();
}

CGridComponent* GameObject::AddCGridComponent() 
{
	return AddComponent<CGridComponent>();
}

CTerrainBruteForce* GameObject::AddCTerrainBruteForce(float xScale, float yScale, float zScale)
{
	CTerrainBruteForce* t = AddComponent<CTerrainBruteForce>();
	t->GetTransform().SetScale(Vector3f(xScale, yScale, zScale));
	return t;
}

CTerrainBruteForce* GameObject::GetCTerrainBruteForce()
{
	return GetComponent<CTerrainBruteForce>();
}

CCamera* GameObject::GetCCamera()
{
	return GetComponent<CCamera>();
}

CCharacter* GameObject::GetCCharacter()
{
	return GetComponent<CCharacter>();
}

Transform* GameObject::GetTransform()
{
	return &m_transform;
}

GameObject* GameObject::GetClosestObject(std::string partialKey)
{
	return GAMEOBJECT->getClosestObject(&m_transform, partialKey);
}

CAABBCollider* GameObject::AddCAABBCollider()
{
	return AddComponent<CAABBCollider>();
}

CSpotlight* GameObject::AddCSpotlight()
{
	return AddComponent<CSpotlight>();
}

CSpotlight* GameObject::GetCSpotlight()
{
	return GetComponent<CSpotlight>();
}

CWater* GameObject::AddCWaterComponent()
{
	return AddComponent<CWater>();
}

std::string GameObject::getFactoryKey() {
	return m_factoryKey;
}

void GameObject::setFactoryKey(std::string key) {
	this->m_factoryKey = key;
}

void GameObject::SetActive(bool activeStatus)
{
	m_isActive = activeStatus;
	if (activeStatus)
	{
		Start();
	}
}

void GameObject::SetDifficulty(std::string difficulty)
{
	m_difficulty = difficulty;
	if (m_isActive)
	{
		Start();
	}
}

std::string GameObject::GetDifficulty()
{
	return m_difficulty;
}

void GameObject::Start()
{
	m_initialActivation = m_isActive;
	
	m_initTransform = new Transform();
	m_initTransform.SetPositionV(m_transform.GetPosition());
	m_initTransform.SetRotation(m_transform.GetRotation());
	m_initTransform.SetScale(m_transform.GetScale());

	if (m_isActive)
	{
		// iterate through all component lists
		for (std::unordered_map<std::type_index, std::list<Component*>*>::iterator mapIterator = m_components.begin(); mapIterator != m_components.end(); ++mapIterator)
		{
			// iterate through all components in list
			for (std::list<Component*>::iterator listIterator = (*mapIterator).second->begin(); listIterator != (*mapIterator).second->end(); ++listIterator)
			{
				(*listIterator)->Start();
			}
		}
	}
}

void GameObject::Update()
{
	if (m_isActive)
	{
		// iterate through all component lists
		for (std::unordered_map<std::type_index, std::list<Component*>*>::iterator mapIterator = m_components.begin(); mapIterator != m_components.end(); ++mapIterator)
		{
			// iterate through all components in list
			for (std::list<Component*>::iterator listIterator = (*mapIterator).second->begin(); listIterator != (*mapIterator).second->end(); ++listIterator)
			{
				(*listIterator)->Update();
			}
		}
	}
}

void GameObject::Render()
{
	if (m_isActive)
	{
		// iterate through all component lists
		for (std::unordered_map<std::type_index, std::list<Component*>*>::iterator mapIterator = m_components.begin(); mapIterator != m_components.end(); ++mapIterator)
		{
			// iterate through all components in list
			for (std::list<Component*>::iterator listIterator = (*mapIterator).second->begin(); listIterator != (*mapIterator).second->end(); ++listIterator)
			{
				(*listIterator)->Render();
			}
		}
	}
}

void GameObject::LateRender()
{
	if (m_isActive)
	{
		// iterate through all component lists
		for (std::unordered_map<std::type_index, std::list<Component*>*>::iterator mapIterator = m_components.begin(); mapIterator != m_components.end(); ++mapIterator)
		{
			// iterate through all components in list
			for (std::list<Component*>::iterator listIterator = (*mapIterator).second->begin(); listIterator != (*mapIterator).second->end(); ++listIterator)
			{
				(*listIterator)->LateRender();
			}
		}
	}
}

void GameObject::Restart()
{
	m_isActive = m_initialActivation;

	m_transform.SetPositionV(m_initTransform.GetPosition());
	m_transform.SetRotation(m_initTransform.GetRotation());
	m_transform.SetScale(m_initTransform.GetScale());

	// iterate through all component lists
	for (std::unordered_map<std::type_index, std::list<Component*>*>::iterator mapIterator = m_components.begin(); mapIterator != m_components.end(); ++mapIterator)
	{
		// iterate through all components in list
		for (std::list<Component*>::iterator listIterator = (*mapIterator).second->begin(); listIterator != (*mapIterator).second->end(); ++listIterator)
		{
			(*listIterator)->Restart();
		}
	}
}

void GameObject::Save()
{
	m_savedActivation = m_isActive;

	m_savedTransform = new Transform();
	m_savedTransform.SetPositionV(m_transform.GetPosition());
	m_savedTransform.SetRotation(m_transform.GetRotation());
	m_savedTransform.SetScale(m_transform.GetScale());

	// iterate through all component lists
	for (std::unordered_map<std::type_index, std::list<Component*>*>::iterator mapIterator = m_components.begin(); mapIterator != m_components.end(); ++mapIterator)
	{
		// iterate through all components in list
		for (std::list<Component*>::iterator listIterator = (*mapIterator).second->begin(); listIterator != (*mapIterator).second->end(); ++listIterator)
		{
			(*listIterator)->Save();
		}
	}
}

void GameObject::Load()
{
	m_isActive = m_savedActivation;

	m_transform.SetPositionV(m_savedTransform.GetPosition());
	m_transform.SetRotation(m_savedTransform.GetRotation());
	m_transform.SetScale(m_savedTransform.GetScale());

	// iterate through all component lists
	for (std::unordered_map<std::type_index, std::list<Component*>*>::iterator mapIterator = m_components.begin(); mapIterator != m_components.end(); ++mapIterator)
	{
		// iterate through all components in list
		for (std::list<Component*>::iterator listIterator = (*mapIterator).second->begin(); listIterator != (*mapIterator).second->end(); ++listIterator)
		{
			(*listIterator)->Load();
		}
	}
}