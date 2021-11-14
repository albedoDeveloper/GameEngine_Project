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

	//Gets every possible affordance in the map
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
		//GRAPHICS->DrawLine(vec1, vec2, Vector3f(1.0f, 0.5f, 0.5f));

		if (!path.empty())
		{
			NavNode *prevNode = path[0];

			;

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
	// State machine that determines what the AI should do
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

	// Checks every emotion and adds their multiplier over time (for example if an AI gets angry over time)
	for (auto emotion : emotions)
	{
		if (emotion.second.emotion < 1 && emotion.second.emotion > 0)
			emotion.second.emotion += emotion.second.emotionNativeChange * TIME->GetDeltaTime();
	}

}

void CAgent::AiThink()
{
	// At the start of the simulation (or at the end of task) the AI will find a new affordance
	FindNewAffordance();

	// Checks to see if an afforance has been found, then change the state to AI move
	if (currentAffordance != nullptr)
	{
		currentState = AiState::MOVE;
		
		// Plays the walking animation of the AI (if no animation exists they will just tpose instead)
		GetParentObject()->GetCAnimator()->PlayAnimation("agent_walk");
		
		auto pTrans = GetParentObject()->GetTransform()->GetRelativePosition();
		auto afforanceTrans = currentAffordance->parentObj->GetCAffordanceManager()->GetTransform().GetWorldTransform().GetRelativePosition();
		startLocation = pTrans;

		//Random calculates the amount of time an AI
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
	/*FindNavLocation();*/

	Vector3f startPos{ 0,0,0 };
	Vector3f endPos{ 5,1,5 };

	if (navNode != NULL)
		startPos = navNode->GetTransform()->GetWorldTransform().GetRelativePosition();

	auto pTrans = GetParentObject()->GetTransform()->GetRelativePosition();
	//GetParentObject()->GetTransform()->SetRelativePosition(startPos.GetX(),startPos.GetY(),startPos.GetZ());
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

	// Start when the AI reaches the affordances
	if (dst.Magnitude() < 2)
	{
		// Checks to see if the AI is in use by another AI, if it is they will try to find another AI
		if (currentAffordance->parentObj->GetCAffordanceManager()->isInUse)
		{
			currentState = AiState::THINK;
			currentInUseAffordance = currentAffordance->parentObj->GetFactoryKey();

		}
			
		//Start performing the affordance
		else
		{
			currentState = AiState::ACTION;
			lerpTime = 0;
			
			// Set the affordance to being in use by the AI
			currentAffordance->parentObj->GetCAffordanceManager()->isInUse = true;

			// plays the animation for that affordance
			if (!currentAffordance->animation._Equal(""))
				GetParentObject()->GetCAnimator()->PlayAnimation(currentAffordance->animation);

			// plays the sound for that affordance
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

		//std::cout << "Path Start " << std::endl;

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

				// Checks what direction the next node is, then causes the AI agent to face that direaction
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


		}
	}

}


void CAgent::AiAction()
{
	time += TIME->GetDeltaTime();

	// Waits until the designated time is up before finishing the affordance
	if (time > waitTime)
	{
		time = 0;
		std::cout << "-------------------------------------------" << std::endl;
		std::cout << "Agent Name: " << this->GetParentObject()->GetFactoryKey() << std::endl;

		//Applies the affordances effects on each emotion
		for (auto &emotionEffect : currentAffordance->EmotionEffectors)
		{
			// adds the emotion effect of the affordance to the coresponding emotion of the AI, which is multiplied by the AI's trait and finally a random amount
			// The random amount simulates real life, where every time you participate in an activity, what emotion you get out of it is slightly ranfom
			emotions.at(emotionEffect.first).emotion += emotionEffect.second * emotions.at(lowestName).multipler * (static_cast<float>(std::rand() % 140 + 70) / 100);

			// Prevents emotion overall (an agent can go beyond very high arousal for example)
			if (emotions.at(emotionEffect.first).emotion > 1)
				emotions.at(emotionEffect.first).emotion = 1;

			else if (emotions.at(emotionEffect.first).emotion < 0)
				emotions.at(emotionEffect.first).emotion = 0;

			std::cout << "Emotion: " << emotionEffect.first << " = " << emotions.at(emotionEffect.first).emotion << std::endl;
		}

		//Changes agent to think about a new affordance
		currentState = AiState::THINK;
		
		//Makes it so the affordance object is no longer in use
		currentAffordance->parentObj->GetCAffordanceManager()->isInUse = false;
		currentInUseAffordance = "";
	}
}

void CAgent::FindNewAffordance()
{
	// First find which emotion out of all of them is the lowest for the agent
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

	// Then go through all the affordances possible, determining which affordance will best increase the agents emotion the most
	for (auto &affordancelist : allAffordances)
	{
		for (auto &affordance : *affordancelist.second)
		{
			if (affordance.second.EmotionEffectors.count(lowestName) != 0)
			{
				// Set the trait modifier to 1 (meaning no effect
				auto trait = 1.0;

				//If the user has a trait for that particular affordance, then apply it
				if (traits.count(affordance.first) != 0)
					trait = traits.at(affordance.first);

				// Calculate the total float value you gain from that affordance, based upon its original amount the affordance gives, the users trait, as well as slight random modifier
				float affordanceAmount = affordance.second.EmotionEffectors.find(lowestName)->second * trait * (static_cast<float>(std::rand() % 150 + 50) / 100);

				// if this affordance gives the most emotion float value amount AND is not taken by another agent, then set that as the affordance target
				if (affordanceAmount >= highestImprovement && affordance.second.parentObj->GetFactoryKey() != currentInUseAffordance)
				{
					currentAffordance = &affordance.second;

					highestImprovement = affordanceAmount;
				}

			}
		}
	}

}
//Set the corresponding affordance value to a string
//THIS IS NOT NEEDED FOR THE AI ENGINE, IT IS PURELY HERE TO GIVE  A VISUAL REPRSENTATION OF THE AI ENGINE AND EMOTIONAL MODEL IN ACTION
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
		//Play the voice line corresponding to that emotion
		GetParentObject()->GetCSound()->PlaySound(currentCircumplex + ".wav", 0, true);
	}
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

		destinationNode = navMesh->FindNearest(position);
		destinationNode->SetActive(false);
	}

	return destinationNode;
}


