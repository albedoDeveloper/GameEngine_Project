#pragma once
#include "Transform.h"
#include "Matrix4f.h"
#include "Bone.h"
#include <string>
#include <vector>
#include "ModernOpenGL/AModel.h"

class Animation
{
	public:
		struct AssimpNodeData
		{
			Matrix4f transformation;
			std::string name;
			int childrenCount;
			std::vector<AssimpNodeData> children;
		};

		Animation(const std::string& animationPath, AModel* model);
		Bone* FindBone(const std::string& name);

	private:

		void ReadMissingBones(const aiAnimation* animation, AModel& model);
		void ReadHeirarchyData(AssimpNodeData& dest, const aiNode* src);
		
		float m_Duration;
		int m_TicksPerSecond;
		std::vector<Bone> m_Bones;
		AssimpNodeData m_RootNode;
		std::map<std::string, AModel::BoneInfo> m_BoneInfoMap;
};

