#include "LightFactory.h"
#include <iostream>
#include <iterator>
#include "GameObject.h"

LightFactory::LightFactory() {
	spotlightList = *new std::map<std::string, CSpotlight*>();
}

LightFactory* LightFactory::instance() {
	static LightFactory* factory = new LightFactory();
	return factory;
}

CSpotlight* LightFactory::GetSpotlight(std::string key) {
#if _DEBUG
	if (spotlightList.find(key) == spotlightList.end()) {
		std::cout << "Light (Key:" << key << ") not found\n";
	}
#endif

	if (spotlightList.find(key) != spotlightList.end())
	{
		return spotlightList.at(key);
	}

	return nullptr;
}

CSpotlight* LightFactory::GetClosestSpotlight(const Transform* position)
{
	CSpotlight* closest = spotlightList.begin()->second;
	if (closest == nullptr)
	{
		std::cout << "Error: no spotlights in scene";
		return new CSpotlight(new Transform(), new GameObject());
	}
	for (std::map<std::string, CSpotlight*>::iterator i = spotlightList.begin(); i != spotlightList.end(); i++)
	{
		if (position->GetDistance(i->second->GetTransform()) > position->GetDistance(closest->GetTransform()))
		{
			closest = i->second;
		}
	}

	return closest;
}

CSpotlight* LightFactory::AddSpotlight(CSpotlight* light) {
	static std::string key = "AAAA";
	while (spotlightList.find(key) != spotlightList.end()) {
		iterateKey(key);
	}
	AddSpotlight(light, key);

	return light;
}

void LightFactory::iterateKey(std::string& key) {
	for (int place = 3; place >= 0; place--) {
		if (key[place] < 'Z') {
			key[place]++;
			return;
		}
		key[place] = 'A';
	}
	std::cout << "ran out of space in light factory";
}

CSpotlight* LightFactory::AddSpotlight(CSpotlight* light, std::string key) {
	if (spotlightList.begin() == spotlightList.end())
	{
		GRAPHICS->initLighting();
	}

	if (spotlightList.find(key) != spotlightList.end()) {
		return nullptr;
	}
	spotlightList.emplace(key, light);

#if _DEBUG
	std::cout << "Light Created. Key = " << key << "\n";
#endif

	return light;
}