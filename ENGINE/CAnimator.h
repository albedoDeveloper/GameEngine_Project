#pragma once
#include "Animation.h"
#include "ModernOpenGL/AModel.h"
#include <map>
#include "CComponent.h"
#include "Time.h"


class CAnimator : public CComponent
{
	public:
		
		CAnimator(Transform* parent, GameObject* parentObj);
		~CAnimator(){
			delete  m_CurrentAnimation;
			m_CurrentAnimation = nullptr;
		}
		void AddAnimation( std::string filePath, bool playAtStart, std::string modelKey);
		void UpdateBone();
		void CalculateBoneTransform(const Animation::AssimpNodeData* node, Matrix4f parentTransform);
		void PlayAnimation(std::string animationName);

	private:
		std::map<std::string, Animation*> allAnimations;
		std::vector<Matrix4f> m_FinalBoneMatrices;
		std::vector<Bone*> listOfBones;
		Animation* m_CurrentAnimation = nullptr;
		float m_CurrentTime;
		float m_DeltaTime;

		bool firstTime = true;
		int iterator = 0;
};

