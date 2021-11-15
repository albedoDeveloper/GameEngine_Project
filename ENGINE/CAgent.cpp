#include "CAgent.h"
#include "GameObjectFactory.h"
#include <iostream>
#include <time.h>  
#include <math.h>
#include "MiscMath.h"
#include "InputManager.h"

CAgent::CAgent(Transform *parent, GameObject *parentObj) :CComponent{ parent, parentObj }
{
	auto allGameObjects = GAMEOBJECT->GetObjectMap();

	std::map<std::string, GameObject *>::iterator it;

	for (it = allGameObjects->begin(); it != allGameObjects->end(); it++)
	{
		if (it->second->GetCAffordanceManager() != nullptr)
			allAffordances.insert(std::pair(it->first, &it->second->GetCAffordanceManager()->listOfAffordances));

		if (it->second->GetCNavMesh() != nullptr)
			navMesh = it->second->GetCNavMesh();
	}
}

void CAgent::Render()
{
	Vector3f vec1 = Vector3f(1, 2, 3);
	Vector3f vec2 = Vector3f(3, 2, 1);

	if (GRAPHICS->m_drawDebug)
	{
		if (!path.empty())
		{
			NavNode *prevNode = path[0];

			for (auto &curNode : path)
			{

				GRAPHICS->DrawLine(prevNode->GetTransform()->GetRelativePosition(), curNode->GetTransform()->GetRelativePosition(), Vector3f(1.0f, 0.5f, 0.5f));

				prevNode = curNode;
			}
		}
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
		if (emotion.second.emotion < 1 && emotion.second.emotion > 0)
			emotion.second.emotion += emotion.second.emotionNativeChange * TIME->GetDeltaTime();
	}

}

void CAgent::Save(nlohmann::json &j)
{
	std::string stateString;

	switch (currentState)
	{
	case AiState::THINK:
		stateString = "THINK";
		break;

	case AiState::MOVE:
		stateString = "MOVE";
		break;

	case AiState::ACTION:
		stateString = "ACTION";
		break;
	}

	auto valence = emotions.at("valence").emotion;
	auto arousel = emotions.at("arousal").emotion;

	GameObject *g = GetParentObject();
	j[g->GetFactoryKey()]["Components"]["AgentComponent"]["AI State"] = stateString;
	j[g->GetFactoryKey()]["Components"]["AgentComponent"]["Valence"] = std::to_string(valence).c_str();
	j[g->GetFactoryKey()]["Components"]["AgentComponent"]["Arousal"] = std::to_string(arousel).c_str();

	j[g->GetFactoryKey()]["Components"]["AgentComponent"]["Activity"] = currentAffordance->name.c_str();
}

void CAgent::Load(nlohmann::json &j)
{
	GameObject *g = GetParentObject();

	std::string stateString = j.at(m_parent->GetFactoryKey()).at("Components").at("AgentComponent").at("AI State");

	if (stateString == "THINK")
	{
		currentState = AiState::THINK;
	}
	
	if (stateString == "MOVE")
	{
		currentState = AiState::MOVE;
	}

	if (stateString == "ACTION")
	{
		currentState = AiState::ACTION;
	}

	//set valence & arousal
	//float valence = j.at(m_parent->GetFactoryKey()).at("Components").at("AgentComponent").at("Valence");
	//emotions.at("valence").emotion = j.at(m_parent->GetFactoryKey()).at("Components").at("AgentComponent").at("Valence");
	//emotions.at("arousal").emotion = j.at(m_parent->GetFactoryKey()).at("Components").at("AgentComponent").at("Arousal");


	//set affordance
	for (auto &affordancelist : allAffordances)
	{
		for (auto &affordance : *affordancelist.second)
		{
			if (affordance.second.name.c_str() == j.at(m_parent->GetFactoryKey()).at("Components").at("AgentComponent").at("Activity"))
			{
				currentAffordance = &affordance.second;
			}
		}
	}


	//recalculate path 
	//grab nodes
	FindNavLocation();
	FindDestinationLocation(currentAffordance->parentObj->GetCAffordanceManager()->GetTransform().GetWorldTransform().GetRelativePosition());

	//clear navNodes
	came_from.clear();
	cost_so_far.clear();

	//clear old path
	path.clear();
	pathIndex = 0;

	if (navNode != nullptr || destinationNode != nullptr)
	{
		//run pathfindign algorithm
		path = navMesh->DijkstraSearch(navNode, destinationNode, came_from, cost_so_far);
	}

	FollowPath();

}

