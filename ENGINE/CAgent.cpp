#include "CAgent.h"
#include "GameObjectFactory.h"
#include <iostream>
#include <time.h>  
#include <math.h>
#include "MiscMath.h"
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

void CAgent::AddEmotion(std::string name, float level, float multipler, float emotionNativeChange)
{
	emotions.insert(std::pair<std::string, Emotion>(name, Emotion(level, multipler, emotionNativeChange)));
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
	
	for (auto emotion : emotions)
	{
		if(emotion.second.emotion < 1 && emotion.second.emotion > 0)
			emotion.second.emotion += emotion.second.emotionNativeChange;
	}
	
}

void CAgent::AiThink()
{
	FindNewAffordance();
	
	if (currentAffordance != nullptr)
	{
		currentState = AiState::MOVE;
		GetParentObject()->GetCAnimator()->PlayAnimation("agent_walk");
		auto pTrans = GetParentObject()->GetTransform()->GetRelativePosition();
		auto afforanceTrans = currentAffordance->parentObj->GetCAffordanceManager()->GetTransform().GetRelativePosition();
		startLocation = pTrans;
		endLocation = afforanceTrans;

		GetParentObject()->GetTransform()->SetRelativeOrientation(LookAt(startLocation, endLocation, GetParentObject()->GetTransform()->GetRelativeUp()).ToQuat().GetInverse());
		waitTime = (std::rand() % 25 + 15);

		ConvertFloatToEmotion();
	}
}

void CAgent::AiMove()
{
	auto pTrans = GetParentObject()->GetTransform()->GetRelativePosition();
	auto afforanceTrans = currentAffordance->parentObj->GetCAffordanceManager()->GetTransform().GetRelativePosition();

		//float t = lerpTime / 400;
		GetParentObject()->GetTransform()->TranslateV(Vector3f(Lerp(startLocation.GetX(), endLocation.GetX(), 1.0f), pTrans.GetY(), Lerp(startLocation.GetZ(), endLocation.GetZ(), 1.0f)) * (TIME->GetDeltaTime()/4));
		//lerpTime += lerpTime * TIME->GetDeltaTime();


	//if ((std::fabs(pTrans.GetX()) <= std::fabs(afforanceTrans.GetX()) + 1 && std::fabs(pTrans.GetX()) >= std::fabs(afforanceTrans.GetX()) - 1) && (std::fabs(pTrans.GetZ()) <= std::fabs(afforanceTrans.GetZ()) + 1 && std::fabs(pTrans.GetZ()) >= std::fabs(afforanceTrans.GetZ()) - 1))
	//{
		currentState = AiState::ACTION;
		lerpTime = 0;

		if (!currentAffordance->animation._Equal(""))
			GetParentObject()->GetCAnimator()->PlayAnimation(currentAffordance->animation);

		if (!currentAffordance->sound._Equal(""))
			GetParentObject()->GetCSound()->PlaySound(currentAffordance->sound, 0, true);
	//}
}

void CAgent::AiAction()
{
	time += TIME->GetDeltaTime();

	if (time > waitTime)
	{
		time = 0;
		std::cout << "-------------------------------------------" << std::endl;
		std::cout << "Agent Name: " << this->GetParentObject()->GetFactoryKey() << std::endl;

		for (auto &emotionEffect : currentAffordance->EmotionEffectors)
		{
			
			emotions.at(emotionEffect.first).emotion += emotionEffect.second * emotions.at(lowestName).multipler * (static_cast<float>(std::rand() % 140 + 70)/100);
			
			if (emotions.at(emotionEffect.first).emotion > 1)
				emotions.at(emotionEffect.first).emotion = 1;
			
			else if (emotions.at(emotionEffect.first).emotion < 0)
				emotions.at(emotionEffect.first).emotion = 0;
			
			std::cout << "Emotion: " << emotionEffect.first << " = " << emotions.at(emotionEffect.first).emotion << std::endl;
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
		if (emotion.second.emotion <= lowest)
		{
			lowestName = emotion.first;
			lowest = emotion.second.emotion;
		}
	}

	auto highestImprovement = -100;

	for (auto &affordancelist : allAffordances)
	{
		for (auto &affordance : *affordancelist.second)
		{
			if (affordance.second.EmotionEffectors.count(lowestName) != 0)
			{
				auto trait = 1.0;

				if (traits.count(affordance.first) != 0)
					trait = traits.at(affordance.first);

				float affordanceAmount = affordance.second.EmotionEffectors.find(lowestName)->second * trait * (static_cast<float>(std::rand() % 150 + 50) / 100);
				
				if ( affordanceAmount >= highestImprovement)
				{
					currentAffordance = &affordance.second;
					highestImprovement = affordanceAmount;
				}

			}
		}
	}

}

void CAgent::ConvertFloatToEmotion()
{
	if (emotions.count("valence") > 0 && emotions.count("arousal") > 0)
	{
		auto valence = emotions.at("valence").emotion;
		auto arousel = emotions.at("arousal").emotion;
		std::string currentCircumplex;

		if (valence <= 0.5 && arousel == 0.0)
			currentCircumplex = "tired";

		else if (valence <= 0.5 && arousel < 0.2)
			currentCircumplex = "bored";

		else if (valence <= 0.5 && arousel < 0.4)
			currentCircumplex = "depressed";

		else if (valence <= 0.5 && arousel < 0.6)
			currentCircumplex = "frustrated";

		else if (valence <= 0.5 && arousel < 0.8)
			currentCircumplex = "angry";

		else if (valence <= 0.5 && arousel < 1.0)
			currentCircumplex = "tense";

		else if (valence > 0.5 && arousel == 0.0)
			currentCircumplex = "calm";

		else if (valence > 0.5 && arousel < 0.2)
			currentCircumplex = "relaxed";

		else if (valence > 0.5 && arousel < 0.4)
			currentCircumplex = "content";

		else if (valence > 0.5 && arousel < 0.6)
			currentCircumplex = "happy";

		else if (valence > 0.5 && arousel < 0.8)
			currentCircumplex = "delighted";

		else if (valence > 0.5 && arousel < 1.0)
			currentCircumplex = "excited";

		std::string name = this->GetParentObject()->GetFactoryKey();

		std::cout << "************************" << std::endl;
		std::cout << "Agent Name: " << name << std::endl;
		std::cout << "Current Circumplex emotion: " << currentCircumplex << std::endl;
		std::cout << "Current activity: " << currentAffordance->name << std::endl;

		std::cout << "************************" << std::endl;
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


