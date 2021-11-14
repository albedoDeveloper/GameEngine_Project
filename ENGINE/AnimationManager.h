#pragma once
#include "Animation.h"

class AnimationManager
{
	public:
		AnimationManager();

		static AnimationManager *Instance();

		void AddAnimation(std::string filePath, std::string model, std::string name);
		Animation *GetAnimation(std::string name);
	private:
		std::unordered_map<std::string, Animation*> animationList;


};

#define ANIMATION AnimationManager::Instance()

