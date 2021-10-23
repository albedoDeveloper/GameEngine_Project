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
		
		
		struct Traits
		{

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

		std::unordered_map<std::string, float> emotions;
		
		bool inAffordance = false;
		
		Affordance* currentAffordance = nullptr;

		std::unordered_map<std::string, std::map<std::string,Affordance>*> allAffordances;
		
		AiState currentState = AiState::THINK;

		std::string lowestName;

		float time = 0;

		void AddEmotion(std::string name, float level);


		virtual void Update();
};

