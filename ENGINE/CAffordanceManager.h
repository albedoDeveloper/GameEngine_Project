#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include "CComponent.h"


struct Affordance
{
	Affordance(std::string name, GameObject *parentObj, std::string animation, std::string sound)
	{
		this->name = name;
		this->parentObj = parentObj;
		this->animation = animation;
		this->sound = sound;
	}

	std::string name;

	std::unordered_map<std::string, float> EmotionEffectors;

	std::string animation;
	std::string sound;
	GameObject *parentObj;
};

class CAffordanceManager : public CComponent
{
	public:
		CAffordanceManager(Transform *parent, GameObject *parentObj);
		void AddAffordance(std::string name, std::string animation, std::string sound);
		void AddEmotion(std::string affordanceName, std::string name, float level);

		std::map<std::string, Affordance> listOfAffordances;
		bool isInUse;
};

