#pragma once
#include "CComponent.h"

#include <iostream>
#include <unordered_map>
#include "CAffordanceManager.h"
#include "CNavMesh.h"


class CAgent : public CComponent
{
private:

	enum class AiState
	{
		THINK,
		MOVE,
		ACTION

	};

	struct Emotion
	{
		Emotion(float emotion, float multiplier, float emotionNativeChange)
		{
			this->emotion = emotion;
			this->multipler = multiplier;
			this->emotionNativeChange = emotionNativeChange;
		}

		//Emotion level for that emotion
		float emotion;

		//Multiplier to see how much a person actually gets out of an activity
		float multipler;


		//Does the AI change the emotion over time
		float emotionNativeChange;
	};

	void ConvertFloatToEmotion();
	void FindNewAffordance();

	void AiThink();
	void AiMove();
	void AiAction();

	void FollowPath();

	NavNode *FindNavLocation();
	NavNode *FindDestinationLocation(Vector3f position);

public:
	CAgent(Transform *parent, GameObject *parentObj);

	~CAgent()
	{
		delete currentAffordance;
		currentAffordance = nullptr;

	}

	/**
	 * @brief renders the navmesh
	*/
	virtual void Render();

	std::unordered_map<std::string, Emotion> emotions;
	std::unordered_map<std::string, float> traits;

	CNavMesh *navMesh;
	NavNode *navNode;
	NavNode *destinationNode;

	std::vector<NavNode * > path;

	int pathIndex = 0;
	std::unordered_map<NavNode *, NavNode *> came_from;
	std::unordered_map<NavNode *, double> cost_so_far;

	Vector3f startLocation;
	Vector3f endLocation;

	Affordance *currentAffordance = nullptr;
	std::string currentCircumplex = "none";

	std::unordered_map<std::string, std::map<std::string, Affordance> *> allAffordances;

	AiState currentState = AiState::THINK;

	std::string lowestName;
	std::string currentInUseAffordance = "";

	float time = 0;
	float lerpTime = 0;
	int waitTime = 0;


	void AddEmotion(std::string name, float level, float multiplier, float emotionNativeChange);

	//-1.0f will make the ai hate it
	void AddTrait(std::string name, float value);

	virtual void Update();

	/**
		* @brief save the component
		* \param j json to save to
		*/
	virtual void Save(nlohmann::json &j);

	/**
	* @brief loads the component from saved state
	* \param j json to save to
	*/
	virtual void Load(nlohmann::json &j);

	/**
		 * @brief Draws to imgui
		*/
	virtual void DrawToImGui();

};

