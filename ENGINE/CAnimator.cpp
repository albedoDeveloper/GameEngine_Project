#include "CAnimator.h"
#include "GameObject.h"
#include "GraphicsEngine.h"
CAnimator::CAnimator(Transform* parent, GameObject* parentObj)
	:CComponent{ parent, parentObj }
{
	m_CurrentTime = 0.0;
	m_DeltaTime = 0;

	m_FinalBoneMatrices.reserve(100);

	for (int i = 0; i < 100; i++)
		m_FinalBoneMatrices.push_back(Matrix4f());

}

void CAnimator::AddAnimation(std::string filePath, bool playAtStart, std::string modelKey)
{
	GameObject* g = GetParentObject();
	AModel* model = &g->GetCStaticMesh()->GetModel();

	allAnimations.emplace(std::pair<std::string, Animation*>(modelKey, new Animation("../Assets/Models/" + filePath, model)));
	
	if (playAtStart)
	{
		m_CurrentAnimation = allAnimations[modelKey];
	}
}

void CAnimator::UpdateBone()
{
	m_DeltaTime = TIME->GetDeltaTime();
	if (m_CurrentAnimation)
	{
		m_CurrentTime += m_CurrentAnimation->GetTicksPerSecond() * m_DeltaTime * 24;
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

void  CAnimator::CalculateBoneTransform(const Animation::AssimpNodeData* node, Matrix4f parentTransform)
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

	Matrix4f globalTransformation = parentTransform * nodeTransform;
	auto boneInfoMap = m_CurrentAnimation->GetBoneIDMap();
	
	if (boneInfoMap.find(nodeName) != boneInfoMap.end() )
	{
		try
		{
			m_FinalBoneMatrices.at(boneInfoMap[nodeName].id) = globalTransformation * boneInfoMap[nodeName].offset;
		}
		catch(...)
		{

		}
	}

	for (int i = 0; i < node->childrenCount; i++)
		CalculateBoneTransform(&node->children[i], globalTransformation);
}


void CAnimator::PlayAnimation(std::string filePath)
{
	m_CurrentAnimation = allAnimations[filePath];
	m_CurrentTime = 0.0f;
	firstTime = true;
	listOfBones.clear();
}