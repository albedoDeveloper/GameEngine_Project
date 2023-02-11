#include "Animation.h"

Animation::Animation(const std::string& animationPath, AModel* model)
{
	Assimp::Importer importer;
	importer.SetPropertyBool(AI_CONFIG_IMPORT_FBX_PRESERVE_PIVOTS, false);

	const aiScene* scene = importer.ReadFile(animationPath, aiProcess_FlipUVs | aiProcess_Triangulate | aiProcess_OptimizeGraph | aiProcess_OptimizeMeshes | aiProcess_CalcTangentSpace | aiProcess_GenNormals | aiProcess_LimitBoneWeights);
	
	assert(("The animation data was not imported correctly", scene && scene->mRootNode));
	
	auto animation = scene->mAnimations[0];
	m_Duration = animation->mDuration;
	m_TicksPerSecond = animation->mTicksPerSecond;

	ReadHeirarchyData(m_RootNode, scene->mRootNode);
	ReadMissingBones(animation, *model);

}

Bone* Animation::FindBone(const std::string& name)
{
	//FIX
	auto iter = std::find_if(m_Bones.begin(), m_Bones.end(),[&](Bone& Bone)
	{
		return Bone.GetBoneName() == name;
	}
	);
	
	if (iter == m_Bones.end())
		return nullptr;
	else 
		return &(*iter);
}

void Animation::ReadMissingBones(const aiAnimation* animation, AModel& model)
{
	int size = animation->mNumChannels;

	auto& boneInfoMap = model.GetBoneInfoMap();
	int& boneCount = model.GetBoneCount();

	for (int i = 0; i < size; i++)
	{
		auto channel = animation->mChannels[i];
		std::string boneName = channel->mNodeName.data;

		if (boneInfoMap.find(boneName) == boneInfoMap.end())
		{
			boneInfoMap[boneName].id = boneCount;
			boneCount++;
		}
		m_Bones.push_back(Bone(channel->mNodeName.data,boneInfoMap[channel->mNodeName.data].id, channel));
	}

	m_BoneInfoMap = boneInfoMap;
}


void Animation::ReadHeirarchyData(NodeData& dest, const aiNode* src)
{
	if (src != nullptr)
	{
		dest.name = src->mName.data;
		dest.transformation = dest.transformation.ConvertAiMatrixToMatrix4f(src->mTransformation);
		dest.childrenCount = src->mNumChildren;

		for (int i = 0; i < src->mNumChildren; i++)
		{
			NodeData newData;
			ReadHeirarchyData(newData, src->mChildren[i]);
			dest.children.push_back(newData);
		}
	}
}

