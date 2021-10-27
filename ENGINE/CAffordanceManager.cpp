#include "CAffordanceManager.h"
#include "GameObject.h"

CAffordanceManager::CAffordanceManager(Transform *parent, GameObject *parentObj) : CComponent{ parent, parentObj }
{


}


void CAffordanceManager::AddAffordance(std::string name,std::string animation, std::string sound)
{
	listOfAffordances.insert(std::pair<std::string, Affordance>(name, Affordance(name,GetParentObject(), animation, sound)));
}

void CAffordanceManager::AddEmotion(std::string affordanceName, std::string name, float level)
{
	listOfAffordances.at(affordanceName).EmotionEffectors.insert(std::pair<std::string, float>(name, level));
}


