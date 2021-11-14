#include "Bone.h"

Bone::Bone(const std::string &name, int ID, const aiNodeAnim *channel)
{
	m_NumPositions = channel->mNumPositionKeys;
	m_Name = name;
	m_ID = ID;
	m_LocalTransform = Matrix4f();
	m_NumPositions = channel->mNumPositionKeys;

	for (int positionIndex = 0; positionIndex < m_NumPositions; positionIndex++)
	{
		aiVector3D aiPosition = channel->mPositionKeys[positionIndex].mValue;
		float timeStamp = channel->mPositionKeys[positionIndex].mTime;
		KeyPosition data;
		data.position = Vector3f(aiPosition.x, aiPosition.y, aiPosition.z);
		data.timeStamp = timeStamp;
		m_Positions.push_back(data);
	}

	m_NumRotations = channel->mNumRotationKeys;
	
	for (int rotationIndex = 0; rotationIndex < m_NumRotations; rotationIndex++)
	{
		aiQuaternion aiOrientation = channel->mRotationKeys[rotationIndex].mValue;
		float timeStamp = channel->mRotationKeys[rotationIndex].mTime;
		KeyRotation data;
		data.orientation = Quaternion(aiOrientation.x, aiOrientation.y, aiOrientation.z, aiOrientation.w);
		data.timeStamp = timeStamp;
		m_Rotations.push_back(data);
	}

	m_NumScalings = channel->mNumScalingKeys;
	
	for (int keyIndex = 0; keyIndex < m_NumScalings; keyIndex++)
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
	for (int transIndex = 0; transIndex < m_NumPositions - 1; transIndex++)
	{
		if (animationTime < m_Positions[transIndex + 1].timeStamp)
			return transIndex;
	}
	assert(0);
}

int  Bone::GetRotationIndex(float animationTime)
{
	for (int rotIndex = 0; rotIndex < m_NumRotations - 1; rotIndex++)
	{
		if (animationTime < m_Rotations[rotIndex + 1].timeStamp)
			return rotIndex;
	}
	assert(0);
}

int  Bone::GetScaleIndex(float animationTime)
{
	for (int sIndex = 0; sIndex < m_NumScalings - 1; sIndex++)
	{
		if (animationTime < m_Scales[sIndex + 1].timeStamp)
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
		tempMatrix.Translate(m_Positions[0].position);
	}

	else
	{
		int beforeIndex = GetPositionIndex(animationTime);
		int afterIndex = beforeIndex + 1;
		float scaleFactor = GetScaleFactor(m_Positions[beforeIndex].timeStamp, m_Positions[afterIndex].timeStamp, animationTime);
		Vector3f finalPosition = m_Positions[beforeIndex].position.Mix(m_Positions[afterIndex].position, scaleFactor);
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
		rotation = m_Rotations[0].orientation;
	}

	else
	{
		int beforeIndex = GetRotationIndex(animationTime);
		int afterIndex = beforeIndex + 1;
		float scaleFactor = GetScaleFactor(m_Rotations[beforeIndex].timeStamp, m_Rotations[afterIndex].timeStamp, animationTime);
		rotation = m_Rotations[beforeIndex].orientation.Slerp(m_Rotations[afterIndex].orientation, scaleFactor);
	}
	
	return rotation.Normalized().Mat4Cast();
}

Matrix4f Bone::InterpolateScaling(float animationTime)
{
	Matrix4f tempMatrix;

	if (1 == m_NumScalings)
	{
		tempMatrix.Scale(m_Scales[0].scale);

		return tempMatrix;
	}

	int beforeIndex = GetScaleIndex(animationTime);
	int afterIndex = beforeIndex + 1;
	float scaleFactor = GetScaleFactor(m_Scales[beforeIndex].timeStamp, m_Scales[afterIndex].timeStamp, animationTime);
	Vector3f finalScale = m_Scales[beforeIndex].scale.Mix(m_Scales[afterIndex].scale, scaleFactor);
	tempMatrix.Scale(finalScale);
	return tempMatrix;
}
