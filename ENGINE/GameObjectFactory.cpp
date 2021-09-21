#include "GameObjectFactory.h"

GameObjectFactory::GameObjectFactory()
{
	m_objects = *new std::map<std::string, GameObject *>();
}

GameObjectFactory *GameObjectFactory::instance()
{
	static GameObjectFactory *factory = new GameObjectFactory();
	return factory;
}

std::map<std::string, GameObject *> *GameObjectFactory::GetObjectMap()
{
	return &m_objects;
}

GameObject *GameObjectFactory::GetGameObject(std::string key)
{
	if (m_objects.find(key) == m_objects.end())
	{
		std::cout << "GameObject (Key:" << key << ") not found\n";
		return nullptr;
	}

	if (m_objects.find(key) != m_objects.end())
	{
		return m_objects.at(key);
	}

}

//GameObject *GameObjectFactory::GetClosestObject(Transform *target, std::string partialKey)
//{
//	GameObject *closest = nullptr;
//
//	for (std::map<std::string, GameObject *>::iterator i = m_objects.begin(); i != m_objects.end(); i++)
//	{
//		if (i->second->getFactoryKey().find(partialKey) != std::string::npos)
//		{
//			if (closest == nullptr)
//			{
//				closest = i->second;
//			}
//			else
//			{
//				if (target->GetDistance(i->second->GetTransform()) < target->GetDistance(closest->GetTransform()) && i->second->GetTransform() != target)
//				{
//					closest = closest = i->second;
//				}
//			}
//		}
//	}
//
//	return closest;
//}

int GameObjectFactory::getNumObjects()
{
	return m_objects.size();
}

bool GameObjectFactory::CheckKey(const std::string &key)
{
	if (m_objects.find(key) == m_objects.end())
	{
		return false;
	}
	else
	{
		return true;
	}
}

GameObject *GameObjectFactory::SpawnGameObject()
{
	GameObject *object = new GameObject();

	static std::string key = "AAAA";
	while (m_objects.find(key) != m_objects.end())
	{
		iterateKey(key);
	}
	m_objects.emplace(key, object);
	object->SetFactoryKey(key);

	return object;
}

void GameObjectFactory::iterateKey(std::string &key)
{
	for (int place = 3; place >= 0; place--)
	{
		if (key[place] < 'Z')
		{
			key[place]++;
			return;
		}
		key[place] = 'A';
	}
	std::cout << "ran out of space in object factory";
}

GameObject *GameObjectFactory::SpawnGameObject(std::string key)
{
	if ((CheckKey(key)))
	{
		std::cout << "[Error] Object key (" << key << ") already taken\n";
		return nullptr;
	}

	GameObject *object = new GameObject();

	if (m_objects.find(key) != m_objects.end())
	{
		return nullptr;
	}
	m_objects.emplace(key, object);
	object->SetFactoryKey(key);

	return object;
}

void GameObjectFactory::Start()
{
	std::map<std::string, GameObject *>::iterator it;
	for (it = m_objects.begin(); it != m_objects.end(); it++)
	{
		it->second->Start();
	}
}

void GameObjectFactory::Update()
{
	std::map<std::string, GameObject *>::iterator it;
	for (it = m_objects.begin(); it != m_objects.end(); it++)
	{
		it->second->Update();
	}
}

void GameObjectFactory::Render()
{
	std::map<std::string, GameObject *>::iterator it;
	for (it = m_objects.begin(); it != m_objects.end(); it++)
	{
		it->second->Render();
	}
	for (it = m_objects.begin(); it != m_objects.end(); it++)
	{
		it->second->LateRender();
	}
}

void GameObjectFactory::Render(Shader &shaderOveride, bool noTexture)
{
	std::map<std::string, GameObject *>::iterator it;
	for (it = m_objects.begin(); it != m_objects.end(); it++)
	{
		it->second->Render(shaderOveride, noTexture);
	}
	for (it = m_objects.begin(); it != m_objects.end(); it++)
	{
		it->second->LateRender();
	}
}

void GameObjectFactory::Save(nlohmann::json &j)
{
	std::map<std::string, GameObject *>::iterator it;
	for (it = m_objects.begin(); it != m_objects.end(); it++)
	{
		it->second->Save(j);
	}
}

void GameObjectFactory::Load(nlohmann::json &j)
{
	std::map<std::string, GameObject *>::iterator it;
	for (it = m_objects.begin(); it != m_objects.end(); it++)
	{
		it->second->Load(j);
	}
}

void GameObjectFactory::Close()
{
	m_objects = *new std::map<std::string, GameObject *>();
}

void GameObjectFactory::ClearCurrentLevel()
{

	//std::map<std::string, GameObject *> *gameObjects = GAMEOBJECT->GetObjectMap();

	std::map<std::string, GameObject *>::iterator it;

	//int i = 0;


	for (auto it = m_objects.cbegin(); it != m_objects.cend(); it++)
	{
		if (it->second->GetFactoryKey() == "player")
		{
			//std::cout << "PLAYER IS HERER" << std::endl;
			it++;
		}
		else if (m_objects.find(it->first) != m_objects.cend())
		{
			std::cout << "delete level test: go =" << it->second->GetFactoryKey() << std::endl;

			//delete it->second;
			m_objects.erase(it++);
		}
		else
		{
			std::cout << "Player or End =" << std::endl;

			it++;
		}

		std::cout << "LIST SIZE == " << m_objects.size() << std::endl;

	}
}