void CAgent::DrawToImGui()
{

	std::string stateString;

	switch (currentState)
	{
	case AiState::THINK:
		stateString = "THINK";
		break;

	case AiState::MOVE:
		stateString = "MOVE";
		break;

	case AiState::ACTION:
		stateString = "ACTION";
		break;
	}

	auto valence = emotions.at("valence").emotion;
	auto arousel = emotions.at("arousal").emotion;


	if (ImGui::TreeNode("Agent CComponent"))
	{
		ImGui::Text("Current State : "); ImGui::SameLine(); ImGui::Text(stateString.c_str());
		ImGui::Text("Current Valence : "); ImGui::SameLine(); ImGui::Text(std::to_string(valence).c_str());
		ImGui::Text("Current Arousal : "); ImGui::SameLine(); ImGui::Text(std::to_string(arousel).c_str());
		ImGui::Text( "Current Circumplex emotion: "); ImGui::SameLine(); ImGui::Text(currentCircumplex.c_str());
		ImGui::Text("Current Activity: "); ImGui::SameLine(); ImGui::Text(currentAffordance->name.c_str());
		ImGui::TreePop();

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
		auto afforanceTrans = currentAffordance->parentObj->GetCAffordanceManager()->GetTransform().GetWorldTransform().GetRelativePosition();
		startLocation = pTrans;

		auto lookat = LookAt(pTrans, afforanceTrans, GetParentObject()->GetTransform()->GetRelativeUp()).Inverse().ToQuat();

		GetParentObject()->GetTransform()->SetRelativeOrientation(lookat);

		waitTime = (std::rand() % 25 + 15);

		ConvertFloatToEmotion();

		//grab nodes
		FindNavLocation();
		FindDestinationLocation(afforanceTrans);

		//clear navNodes
		came_from.clear();
		cost_so_far.clear();

		//clear old path
		path.clear();
		pathIndex = 0;

		if (navNode != nullptr || destinationNode != nullptr)
		{
			//run pathfindign algorithm
			path = navMesh->DijkstraSearch(navNode, destinationNode, came_from, cost_so_far);
		}

	}
}

void CAgent::AiMove()
{
	Vector3f startPos{ 0,0,0 };
	Vector3f endPos{ 5,1,5 };

	if (navNode != NULL)
		startPos = navNode->GetTransform()->GetWorldTransform().GetRelativePosition();

	auto pTrans = GetParentObject()->GetTransform()->GetRelativePosition();
	auto afforanceTrans = currentAffordance->parentObj->GetCAffordanceManager()->GetTransform().GetWorldTransform().GetRelativePosition();

	FindDestinationLocation(afforanceTrans);

	if (destinationNode != NULL)
		endPos = destinationNode->GetTransform()->GetWorldTransform().GetRelativePosition();

	Vector3f dst = afforanceTrans - pTrans;

	if (path.empty())
	{
		m_parent->GetTransform()->TranslateV(Vector3f(std::lerp(pTrans.GetX(), endPos.GetX() - pTrans.GetX(), 1.0f), (std::lerp(pTrans.GetY(), endPos.GetY(), 1.0f)), std::lerp(pTrans.GetZ(), endPos.GetZ() - pTrans.GetZ(), 1.0f)) * TIME->GetDeltaTime() / 4);
	}
	else
	{
		FollowPath();
	}

	if (dst.Magnitude() < 2)
	{
		if (currentAffordance->parentObj->GetCAffordanceManager()->isInUse)
		{
			currentState = AiState::THINK;
			currentInUseAffordance = currentAffordance->parentObj->GetFactoryKey();

		}


		else
		{
			currentState = AiState::ACTION;
			lerpTime = 0;
			currentAffordance->parentObj->GetCAffordanceManager()->isInUse = true;

			if (!currentAffordance->animation._Equal(""))
				GetParentObject()->GetCAnimator()->PlayAnimation(currentAffordance->animation);

			if (!currentAffordance->sound._Equal(""))
				GetParentObject()->GetCSound()->PlaySound(currentAffordance->sound, 0, true);
		}
	}
}

