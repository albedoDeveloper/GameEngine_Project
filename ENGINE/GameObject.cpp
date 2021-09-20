#include "GameObject.h"
#include "GameObjectFactory.h"

GameObject::GameObject()
	:m_components{}, m_factoryKey{}, m_isActive{ true }, m_transform{ this }, m_static{ false }
{
}

CStaticMesh *GameObject::AddCStaticMesh()
{
	return AddComponent<CStaticMesh>();
}

CScript *GameObject::AddCScript()
{
	return AddComponent<CScript>();
}

CStaticMesh *GameObject::GetCStaticMesh()
{
	return GetComponent<CStaticMesh>();
}

CSound *GameObject::AddCSound()
{
	return AddComponent<CSound>();
}

CSound *GameObject::GetCSound()
{
	return GetComponent<CSound>();
}

void GameObject::SetStatic(bool isStatic)
{
	m_static = isStatic;
}

CCharacter *GameObject::AddCCharacter()
{
	return AddComponent<CCharacter>();
}

CCamera *GameObject::AddCCameraComponent()
{
	return AddComponent<CCamera>();
}

CPointLight *GameObject::AddCPointLight()
{
	return AddComponent<CPointLight>();
}

CDirectionalLight *GameObject::AddCDirectionalLight()
{
	return AddComponent<CDirectionalLight>();
}

CPointLight *GameObject::GetCPointLight()
{
	return GetComponent<CPointLight>();
}

CDirectionalLight *GameObject::GetCDirectionalLight()
{
	return GetComponent<CDirectionalLight>();
}

CCamera *GameObject::GetCCamera()
{
	return GetComponent<CCamera>();
}

bool GameObject::IsStatic() const
{
	return m_static;
}

CCharacter *GameObject::GetCCharacter()
{
	return GetComponent<CCharacter>();
}

CCollider *GameObject::GetCCollider()
{
	return GetComponent<CCollider>();
}

Transform *GameObject::GetTransform()
{
	return &m_transform;
}

//GameObject *GameObject::GetClosestObject(std::string partialKey)
//{
//	return GAMEOBJECT->GetClosestObject(&m_transform, partialKey);
//}

CCollider *GameObject::AddCCollider()
{
	return AddComponent<CCollider>();
}

void GameObject::SetParentObject(std::string newParent)
{
	GameObject *otherObject = GAMEOBJECT->GetGameObject(newParent);
	if (otherObject == nullptr)
	{
		std::cout << "ERROR SetParentObject(). Cannot find object by ID: " << newParent << std::endl;
		exit(-25);
	}
	m_transform.SetParent(otherObject->GetTransform());
}

std::string GameObject::GetFactoryKey()
{
	return m_factoryKey;
}

void GameObject::SetFactoryKey(std::string key)
{
	this->m_factoryKey = key;
}

bool GameObject::GetActive()
{
	return m_isActive;
}

void GameObject::SetActive(bool activeStatus)
{
	m_isActive = activeStatus;
	if (activeStatus)
	{
		Start();
	}
}


