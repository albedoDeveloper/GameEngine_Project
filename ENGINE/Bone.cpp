#include "Bone.h"

Bone::Bone(const std::string &name, int ID, const aiNodeAnim *channel)
{
	m_NumPositions = channel->mNumPositionKeys;
	m_Name = name;
	m_ID = ID;
	m_NumPositions = channel->mNumPositionKeys;

	for (int positionIndex = 0; positionIndex < m_NumPositions; positionIndex++)
	{
		aiVector3D aiPos = channel->mPositionKeys[positionIndex].mValue;
		float timeStamp = channel->mPositionKeys[positionIndex].mTime;
		KeyPosition data;
		data.position = Vector3f(aiPos.x, aiPos.y, aiPos.z);
		data.timeStamp = timeStamp;
		m_allPositions.push_back(data);
	}

	m_NumRotations = channel->mNumRotationKeys;
	
	for (int rotationIndex = 0; rotationIndex < m_NumRotations; rotationIndex++)
	{
		aiQuaternion aiRot = channel->mRotationKeys[rotationIndex].mValue;
		float timeStamp = channel->mRotationKeys[rotationIndex].mTime;
		KeyRotation data;
		data.orientation = Quaternion(aiRot.x, aiRot.y, aiRot.z, aiRot.w);
		data.timeStamp = timeStamp;
		m_allRotations.push_back(data);
	}

	m_NumScalings = channel->mNumScalingKeys;
	
	for (int keyIndex = 0; keyIndex < m_NumScalings; keyIndex++)
	{
		aiVector3D aiSize = channel->mScalingKeys[keyIndex].mValue;
		float timeStamp = channel->mScalingKeys[keyIndex].mTime;
		KeyScale data;
		data.scale = Vector3f(aiSize.x, aiSize.y, aiSize.z);
		data.timeStamp = timeStamp;
		m_allScaling.push_back(data);
	}
}


void Bone::UpdateBone(float animationTime)
{
	Matrix4f translation = InterpolatePosition(animationTime);
	Matrix4f rotation = InterpolateRotation(animationTime);
	Matrix4f scale = InterpolateScaling(animationTime);

	m_LocalTransform = translation * rotation * scale;
}



int Bone::GetPosIndex(float animationTime)
{
	for (int transIndex = 0; transIndex < m_NumPositions - 1; transIndex++)
	{
		if (animationTime < m_allPositions[transIndex + 1].timeStamp)
			return transIndex;
	}
	assert(0);
}

int  Bone::GetRotIndex(float animationTime)
{
	for (int rotIndex = 0; rotIndex < m_NumRotations - 1; rotIndex++)
	{
		if (animationTime < m_allRotations[rotIndex + 1].timeStamp)
			return rotIndex;
	}
	assert(0);
}

int  Bone::GetScaleIndex(float animationTime)
{
	for (int sIndex = 0; sIndex < m_NumScalings - 1; sIndex++)
	{
		if (animationTime < m_allScaling[sIndex + 1].timeStamp)
			return sIndex;
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

	if (m_NumPositions == 1)
	{
		tempMatrix.Translate(m_allPositions[0].position);
	}

	else
	{
		int beforeIndex = GetPosIndex(animationTime);
		int afterIndex = beforeIndex + 1;
		float scaleFactor = GetScaleFactor(m_allPositions[beforeIndex].timeStamp, m_allPositions[afterIndex].timeStamp, animationTime);
		Vector3f finalPosition = m_allPositions[beforeIndex].position.Mix(m_allPositions[afterIndex].position, scaleFactor);
		tempMatrix.Translate(finalPosition);
	}
	
	return tempMatrix;
}

Matrix4f Bone::InterpolateRotation(float animationTime)
{
	Matrix4f tempMatrix;
	Quaternion rotation;
	
	if (m_NumRotations == 1)
	{
		rotation = m_allRotations[0].orientation;
	}

	else
	{
		int beforeIndex = GetRotIndex(animationTime);
		int afterIndex = beforeIndex + 1;
		float scaleFactor = GetScaleFactor(m_allRotations[beforeIndex].timeStamp, m_allRotations[afterIndex].timeStamp, animationTime);
		rotation = m_allRotations[beforeIndex].orientation.Slerp(m_allRotations[afterIndex].orientation, scaleFactor);
	}
	
	return rotation.Normalized().Mat4Cast();
}

Matrix4f Bone::InterpolateScaling(float animationTime)
{
	Matrix4f tempMatrix;

	if (1 == m_NumScalings)
	{
		tempMatrix.Scale(m_allScaling[0].scale);
	}

	else
	{
		int beforeIndex = GetScaleIndex(animationTime);
		int afterIndex = beforeIndex + 1;
		float scaleFactor = GetScaleFactor(m_allScaling[beforeIndex].timeStamp, m_allScaling[afterIndex].timeStamp, animationTime);
		Vector3f finalScale = m_allScaling[beforeIndex].scale.Mix(m_allScaling[afterIndex].scale, scaleFactor);
		tempMatrix.Scale(finalScale);
	}
	
	return tempMatrix;
}
