#include "MiscMath.h"
#include "Matrix4f.h"

void Decompose(const Matrix4f &m, Vector3f &scaleOut, Quaternion &rotationOut, Vector3f &positionOut)
{
	glm::mat4 mat(m.m_mat);
	glm::vec3 scale(1.f, 1.f, 1.f);
	glm::quat rot(1.f, 0.f, 0.f, 0.f);
	glm::vec3 pos(0.f, 0.f, 0.f);
	glm::fvec3 temp1(0.f, 0.f, 0.f);
	glm::vec4 temp2(0.f, 0.f, 0.f, 0.f);

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

float Lerp(float start, float end, float interpolant)
{
	return start + (end - start) * interpolant;
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

Matrix4f Ortho(float left, float right, float bottom, float top, float near, float far)
{
	return glm::ortho(left, right, bottom, top, near, far);
}

Vector3f operator/(const Vector3f &lhs, const Matrix3f &rhs)
{
	return lhs.m_vec / rhs.m_mat;
}

Vector3f operator*(const Matrix3f &lhs, const Vector3f &rhs)
{
	return lhs.m_mat * rhs.m_vec;
}

Vector3f operator-(const Vector3f &lhs, const Vector3f &rhs)
{
	return lhs.m_vec - rhs.m_vec;
}

Vector3f operator*(const Vector3f &lhs, const Vector3f &rhs)
{
	return glm::cross(lhs.m_vec, rhs.m_vec);
}

Vector3f operator/(const Vector3f &lhs, float rhs)
{
	return lhs.m_vec / rhs;
}

Vector3f operator*(float lhs, const Vector3f &rhs)
{
	return lhs * rhs.m_vec;
}

Vector3f operator*(const Vector3f &lhs, const Matrix3f &rhs)
{
	return lhs.m_vec * rhs.m_mat;
}

Vector3f operator+(float lhs, const Vector3f &rhs)
{
	return lhs + rhs.m_vec;
}

Vector3f operator/(float lhs, const Vector3f &rhs)
{
	return lhs / rhs.m_vec;
}

Matrix3f operator*(float lhs, const Matrix3f &rhs)
{
	return lhs * rhs.m_mat;
}

Quaternion operator*(float lhs, const Quaternion &rhs)
{
	return lhs * rhs.m_quat;
}
