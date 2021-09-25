#include "CAnimator.h"

CAnimator::CAnimator(Animation* animation)
{
	m_CurrentTime = 0.0;
	m_CurrentAnimation = animation;

	//m_FinalBoneMatrices.reserve(100);

	for (int i = 0; i < 100; i++)
		m_FinalBoneMatrices.push_back(Matrix4f());


}

void CAnimator::AddAnimation(std::string name, std::string filePath)
{
	

}

void CAnimator::UpdateAnimation(float deltaTime)
{
	m_DeltaTime = deltaTime;
	if (m_CurrentAnimation)
	{
		m_CurrentTime += m_CurrentAnimation->GetTicksPerSecond() * deltaTime;
		m_CurrentTime = fmod(m_CurrentTime, m_CurrentAnimation->GetDuration());
		CalculateBoneTransform(&m_CurrentAnimation->GetRootNode(), Matrix4f());
	}
}

void  CAnimator::CalculateBoneTransform(const Animation::AssimpNodeData* node, Matrix4f parentTransform)
{
	std::string nodeName = node->name;
	Matrix4f nodeTransform = node->transformation;

	Bone* Bone = m_CurrentAnimation->FindBone(nodeName);

	if (Bone)
	{
		Bone->UpdateBone(m_CurrentTime);
		nodeTransform = Bone->GetLocalTransform();
	}

	Matrix4f globalTransformation = parentTransform * nodeTransform;

	auto boneInfoMap = m_CurrentAnimation->GetBoneIDMap();
	if (boneInfoMap.find(nodeName) != boneInfoMap.end())
	{
		int index = boneInfoMap[nodeName].id;
		Matrix4f offset = boneInfoMap[nodeName].offset;
		m_FinalBoneMatrices[index] = globalTransformation * offset;
	}

	for (int i = 0; i < node->childrenCount; i++)
		CalculateBoneTransform(&node->children[i], globalTransformation);
}


void CAnimator::PlayAnimation(Animation* animation)
{
	m_CurrentAnimation = animation;
	m_CurrentTime = 0.0f;
}