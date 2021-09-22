#pragma once
#include "Transform.h"
#include "Matrix4f.h"
#include <string>
#include <assimp/anim.h>
#include <glm/glm/glm.hpp>
struct KeyPosition
{
	Vector3f position;
	float timeStamp;
};

struct KeyRotation
{
	Quaternion orientation;
	float timeStamp;
};

struct KeyScale
{
	Vector3f scale;
	float timeStamp;
};

class Bone
{
private:

	std::vector<KeyPosition> m_Positions;
	std::vector<KeyRotation> m_Rotations;
	std::vector<KeyScale> m_Scales;
	
	int m_NumPositions;
	int m_NumRotations;
	int m_NumScalings;

	glm::mat4 m_LocalTransform;
	std::string m_Name;
	int m_ID;
	
	
	public:
		Bone(const std::string& name, int ID, const aiNodeAnim* channel);
		void UpdateBone(float animationTime);

		int GetPositionIndex(float animationTime);
		int GetRotationIndex(float animationTime);
		int GetScaleIndex(float animationTime);
		float GetScaleFactor(float lastTimeStamp, float nextTimeStamp, float animationTime);

		Matrix4f InterpolatePosition(float animationTime);
		Matrix4f InterpolateRotation(float animationTime);
		Matrix4f InterpolateScaling(float animationTime)

};

