#pragma once
#include "CComponent.h"

#include <iostream>
#include <unordered_map>
#include "CAffordanceManager.h"


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


		struct Traits
		{
			

			//Special trait list 
			//multiplier for events
			//Change in multipler
			//Gradual change in emotion
		};

		void FindNewAffordance();

		void AiThink();
		void AiMove();
		void AiAction();

	public:
		CAgent(Transform *parent, GameObject *parentObj);
		
		~CAgent(){
			delete currentAffordance;
			currentAffordance = nullptr;

		}

		std::unordered_map<std::string, Emotion> emotions;
		std::unordered_map<std::string, float> traits;

		Vector3f startLocation;
		Vector3f endLocation;
		
		Affordance* currentAffordance = nullptr;

		std::unordered_map<std::string, std::map<std::string,Affordance>*> allAffordances;
		
		AiState currentState = AiState::THINK;

		std::string lowestName;

		float time = 0;
		float lerpTime = 0;
		int waitTime = 0;
		void AddEmotion(std::string name, float level, float multiplier, float emotionNativeChange);
		
		//-1.0f will make the ai hate it
		void AddTrait(std::string name, float value);

		virtual void Update();
};

