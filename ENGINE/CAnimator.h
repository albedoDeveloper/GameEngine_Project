#pragma once
#include "Animation.h"
#include "ModernOpenGL/AModel.h"
#include <map>
#include "CComponent.h"
#include "MyTime.h"
#include "Animation.h"

class CAnimator : public CComponent
{
public:
	/// @brief Basic constructor that all components of a gameobject must have
	/// @param parent 
	/// @param parentObj 
	CAnimator(Transform *parent, GameObject *parentObj);
	
	/// @brief deconstructor for pointers
	~CAnimator()
	{
		delete  m_CurrentAnimation;
		m_CurrentAnimation = nullptr;
	}
	/// @brief Update every bone in the animation with its new movements, and then update how that bone is drawn in the shader
	void UpdateBone();
	
	/// @brief Calculate the transforms of the bones based upon the bone transformations applied in the animation class
	/// @param node 
	/// @param parentTransform 
	void CalculateBoneTransform(const Animation::NodeData *node, Matrix4f parentTransform);
	
	/// @brief Play a new animation
	/// @param animationName 
	void PlayAnimation(std::string animationName);

private:
	/// @brief Contains a vector of each bones movements from the animation class
	std::vector<Matrix4f> m_FinalBoneMatrices;
	/// @brief List of each bone that is used in the current animation
	std::vector<Bone *> listOfBones;
	/// @brief  The animation that is playing
	Animation *m_CurrentAnimation = nullptr;
	
	/// @brief the amount of time that the animation has played for
	float m_CurrentTime;

	/// @brief Whether or not this is the first time that the animation is playing
	bool firstTime = true;

	int iterator = 0;
};