void GameObject::Start()
{
	if (m_isActive)
	{
		// iterate through all component lists
		for (std::unordered_map<std::type_index, std::list<CComponent *> *>::iterator mapIterator = m_components.begin(); mapIterator != m_components.end(); ++mapIterator)
		{
			// iterate through all components in list
			for (std::list<CComponent *>::iterator listIterator = (*mapIterator).second->begin(); listIterator != (*mapIterator).second->end(); ++listIterator)
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
		for (std::unordered_map<std::type_index, std::list<CComponent *> *>::iterator mapIterator = m_components.begin(); mapIterator != m_components.end(); ++mapIterator)
		{
			// iterate through all components in list
			for (std::list<CComponent *>::iterator listIterator = (*mapIterator).second->begin(); listIterator != (*mapIterator).second->end(); ++listIterator)
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
			for (std::list<CComponent *>::iterator listIterator = (*mapIterator).second->begin(); listIterator != (*mapIterator).second->end(); ++listIterator)
			{
				(*listIterator)->Render();
			}
		}
	}
}

void GameObject::Render(Shader &shaderOveride)
{
	if (m_isActive)
	{
		// iterate through all component lists
		for (auto mapIterator = m_components.begin(); mapIterator != m_components.end(); ++mapIterator)
		{
			// iterate through all components in list
			for (std::list<CComponent *>::iterator listIterator = (*mapIterator).second->begin(); listIterator != (*mapIterator).second->end(); ++listIterator)
			{
				(*listIterator)->Render(shaderOveride);
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
			for (std::list<CComponent *>::iterator listIterator = (*mapIterator).second->begin(); listIterator != (*mapIterator).second->end(); ++listIterator)
			{
				(*listIterator)->LateRender();
			}
		}
	}
}

void GameObject::Save(nlohmann::json &j)
{
	//first we store the name/key of the object
	j[GetFactoryKey()]["key"] = GetFactoryKey();

	GetTransform()->ToJson(j, GetFactoryKey());

	//then we store whether it is active or inactive
	j[GetFactoryKey()]["active"] = m_isActive;

	// iterate through all component lists
	for (std::unordered_map<std::type_index, std::list<CComponent *> *>::iterator mapIterator = m_components.begin(); mapIterator != m_components.end(); ++mapIterator)
	{
		// iterate through all components in list
		for (std::list<CComponent *>::iterator listIterator = (*mapIterator).second->begin(); listIterator != (*mapIterator).second->end(); ++listIterator)
		{
			(*listIterator)->Save(j);
		}
	}


	//assign parent if we have one
	if (GetTransform()->GetParent() != nullptr)
	{
		j[GetFactoryKey()]["parent"] = GetTransform()->GetParent()->GetGameObject()->GetFactoryKey();
		//j[GetFactoryKey()]["parent"] = "PARENT";
	}
	else
	{
		j[GetFactoryKey()]["parent"] = "TEST";
	}
}

void GameObject::Load(nlohmann::json &j)
{
	//std::cout << getFactoryKey() << std::endl;
	GetTransform()->FromJson(j, GetFactoryKey());

	//then we check whether it is active or inactive
	m_isActive = j.at(GetFactoryKey()).at("active");

	//we get teh number of components
	std::cout << j.at(GetFactoryKey()).at("Components").size() << std::endl;

	for (auto it : j.at(GetFactoryKey()).at("Components").items())
	{
		std::cout << "GO TEST" << it.key() << " | " << it.value() << std::endl;



		if (it.key() == "ScriptComponent")
		{
			if (GetComponent<CScript>())
			{
				GetComponent<CScript>()->AssignScriptByKey(j.at(GetFactoryKey()).at("Components").at("ScriptComponent").at("Script"));
			}
			else
			{
				AddCScript()->AssignScriptByKey(j.at(GetFactoryKey()).at("Components").at("ScriptComponent").at("Script"));
			}
		}

		if (it.key() == "StaticMeshComponent")
		{
			if (GetComponent<CStaticMesh>())
			{
				GetComponent<CStaticMesh>()->AssignModelByKey(j.at(GetFactoryKey()).at("Components").at("StaticMeshComponent").at("AModel"));
				GetComponent<CStaticMesh>()->Load(j);

			}
			else
			{
				AddCStaticMesh()->AssignModelByKey(j.at(GetFactoryKey()).at("Components").at("StaticMeshComponent").at("AModel"));
				GetComponent<CStaticMesh>()->Load(j);

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
				CCollider *col = AddCCollider();

				col->Load(j);
			}
		}
	}


	//Assign parent
	if (j.at(GetFactoryKey()).at("parent") != "TEST")
	{

		GameObject *myParent = GAMEOBJECT->GetGameObject(j.at(GetFactoryKey()).at("parent"));
		GetTransform()->SetParent(myParent->GetTransform());

		std::cout << GetFactoryKey() << " PARENT = " << GetTransform()->GetParent()->GetGameObject()->GetFactoryKey() << std::endl;
	}

}

std::unordered_map<std::type_index, std::list<CComponent *> *> GameObject::GetComponentMap()
{
	return m_components;
}