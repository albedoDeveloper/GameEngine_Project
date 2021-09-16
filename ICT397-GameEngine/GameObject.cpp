#include "GameObject.h"
#include "GameObjectFactory.h"

GameObject::GameObject()
	:m_components{}, m_factoryKey{}, m_isActive{ true }, m_transform{ }, m_static{ false }
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

CStaticMesh* GameObject::GetCStaticMesh()
{
	return GetComponent<CStaticMesh>();
}

CSound* GameObject::AddCSound()
{
	return AddComponent<CSound>();
}

CSound* GameObject::GetCSound()
{
	return GetComponent<CSound>();
}

void GameObject::SetStatic(bool isStatic)
{
	m_static = isStatic;
}

CCharacter* GameObject::AddCCharacter()
{
	return AddComponent<CCharacter>();
}

CCamera* GameObject::AddCCameraComponent()
{
	return AddComponent<CCamera>();
}

CPointLight* GameObject::AddCPointLight()
{
	return AddComponent<CPointLight>();
}

CPointLight* GameObject::GetCPointLight()
{
	return GetComponent<CPointLight>();
}

CCamera* GameObject::GetCCamera()
{
	return GetComponent<CCamera>();
}

bool GameObject::IsStatic() const
{
	return m_static;
}

CCharacter* GameObject::GetCCharacter()
{
	return GetComponent<CCharacter>();
}

CCollider* GameObject::GetCCollider()
{
	return GetComponent<CCollider>();
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
		for (std::unordered_map<std::type_index, std::list<CComponent*>*>::iterator mapIterator = m_components.begin(); mapIterator != m_components.end(); ++mapIterator)
		{
			// iterate through all components in list
			for (std::list<CComponent*>::iterator listIterator = (*mapIterator).second->begin(); listIterator != (*mapIterator).second->end(); ++listIterator)
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
		for (std::unordered_map<std::type_index, std::list<CComponent*>*>::iterator mapIterator = m_components.begin(); mapIterator != m_components.end(); ++mapIterator)
		{
			// iterate through all components in list
			for (std::list<CComponent*>::iterator listIterator = (*mapIterator).second->begin(); listIterator != (*mapIterator).second->end(); ++listIterator)
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
		for (auto mapIterator = m_components.begin(); mapIterator != m_components.end(); ++mapIterator)
		{
			// iterate through all components in list
			for (std::list<CComponent*>::iterator listIterator = (*mapIterator).second->begin(); listIterator != (*mapIterator).second->end(); ++listIterator)
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
		for (auto mapIterator = m_components.begin(); mapIterator != m_components.end(); ++mapIterator)
		{
			// iterate through all components in list
			for (std::list<CComponent*>::iterator listIterator = (*mapIterator).second->begin(); listIterator != (*mapIterator).second->end(); ++listIterator)
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
	for (std::unordered_map<std::type_index, std::list<CComponent*>*>::iterator mapIterator = m_components.begin(); mapIterator != m_components.end(); ++mapIterator)
	{
		// iterate through all components in list
		for (std::list<CComponent*>::iterator listIterator = (*mapIterator).second->begin(); listIterator != (*mapIterator).second->end(); ++listIterator)
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
			if (GetComponent<CScript>()) 
			{
				GetComponent<CScript>()->AssignScriptByKey(j.at(getFactoryKey()).at("Components").at("ScriptComponent").at("Script"));
			}
			else 
			{
				AddCScript()->AssignScriptByKey(j.at(getFactoryKey()).at("Components").at("ScriptComponent").at("Script"));
			}
		}

		if (it.key() == "StaticMeshComponent")
		{
			if (GetComponent<CStaticMesh>())
			{
				GetComponent<CStaticMesh>()->AssignModelByKey(j.at(getFactoryKey()).at("Components").at("StaticMeshComponent").at("AModel"));
			}
			else 
			{
				AddCStaticMesh()->AssignModelByKey(j.at(getFactoryKey()).at("Components").at("StaticMeshComponent").at("AModel"));
			}
		}

		if (it.key() == "AABBComponent")
		{
			if (GetComponent<CCollider>()) 
			{
				std::cout << "collider already exists" << std::endl;
				GetComponent<CCollider>()->UpdateCollider();
			}
			else
			{
				CCollider* col = AddCCollider();
				
				col->Load(j);
			}
		}
	}
}

std::unordered_map<std::type_index, std::list<CComponent*>*> GameObject::GetComponentMap() 
{
	return m_components;
}