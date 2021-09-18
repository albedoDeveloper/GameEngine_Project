#include "MiscMath.h"
#include "Matrix4f.h"

void Decompose(const Matrix4f &m, Vector3f &scaleOut, Quaternion &rotationOut, Vector3f &positionOut)
{
	glm::mat4 mat(m.m_mat);
	glm::vec3 scale(scaleOut.GetX(), scaleOut.GetY(), scaleOut.GetZ());
	glm::quat rot(rotationOut.GetW(), rotationOut.GetX(), rotationOut.GetY(), rotationOut.GetZ());
	glm::vec3 pos(positionOut.GetX(), positionOut.GetY(), positionOut.GetZ());
	glm::vec3 temp1;
	glm::vec4 temp2;

	glm::decompose(
		mat,
		scale,
		rot,
		pos,
		temp1,
		temp2
	);

	scaleOut.SetX(scale.x);
	scaleOut.SetY(scale.y);
	scaleOut.SetZ(scale.z);
	rotationOut.SetX(rot.x);
	rotationOut.SetY(rot.y);
	rotationOut.SetZ(rot.z);
	rotationOut.SetW(rot.w);
	positionOut.SetX(pos.x);
	positionOut.SetY(pos.y);
	positionOut.SetZ(pos.z);
}

float Lerp(float start, float end, float time)
{
	return start + time * (end - start);
}

float BiLerp(float a, float b, float c, float d, float x, float z)
{
	float abx = Lerp(a, b, x);
	float dcx = Lerp(d, c, x);
	return Lerp(abx, dcx, z);
}

float RadToDegrees(float rads)
{
	return glm::degrees(rads);
}

float DegreesToRad(float degrees)
{
	return glm::radians(degrees);
}

Matrix4f Perspective(float fovyDegrees, float aspect, float near, float far)
{
	return glm::perspective(glm::radians(fovyDegrees), aspect, near, far);
}

Matrix4f LookAt(const Vector3f &eye, const Vector3f &centre, const Vector3f &up)
{
	return glm::lookAt(eye.m_vec, centre.m_vec, up.m_vec);
}
