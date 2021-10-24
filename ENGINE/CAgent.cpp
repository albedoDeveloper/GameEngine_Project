#include "CAgent.h"
#include "GameObjectFactory.h"
#include <iostream>
CAgent::CAgent(Transform *parent, GameObject *parentObj):CComponent{ parent, parentObj }
{
	auto allGameObjects = GAMEOBJECT->GetObjectMap();
	
	std::map<std::string, GameObject *>::iterator it;
	
	for (it = allGameObjects->begin(); it != allGameObjects->end(); it++)
	{
		if (it->second->GetCAffordanceManager() != nullptr)
			allAffordances.insert(std::pair(it->first, &it->second->GetCAffordanceManager()->listOfAffordances));
	}

}

void CAgent::AddEmotion(std::string name, float level, float multipler)
{
	emotions.insert(std::pair<std::string, Emotion>(name, Emotion(level, multipler)));
}

void CAgent::AddTrait(std::string name, float value)
{
	traits.insert(std::pair<std::string, float>(name, value));
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
			emotions.at(emotionEffect.first).emotion += emotionEffect.second * emotions.at(lowestName).multipler;
		}
		currentState = AiState::THINK;
	}
}

void CAgent::FindNewAffordance()
{
	auto lowest = emotions.begin()->second.emotion;
	lowestName = emotions.begin()->first;
	
	for (auto &emotion : emotions)
	{
		if (emotion.second.emotion < lowest)
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
				auto trait = 1.0f;

				if (traits.count(affordance.first) != 0)
					trait = traits.at(affordance.first);

				if (affordance.second.EmotionEffectors.find(lowestName)->second * trait >= highestImprovement)
				{
					currentAffordance = &affordance.second;
					inAffordance = true;
				}

			}
		}
	}

}

void ChangeEmotionNatively(float &emotion, float modifier)
{
	if (emotion > 0.0 && emotion < 1.0)
	{
		emotion += modifier;
	}

	else if (emotion > 1.0)
		emotion = 1.0;

	else
		emotion = 0.0;

}

void ChangeMultiplier(float multipler, float modification)
{


}


