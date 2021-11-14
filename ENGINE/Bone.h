#pragma once
#include "Transform.h"
#include "Matrix4f.h"
#include <string>
#include <assimp/anim.h>
#include <glm/glm/glm.hpp>


/// @brief Contains the current translation of the bone at a particular time
struct KeyPosition
{
	Vector3f position;
	float timeStamp;
};

/// @brief Contains the current rotation of the bone at a particular time
struct KeyRotation
{
	Quaternion orientation;
	float timeStamp;
};

/// @brief Contains the current scale of the bone at a particular time
struct KeyScale
{
	Vector3f scale;
	float timeStamp;
};

class Bone
{
private:

	/// @brief contains all the different positions the bone can be at each time interval of the animation
	std::vector<KeyPosition> m_allPositions;
	
	/// @brief contains all the different rotations the bone can be at each time interval of the animation
	std::vector<KeyRotation> m_allRotations;
	
	/// @brief contains all the different scalings the bone can be at each time interval of the animation
	std::vector<KeyScale> m_allScaling;
	
	/// @brief Total number of positons the animation has
	int m_NumPositions;
	
	/// @brief Total number of rotations the animation has
	int m_NumRotations;

	/// @brief Total number of times the animations scales
	int m_NumScalings;


	/// @brief Contains the current position, rotation, scale at a particular time
	Matrix4f m_LocalTransform;
	
	/// @brief The name of the bone
	std::string m_Name;
	
	/// @brief The bone ID
	int m_ID;
	
	
	public:
		/// @brief Constructor for the bone that sets its parameters, including the assimp animation data containing all the positions.
		/// @param name 
		/// @param ID 
		/// @param channel 
		Bone(const std::string& name, int ID, const aiNodeAnim* channel);
		
		/// @brief Change the bones position, rotation and scaling based upon the current time of the animation
		/// @param animationTime 
		void UpdateBone(float animationTime);

		/// @brief Go through all the positions to find the one that is needed for the current time of the animation
		/// @param animationTime 
		/// @return 
		int GetPosIndex(float animationTime);

		/// @brief Go through all the rotations to find the one that is needed for the current time of the animation
		/// @param animationTime 
		/// @return 
		int GetRotIndex(float animationTime);

		/// @brief Go through all the rotations to find the one that is needed for the current time of the animation
		/// @param animationTime 
		/// @return 
		int GetScaleIndex(float animationTime);
		
		/// @brief Used to determine what the scale is for lerping, slerping etc..., which is determined by how close the animation is to the previous or next bone state
		/// @param lastTimeStamp 
		/// @param nextTimeStamp 
		/// @param animationTime 
		/// @return 
		float GetScaleFactor(float lastTimeStamp, float nextTimeStamp, float animationTime);

		/// @brief Lerp between the the previous position and new position of the bone, to create a fluid translation
		/// @param animationTime 
		/// @return 
		Matrix4f InterpolatePosition(float animationTime);


		/// @brief slerp between the the previous rotation and new rotation of the bone, to create fluid rotation of the bone
		/// @param animationTime 
		/// @return 
		Matrix4f InterpolateRotation(float animationTime);
		
		/// @brief mix between the the previous scaling and new scaling of the bone, to create fluid scale changes of the bone
		/// @param animationTime 
		/// @return 
		Matrix4f InterpolateScaling(float animationTime);
		
		/// @brief Returns the name of the bone
		/// @return 
		std::string GetBoneName() { return m_Name; }
		
		/// @brief Returns the transform of the bone
		/// @return 
		Matrix4f GetLocalTransform() { return m_LocalTransform; }

};

