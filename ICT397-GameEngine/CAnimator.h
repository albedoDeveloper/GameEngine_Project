#pragma once
#include "Animation.h"
#include "ModernOpenGL/AModel.h"
#include <map>
#include "CComponent.h"
#include "DeltaTime.h"


class CAnimator : public CComponent
{
	public:
		
		CAnimator(Transform* parent, GameObject* parentObj);
		~CAnimator(){
			delete  m_CurrentAnimation;
			m_CurrentAnimation = nullptr;
		}
		void AddAnimation( std::string filePath);
		void Update();
		void CalculateBoneTransform(const Animation::AssimpNodeData* node, Matrix4f parentTransform);
		void PlayAnimation(Animation* Animation);

		std::vector<Matrix4f> GetFinalBoneMatrices() { return m_FinalBoneMatrices; }

	private:
		std::map<std::string, Animation> allAnimations;
		std::vector<Matrix4f> m_FinalBoneMatrices;
		Animation* m_CurrentAnimation;
		float m_CurrentTime;
		float m_DeltaTime;
};