void CAgent::FollowPath()
{

	if (!path.empty())
	{
		NavNode *prevNode = path[0];
		NavNode *nextNode = path[0];

		if (pathIndex < path.size() - 1)
		{
			nextNode = path[pathIndex];

			Vector3f pos = GetParentObject()->GetTransform()->GetRelativePosition();
			Vector3f endPos = nextNode->GetTransform()->GetWorldTransform().GetRelativePosition();

			Vector3f dst = endPos - GetParentObject()->GetTransform()->GetRelativePosition();

			if (dst.Magnitude() > 1)
			{
				m_parent->GetTransform()->TranslateV(Vector3f(std::lerp(pos.GetX(), endPos.GetX() - pos.GetX(), 1.0f), (std::lerp(pos.GetY(), endPos.GetY(), 1.0f)), std::lerp(pos.GetZ(), endPos.GetZ() - pos.GetZ(), 1.0f)) * TIME->GetDeltaTime());

			}

			if (dst.Magnitude() < 1)
			{
				auto zvalue = 0;
				auto xvalue = 0;

				prevNode = path[pathIndex];
				pathIndex++;

					
				auto endNode = (Vector3f(path[pathIndex]->GetTransform()->GetRelativePosition().GetX(), path[pathIndex]->GetTransform()->GetRelativePosition().GetY(), path[pathIndex]->GetTransform()->GetRelativePosition().GetZ()));

				GetParentObject()->GetTransform()->SetRelativeOrientation(Quaternion());

				if (prevNode->GetTransform()->GetRelativePosition().GetX() - endNode.GetX() > 0 && prevNode->GetTransform()->GetRelativePosition().GetZ() - endNode.GetZ() == 0)
					zvalue = 90;
				
				else if (prevNode->GetTransform()->GetRelativePosition().GetX() - endNode.GetX() < 0 && prevNode->GetTransform()->GetRelativePosition().GetZ() - endNode.GetZ() == 0)
					zvalue = 270;

				if (prevNode->GetTransform()->GetRelativePosition().GetX() - endNode.GetX() == 0 && prevNode->GetTransform()->GetRelativePosition().GetZ() - endNode.GetZ() < 0)
					zvalue = 0;

				else if (prevNode->GetTransform()->GetRelativePosition().GetX() - endNode.GetX() == 0 && prevNode->GetTransform()->GetRelativePosition().GetZ() - endNode.GetZ() > 0)
					zvalue = 180;


				auto endPos = Vector3f(xvalue, path[pathIndex]->GetTransform()->GetRelativePosition().GetY(), zvalue);

				GetParentObject()->GetTransform()->RotateLocalY(zvalue);
			}
		}
		else
		{
			Vector3f pos = GetParentObject()->GetTransform()->GetRelativePosition();
			Vector3f endPos = destinationNode->GetTransform()->GetWorldTransform().GetRelativePosition();

			m_parent->GetTransform()->TranslateV(Vector3f(std::lerp(pos.GetX(), endPos.GetX() - pos.GetX(), 1.0f), (std::lerp(pos.GetY(), endPos.GetY(), 1.0f)), std::lerp(pos.GetZ(), endPos.GetZ() - pos.GetZ(), 1.0f)) * TIME->GetDeltaTime());

			auto lookat = LookAt(pos, endPos, GetParentObject()->GetTransform()->GetRelativeUp()).Inverse().ToQuat();

			if (lookat.GetEulerAnglesDegrees().GetY() >= 360)
				lookat.SetY(0);
		}
	}
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

			emotions.at(emotionEffect.first).emotion += emotionEffect.second * emotions.at(lowestName).multipler * (static_cast<float>(std::rand() % 140 + 70) / 100);

			if (emotions.at(emotionEffect.first).emotion > 1)
				emotions.at(emotionEffect.first).emotion = 1;

			else if (emotions.at(emotionEffect.first).emotion < 0)
				emotions.at(emotionEffect.first).emotion = 0;

			std::cout << "Emotion: " << emotionEffect.first << " = " << emotions.at(emotionEffect.first).emotion << std::endl;
		}

		currentState = AiState::THINK;
		currentAffordance->parentObj->GetCAffordanceManager()->isInUse = false;
		currentInUseAffordance = "";
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

				if (affordanceAmount >= highestImprovement && affordance.second.parentObj->GetFactoryKey() != currentInUseAffordance)
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
		//std::string currentCircumplex;

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

		else if (valence <= 0.5 && arousel <= 1.0)
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

		else if (valence > 0.5 && arousel <= 1.0)
			currentCircumplex = "excited";

		std::string name = this->GetParentObject()->GetFactoryKey();

		std::cout << "************************" << std::endl;
		std::cout << "Agent Name: " << name << std::endl;
		std::cout << "Current Circumplex emotion: " << currentCircumplex << std::endl;
		std::cout << "Current activity: " << currentAffordance->name << std::endl;

		std::cout << "************************" << std::endl;

		GetParentObject()->GetCSound()->PlaySound(currentCircumplex + ".wav", 0, true);
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


NavNode *CAgent::FindNavLocation()
{
	if (navMesh == NULL)
	{

		auto allGameObjects = GAMEOBJECT->GetObjectMap();

		std::map<std::string, GameObject *>::iterator it;

		for (it = allGameObjects->begin(); it != allGameObjects->end(); it++)
		{
			if (it->second->GetCNavMesh() != nullptr)
				navMesh = it->second->GetCNavMesh();
		}

		navNode = navMesh->FindNearest(m_transform.GetWorldTransform().GetRelativePosition());
	}
	else
	{
		navNode = navMesh->FindNearest(m_transform.GetWorldTransform().GetRelativePosition());
	}

	return navNode;
}

NavNode *CAgent::FindDestinationLocation(Vector3f position)
{
	if (navMesh == NULL)
	{

		auto allGameObjects = GAMEOBJECT->GetObjectMap();

		std::map<std::string, GameObject *>::iterator it;

		for (it = allGameObjects->begin(); it != allGameObjects->end(); it++)
		{
			if (it->second->GetCNavMesh() != nullptr)
				navMesh = it->second->GetCNavMesh();
		}
	}
	else
	{
		//std::cout << "Affordance pos = " << position.GetX() << ", " << position.GetY() << ", " << position.GetZ() << std::endl;

		destinationNode = navMesh->FindNearest(position);
		destinationNode->SetActive(false);

		//std::cout << "Affordance " << this->GetParentObject()->GetFactoryKey() << " dst at x =" << destinationNode->GetXPos() << " z = " << destinationNode->GetZPos() << std::endl;
	}

	//endLocation = destinationNode->GetTransform()->GetWorldTransform().GetRelativePosition();

	return destinationNode;
}


