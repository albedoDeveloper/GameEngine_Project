#include "Quaternion.h"
#include "Vector3f.h"
#include <glm/glm/gtc/quaternion.hpp>
#include "Matrix4f.h"

Quaternion::Quaternion()
	:m_quat(glm::identity<glm::quat>())
{}

float Quaternion::DotProduct(Quaternion oQuat)
{
	return glm::dot(m_quat, oQuat.m_quat);
}

Quaternion Quaternion::Conjugate() const
{
	return glm::conjugate(m_quat);
}

void Quaternion::Rotate(float degrees, const Vector3f &axis)
{
	m_quat = glm::rotate(m_quat, glm::radians(degrees), glm::vec3(axis.GetX(), axis.GetY(), axis.GetZ()));
}

Vector3f Quaternion::GetAxis() const
{
	glm::vec3 axis = glm::axis(m_quat);
	return Vector3f(
		axis.x,
		axis.y,
		axis.z
	);
}

float Quaternion::GetAxisAngleRadians() const
{
	return glm::angle(m_quat);
}

Vector3f Quaternion::GetEulerAnglesDegrees() const
{
	glm::vec3 axis = glm::degrees(glm::eulerAngles(m_quat));
	return Vector3f(
		axis.x,
		axis.y,
		axis.z
	);
}

void Quaternion::SetEulerAnglesDegrees(float x, float y, float z)
{
	m_quat = glm::quat(glm::vec3(
		glm::radians(x),
		glm::radians(y),
		glm::radians(z)
	));
}

float Quaternion::GetX() const
{
	return m_quat.x;
}

float Quaternion::GetY() const
{
	return m_quat.x;
}

float Quaternion::GetZ() const
{
	return m_quat.z;
}

float Quaternion::GetW() const
{
	return m_quat.w;
}

void Quaternion::SetX(float x)
{
	m_quat.x = x;
}

void Quaternion::SetY(float y)
{
	m_quat.y = y;
}

void Quaternion::SetZ(float z)
{
	m_quat.z = z;
}

void Quaternion::SetW(float w)
{
	m_quat.w = w;
}

Quaternion Quaternion::GetInverse()
{
	return glm::inverse(m_quat);
}

Matrix4f Quaternion::Mat4Cast() const
{
	return glm::mat4_cast(m_quat);
}
