#pragma once
#include "Animation.h"
#include "ModernOpenGL/AModel.h"
#include <map>

class CAnimator
{
	public:
		
		CAnimator(Animation* animation);
		void AddAnimation(std::string name, std::string filePath);
		void UpdateAnimation(float deltaTime);
		void CalculateBoneTransform(const Animation::AssimpNodeData* node, Matrix4f parentTransform);
		void PlayAnimation(Animation* Animation);

	private:
		std::map<std::string, Animation> allAnimations;
		std::vector<Matrix4f> m_FinalBoneMatrices;
		Animation* m_CurrentAnimation;
		float m_CurrentTime;
		float m_DeltaTime;
};

