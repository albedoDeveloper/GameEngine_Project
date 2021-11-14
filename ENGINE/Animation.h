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
		/// @brief Contains all the animation that has been extracted from a file via assimp
		struct AssimpNodeData
		{
			Matrix4f transformation;
			std::string name;
			int childrenCount;
			std::vector<AssimpNodeData> children;
		};

		/// @brief Create a new animation based upon an already preloaded model
		/// @param animationPath 
		/// @param model 
		Animation(const std::string& animationPath, AModel* model);
		
		/// @brief Find a bone using the id from the aninmation data that needs to move at a particular time
		/// @param name 
		/// @return 
		Bone* FindBone(const std::string& name);
		
		/// @brief Return how many times the animaton changes each second
		/// @return 
		float GetTicksPerSecond() { return m_TicksPerSecond; }
		
		/// @brief Get the total time the 
		/// @return 
		float GetDuration() { return m_Duration; }
		
		/// @brief Get the root animation data (ie the information of the first frame of animation)
		/// @return 
		AssimpNodeData& GetRootNode() { return m_RootNode; }
		
		/// @brief Contains all the different bones that are used in the animation
		/// @return 
		const std::map<std::string, AModel::BoneInfo>& GetBoneIDMap(){ return m_BoneInfoMap; }


	private:
		/// @brief Goes through all the animation data, and links movement from the animation with a bone that is attached to the model
		/// @param animation 
		/// @param model 
		void ReadMissingBones(const aiAnimation* animation, AModel& model);
		
		/// @brief Goes through each piece of animation data for each child of the model (for example from arm -> hand)
		/// @param dest 
		/// @param src 
		void ReadHeirarchyData(AssimpNodeData& dest, const aiNode* src);
		
		/// @brief How the long the animation goes for in seconds
		float m_Duration;
		/// @brief  How many times the animation changes per second (generally is at 30fps)
		int m_TicksPerSecond;
		
		/// @brief Vector of all the bones that are in the animation
		std::vector<Bone> m_Bones;
		/// @brief The starting animation node (ie the information about the first frame of the animation)
		AssimpNodeData m_RootNode;
		
		/// @brief Map of all the different bones that are used at what time
		std::map<std::string, AModel::BoneInfo> m_BoneInfoMap;
};

