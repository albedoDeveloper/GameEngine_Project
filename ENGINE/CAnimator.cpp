#include "CAnimator.h"
#include "GameObject.h"
#include "GraphicsEngine.h"
#include "AnimationManager.h"

CAnimator::CAnimator(Transform* parent, GameObject* parentObj)
	:CComponent{ parent, parentObj }
{
	m_CurrentTime = 0.0;

	m_FinalBoneMatrices.reserve(100);

	for (int i = 0; i < 100; i++)
		m_FinalBoneMatrices.push_back(Matrix4f());
}


void CAnimator::UpdateBone()
{
	if (m_CurrentAnimation)
	{
		m_CurrentTime += m_CurrentAnimation->GetTicksPerSecond() * TIME->GetDeltaTime() * 24;
		m_CurrentTime = fmod(m_CurrentTime, m_CurrentAnimation->GetDuration());
		CalculateBoneTransform(&m_CurrentAnimation->GetRootNode(), Matrix4f());
		firstTime = false;
		iterator = 0;
	}

	for (int i = 0; i < m_FinalBoneMatrices.size(); i++)
	{
		GRAPHICS->m_litShader->SetMat4Uniform("finalBonesMatrices[" + std::to_string(i) + "]", m_FinalBoneMatrices[i]);
		GRAPHICS->m_unlitShader->SetMat4Uniform("finalBonesMatrices[" + std::to_string(i) + "]", m_FinalBoneMatrices[i]);
	}

}

void  CAnimator::CalculateBoneTransform(const Animation::NodeData* node, Matrix4f parentTransform)
{
	std::string nodeName = node->name;
	Matrix4f nodeTransform = node->transformation;	

	Bone* Bone;
	
	if (firstTime)
	{
		Bone = m_CurrentAnimation->FindBone(nodeName);
		listOfBones.push_back(Bone);
	}

	else
	{
		Bone = listOfBones[iterator];
		iterator++;
	}

	if (Bone)
	{
		Bone->UpdateBone(m_CurrentTime);
		nodeTransform = Bone->GetLocalTransform();
	}

	auto transform = parentTransform * nodeTransform;
	auto relevantBones = m_CurrentAnimation->GetBoneIDMap();
	
	if (relevantBones.find(nodeName) != relevantBones.end() )
	{
		try
		{
			m_FinalBoneMatrices.at(relevantBones[nodeName].id) = transform * relevantBones[nodeName].offset;
		}
		catch(...)
		{
			std::cout << "Could not find bones" << std::endl;
		}
	}

	for (int i = 0; i < node->childrenCount; i++)
		CalculateBoneTransform(&node->children[i], transform);
}


void CAnimator::PlayAnimation(std::string filePath)
{
	m_CurrentAnimation = ANIMATION->GetAnimation(filePath);
	
	m_CurrentTime = 0.0f;
	firstTime = true;
	listOfBones.clear();
}