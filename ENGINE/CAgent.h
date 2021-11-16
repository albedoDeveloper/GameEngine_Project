#pragma once
#include "CComponent.h"

#include <iostream>
#include <unordered_map>
#include "CAffordanceManager.h"
#include "CNavMesh.h"


class CAgent : public CComponent
{	
	private:
		/// @brief Enum containing all the different states the AI can be in
		enum class AiState
		{
			THINK,
			MOVE,
			ACTION
			
		};
		
		/// @brief Contains all the information about an emotion that an AI agent can have
		struct Emotion
		{
			/// @brief Constructor for an emotion, setting the emotion itself, the persons multipler to that emotion when do the activity, and the emotion change overtime
			/// @param emotion 
			/// @param multiplier 
			/// @param emotionNativeChange 
			Emotion(float emotion, float multiplier, float emotionNativeChange)
			{
				this->emotion = emotion;
				this->multipler = multiplier;
				this->emotionNativeChange = emotionNativeChange;
			}
			
			/// @brief Emotion level for that emotion
			float emotion;
			
			/// @brief Multiplier to see how much a person actually gets out of an activity
			float multipler;


			/// @brief Does the AI change the emotion over time
			float emotionNativeChange;
		};

		/// @brief Converts an emotion from system 
		/// THIS FUNCTION IS PURELY TO DEMONSTRATE THE AI IN HUMAN TERMS, THE SYSTEM DOESNT NEED TO USE IT
		void ConvertFloatToEmotion();
		
		/// @brief Searches for a new affordance for the AI agent, based on its parameters
		void FindNewAffordance();

		/// @brief The state of the AI when its finding a new affordance
		void AiThink();
		
		/// @brief The state of the AI when its moving to its determined affordance
		void AiMove();

		/// @brief The state of the AI when its performing an affordance
		void AiAction();

		//Does the AI change the emotion over time
		float emotionNativeChange;

		/// @brief the current affordance the AI wishes to perform
		Affordance *currentAffordance = nullptr;

		/// @brief A list of all possible affordances in the world (these affordances can be anything, and its unlimited in the amount the AI can access
		std::unordered_map<std::string, std::map<std::string, Affordance> *> allAffordances;

		/// @brief The state machine of the AI, and its starting state
		AiState currentState = AiState::THINK;

		/// @brief The name of the emotion that the AI wants to improve the most
		std::string lowestName;
		
		/// @brief The name of the affordance the AI is currently
		std::string currentInUseAffordance = "";

		/// @brief Map containing all of the AI's emotions
		std::unordered_map<std::string, Emotion> emotions;
		
		/// @brief Map containing all of the AI's traits
		std::unordered_map<std::string, float> traits;

		float time = 0;
		float lerpTime = 0;
		int waitTime = 0;

	public:
		CAgent(Transform *parent, GameObject *parentObj);
		
		~CAgent(){
			delete currentAffordance;
			currentAffordance = nullptr;
		}
		void FollowPath();

		NavNode *FindNavLocation();
		NavNode *FindDestinationLocation(Vector3f position);

		/**
		* @brief renders the navmesh
		*/
		virtual void Render();

		CNavMesh *navMesh;
		NavNode *navNode;
		NavNode *destinationNode;

		std::string currentCircumplex;

		std::vector<NavNode * > path;

		int pathIndex = 0;
		std::unordered_map<NavNode *, NavNode *> came_from;
		std::unordered_map<NavNode *, double> cost_so_far;

		Vector3f startLocation;
		Vector3f endLocation;

		/// @brief Add a new emotion to the AI agent
		/// @param name 
		/// @param level 
		/// @param multiplier 
		/// @param emotionNativeChange 
		void AddEmotion(std::string name, float level, float multiplier, float emotionNativeChange);
		
	
		/// @brief Add a trait to the AI agent (A trait in this case is how much they like or dislike certain affordances, 	-1.0f will for example make the AI hate it,
		/// While 0.3 will make the AI like it less
		/// @param name 
		/// @param value 
		void AddTrait(std::string name, float value);

		/// @brief Update the AI every frame
		virtual void Update();

		/**
		 * @brief saves the component
		*/
		virtual void Save(nlohmann::json &j);

			/**
			 * @brief loads the component from saved state
			*/
		virtual void Load(nlohmann::json &j);

			/**
			 * @brief Draws to imgui
			*/
		virtual void DrawToImGui();
};

