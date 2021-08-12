#include "GameObjectFactory.h"
#include <iostream>

GameObjectFactory::GameObjectFactory() {
	objectList = *new std::map<std::string, GameObject*>();
}

GameObjectFactory* GameObjectFactory::instance() {
	static GameObjectFactory* factory = new GameObjectFactory();
	return factory;
}

GameObject* GameObjectFactory::getObject(std::string key) {
#if _DEBUG
	if (objectList.find(key) == objectList.end()) {
		std::cout << "GameObject (Key:" << key << ") not found\n";
	}
#endif

	if (objectList.find(key) != objectList.end())
	{
		return objectList.at(key);
	}

	return nullptr;
}

GameObject* GameObjectFactory::getClosestObject(Transform* target, std::string partialKey) 
{
	GameObject* closest = nullptr;

	for (std::map<std::string, GameObject*>::iterator i = objectList.begin(); i != objectList.end(); i++)
	{
		if (i->second->getFactoryKey().find(partialKey) != std::string::npos)
		{
			if (closest == nullptr)
			{
				closest = i->second;
			}
			else
			{
				if (target->GetDistance(i->second->GetTransform()) < target->GetDistance(closest->GetTransform()) && i->second->GetTransform() != target)
				{
					closest = closest = i->second;
				}
			}
		}
	}

	return closest;
}

int GameObjectFactory::getNumObjects()
{
	return objectList.size();
}

GameObject* GameObjectFactory::SpawnGameObject() {
	GameObject* object = new GameObject();

	static std::string key = "AAAA";
	while(objectList.find(key) != objectList.end()){
		iterateKey(key);
	}
	objectList.emplace(key, object);
	object->setFactoryKey(key);

	return object;
}

void GameObjectFactory::iterateKey(std::string &key) {
	for (int place = 3; place >= 0; place--) {
		if (key[place] < 'Z') {
			key[place]++;
			return;
		}
		key[place] = 'A';
	}
	std::cout << "ran out of space in object factory";
}

GameObject* GameObjectFactory::SpawnGameObject(std::string key) {
	GameObject* object = new GameObject();

	if (objectList.find(key) != objectList.end()) {
		return nullptr;
	}
	objectList.emplace(key, object);
	object->setFactoryKey(key);

#if _DEBUG
	std::cout << "Game Object Created. Key = " << key << "\n";
#endif

	return object;
}

void GameObjectFactory::Start()
{
	std::map<std::string, GameObject*>::iterator it;
	for (it = objectList.begin(); it != objectList.end(); it++) {
		it->second->Start();
	}
}

void GameObjectFactory::Update()
{
	std::map<std::string, GameObject*>::iterator it;
	for (it = objectList.begin(); it != objectList.end(); it++) {
		it->second->Update();
	}
}

void GameObjectFactory::render() {
	std::map<std::string, GameObject*>::iterator it;
	for (it = objectList.begin(); it != objectList.end(); it++) {
		it->second->Render();
	}
	for (it = objectList.begin(); it != objectList.end(); it++) {
		it->second->LateRender();
	}
}

void GameObjectFactory::Restart()
{
	std::map<std::string, GameObject*>::iterator it;
	for (it = objectList.begin(); it != objectList.end(); it++) {
		it->second->Restart();
	}
}

void GameObjectFactory::Save()
{
	std::map<std::string, GameObject*>::iterator it;
	for (it = objectList.begin(); it != objectList.end(); it++) {
		it->second->Save();
	}
}

void GameObjectFactory::Load()
{
	std::map<std::string, GameObject*>::iterator it;
	for (it = objectList.begin(); it != objectList.end(); it++) {
		it->second->Load();
	}
}

void GameObjectFactory::Close() {
	objectList = *new std::map<std::string, GameObject*>();
}