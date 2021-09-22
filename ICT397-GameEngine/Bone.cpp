#include "Bone.h"

Bone::Bone(const std::string& name, int ID, const aiNodeAnim* channel)
{
	m_NumPositions = channel->mNumPositionKeys;

	for (int positionIndex = 0; positionIndex < m_NumPositions; ++positionIndex)
	{
		aiVector3D aiPosition = channel->mPositionKeys[positionIndex].mValue;
		float timeStamp = channel->mPositionKeys[positionIndex].mTime;
		KeyPosition data;
		data.position = Vector3f (aiPosition.x, aiPosition.y, aiPosition.z);
		data.timeStamp = timeStamp;
		m_Positions.push_back(data);
	}

	m_NumRotations = channel->mNumRotationKeys;
	for (int rotationIndex = 0; rotationIndex < m_NumRotations; ++rotationIndex)
	{
		aiQuaternion aiOrientation = channel->mRotationKeys[rotationIndex].mValue;
		float timeStamp = channel->mRotationKeys[rotationIndex].mTime;
		KeyRotation data;
		data.orientation = Quaternion(aiOrientation.w, aiOrientation.x, aiOrientation.y, aiOrientation.z);
		data.timeStamp = timeStamp;
		m_Rotations.push_back(data);
	}

	m_NumScalings = channel->mNumScalingKeys;
	for (int keyIndex = 0; keyIndex < m_NumScalings; ++keyIndex)
	{
		aiVector3D scale = channel->mScalingKeys[keyIndex].mValue;
		float timeStamp = channel->mScalingKeys[keyIndex].mTime;
		KeyScale data;
		data.scale = Vector3f(scale.x, scale.y, scale.z);
		data.timeStamp = timeStamp;
		m_Scales.push_back(data);
	}
}


void Bone::UpdateBone(float animationTime)
{
	Matrix4f translation = InterpolatePosition(animationTime);
	Matrix4f rotation = InterpolateRotation(animationTime);
	Matrix4f scale = InterpolateScaling(animationTime);
	
	m_LocalTransform = translation * rotation * scale;
}



int Bone::GetPositionIndex(float animationTime)
{
	for (int index = 0; index < m_NumPositions - 1; ++index)
	{
		if (animationTime < m_Positions[index + 1].timeStamp)
			return index;
	}
	assert(0);
}

int  Bone::GetRotationIndex(float animationTime)
{
	for (int index = 0; index < m_NumRotations - 1; ++index)
	{
		if (animationTime < m_Rotations[index + 1].timeStamp)
			return index;
	}
	assert(0);
}

int  Bone::GetScaleIndex(float animationTime)
{
	for (int index = 0; index < m_NumScalings - 1; ++index)
	{
		if (animationTime < m_Scales[index + 1].timeStamp)
			return index;
	}
	assert(0);
}

float Bone::GetScaleFactor(float lastTimeStamp, float nextTimeStamp, float animationTime)
{
	float scaleFactor = 0.0f;
	float midWayLength = animationTime - lastTimeStamp;
	float framesDiff = nextTimeStamp - lastTimeStamp;
	scaleFactor = midWayLength / framesDiff;
	return scaleFactor;
}

Matrix4f Bone::InterpolatePosition(float animationTime)
{
	Matrix4f tempMatrix;
	
	if (1 == m_NumPositions)
	{
		tempMatrix.Translate(m_Positions[0].position);
		return tempMatrix;
	}
	
	int p0Index = GetPositionIndex(animationTime);
	int p1Index = p0Index + 1;
	float scaleFactor = GetScaleFactor(m_Positions[p0Index].timeStamp,m_Positions[p1Index].timeStamp, animationTime);
	Vector3f finalPosition = glm::mix(m_Positions[p0Index].position, m_Positions[p1Index].position, scaleFactor);
	tempMatrix.Translate(finalPosition);
	
	return tempMatrix;
}



Matrix4f Bone::InterpolateRotation(float animationTime)
{
	Matrix4f tempMatrix;
	
	if (1 == m_NumRotations)
	{
		auto rotation = glm::normalize(m_Rotations[0].orientation);
		return glm::toMat4(rotation);
	}

	int p0Index = GetRotationIndex(animationTime);
	int p1Index = p0Index + 1;
	float scaleFactor = GetScaleFactor(m_Rotations[p0Index].timeStamp,m_Rotations[p1Index].timeStamp, animationTime);
	Quaternion finalRotation = glm::slerp(m_Rotations[p0Index].orientation, m_Rotations[p1Index].orientation, scaleFactor);
	finalRotation = glm::normalize(finalRotation);
	tempMatrix.
	
	return glm::toMat4(finalRotation);

}

Matrix4f Bone::InterpolateScaling(float animationTime)
{
	Matrix4f tempMatrix;
	
	if (1 == m_NumScalings)
	{
		tempMatrix.Scale(m_Scales[0].scale);
		
		return tempMatrix;
	}
		

	int p0Index = GetScaleIndex(animationTime);
	int p1Index = p0Index + 1;
	float scaleFactor = GetScaleFactor(m_Scales[p0Index].timeStamp, m_Scales[p1Index].timeStamp, animationTime);
	Vector3f finalScale = glm::mix(m_Scales[p0Index].scale, m_Scales[p1Index].scale, scaleFactor);
	tempMatrix.Scale(finalScale);
	return tempMatrix;
}
