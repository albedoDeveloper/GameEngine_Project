#include "CAgent.h"
#include "GameObjectFactory.h"
#include <iostream>
CAgent::CAgent(Transform *parent, GameObject *parentObj)
	:CComponent{ parent, parentObj }
{
	auto allGameObjects = GAMEOBJECT->GetObjectMap();
	
	std::map<std::string, GameObject *>::iterator it;
	
	for (it = allGameObjects->begin(); it != allGameObjects->end(); it++)
	{
		if (it->second->GetCAffordanceManager() != nullptr)
			allAffordances.insert(std::pair(it->first, &it->second->GetCAffordanceManager()->listOfAffordances));
	}

}

void CAgent::AddEmotion(std::string name, float level)
{
	emotions.insert(std::pair<std::string, float>(name, level));
}

void CAgent::Update()
{

	switch (currentState)
	{
		case AiState::THINK:
			AiThink();
			break;

		case AiState::MOVE: 
			AiMove();
			break;

		case AiState::ACTION:
			AiAction();
			break;
	}
}

void CAgent::AiThink()
{
	FindNewAffordance();
	if(inAffordance)
		currentState = AiState::MOVE;
}

void CAgent::AiMove()
{
	auto pTrans = GetParentObject()->GetTransform()->GetWorldTransform();

	currentState = AiState::ACTION;

	if (!currentAffordance->animation._Equal(""))
		GetParentObject()->GetCAnimator()->PlayAnimation(currentAffordance->animation);
}

void CAgent::AiAction()
{
	time += TIME->GetDeltaTime();

	if (time > 5.0)
	{
		time = 0;
		
		for (auto &emotionEffect : currentAffordance->EmotionEffectors)
		{
			emotions[emotionEffect.first] += emotionEffect.second;
		}
		currentState = AiState::THINK;
	}
}

void CAgent::FindNewAffordance()
{
	auto lowest = emotions.begin()->second;
	lowestName = emotions.begin()->first;
	
	for (auto &emotion : emotions)
	{
		if (emotion.second < lowest)
		{
			lowestName = emotion.first;
		}
	}

	auto highestImprovement = 0.0f;


	for (auto &affordancelist : allAffordances)
	{
		for (auto &affordance : *affordancelist.second)
		{
			if (affordance.second.EmotionEffectors.count(lowestName) != 0)
			{
				if (affordance.second.EmotionEffectors.find(lowestName)->second >= highestImprovement)
				{
					currentAffordance = &affordance.second;
					inAffordance = true;
				}

			}
		}
	}



}