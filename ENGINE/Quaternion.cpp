#include "Quaternion.h"
#include "Vector3f.h"
#include <glm/glm/gtc/quaternion.hpp>
#include "Matrix4f.h"
#include "Matrix3f.h"

Quaternion::Quaternion()
	:m_quat(glm::identity<glm::quat>())
{}

Quaternion::Quaternion(float x, float y, float z, float w)
	: m_quat(glm::quat(w, x, y, z))
{}

Quaternion Quaternion::Inverse() const
{
	return glm::inverse(m_quat);
}

void Quaternion::Rotate(float degrees, const Vector3f &axis)
{
	m_quat = glm::rotate(m_quat, glm::radians(degrees), glm::vec3(axis.GetX(), axis.GetY(), axis.GetZ()));
	Normalize();
}

float Quaternion::GetMagnitude() const
{
	return glm::length(m_quat);
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
	glm::vec3 axis = glm::eulerAngles(m_quat);
	return Vector3f(
		glm::degrees(axis.x),
		glm::degrees(axis.y),
		glm::degrees(axis.z)
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
	return m_quat.y;
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


Quaternion Quaternion::Slerp(const Quaternion &two, float scaleFactor)
{
	Quaternion temp(glm::slerp(m_quat, glm::quat(two.GetW(), two.GetX(), two.GetY(), two.GetZ()), scaleFactor));

	return temp;
}

Quaternion Quaternion::Normalized() const
{
	return glm::normalize(m_quat);
}

void Quaternion::Normalize()
{
	m_quat = glm::normalize(m_quat);
}

void Quaternion::IntegrateAngVel(const Vector3f &v, float scale)
{
	glm::quat w(
		0.f,
		v.GetX(),
		v.GetY(),
		v.GetZ()
	);
	m_quat -= (scale / 2.f) * w * m_quat;
}

Quaternion &Quaternion::operator+=(const Quaternion &other)
{
	m_quat += other.m_quat;
	return *this;
}

Quaternion Quaternion::operator*(float scalar)
{
	return m_quat * scalar;
}

Quaternion Quaternion::operator*(const Quaternion &rhs)
{
	return m_quat * rhs.m_quat;
}

Quaternion Quaternion::operator+(const Quaternion &rhs)
{
	return m_quat + rhs.m_quat;
}

Matrix3f Quaternion::Mat3Cast() const
{
	return glm::mat3_cast(m_quat);
}