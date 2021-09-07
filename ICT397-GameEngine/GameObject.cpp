#include "GameObject.h"
#include "GameObjectFactory.h"

GameObject::GameObject()
	:m_components{}, m_factoryKey{}, m_isActive{ true }, m_transform{ }
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

CCollider* GameObject::AddCCollider()
{
	return AddComponent<CCollider>();
}

CSpotlight* GameObject::AddCSpotlight()
{
	return AddComponent<CSpotlight>();
}

CSpotlight* GameObject::GetCSpotlight()
{
	return GetComponent<CSpotlight>();
}

void GameObject::SetParentObject(std::string newParent)
{
	GameObject* otherObject = GAMEOBJECT->GetGameObject(newParent);
	if (otherObject == nullptr)
	{
		std::cout << "ERROR SetParentObject(). Cannot find object by ID: " << newParent << std::endl;
		exit(-25);
	}
	m_transform.SetParent(otherObject->GetTransform());
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

void GameObject::Save(nlohmann::json& j)
{
	j[getFactoryKey()]["key"] = getFactoryKey();

	GetTransform()->ToJson(j, getFactoryKey());

	std::cout << "SAVED" << std::endl;

	// iterate through all component lists
	for (std::unordered_map<std::type_index, std::list<Component*>*>::iterator mapIterator = m_components.begin(); mapIterator != m_components.end(); ++mapIterator)
	{
		// iterate through all components in list
		for (std::list<Component*>::iterator listIterator = (*mapIterator).second->begin(); listIterator != (*mapIterator).second->end(); ++listIterator)
		{
			(*listIterator)->Save(j);
		}
	}
}

void GameObject::Load(nlohmann::json& j)
{
	std::cout << getFactoryKey() << std::endl;
	GetTransform()->FromJson(j, getFactoryKey());

	std::cout << j.at(getFactoryKey()).at("Components").size() << std::endl;

	for (auto it : j.at(getFactoryKey()).at("Components").items())
	{
		std::cout << "GO TEST" << it.key() << " | " << it.value() << std::endl;

		

		if (it.key() == "ScriptComponent")
		{
			AddCScript()->AssignScriptByKey(j.at(getFactoryKey()).at("Components").at("ScriptComponent").at("Script"));
		}

		if (it.key() == "StaticMeshComponent")
		{
			
			AddCStaticMesh()->AssignModelByKey(j.at(getFactoryKey()).at("Components").at("StaticMeshComponent").at("Model"));
		}

		if (it.key() == "AABBComponent")
		{
			if (GetComponent<CCollider>() == nullptr) 
			{
				CCollider* col = AddCCollider();
				col->Load(j);
			}
		}



	}
}

std::unordered_map<std::type_index, std::list<Component*>*> GameObject::GetComponentMap() 
{
	return m_components;
}