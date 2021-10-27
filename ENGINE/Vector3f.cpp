#include "Vector3f.h"
#include "MiscMath.h"
#include "Matrix4f.h"

Vector3f::Vector3f()
	:m_vec{ 0.f,0.f,0.f }
{}

Vector3f::Vector3f(float x, float y, float z)
	: m_vec(x, y, z)
{}

Vector3f &Vector3f::operator+=(const Vector3f &v)
{
	m_vec += v.m_vec;
	return *this;
}

float *Vector3f::ValuePtr()
{
	return glm::value_ptr(m_vec);
}

void Vector3f::Scale(float x, float y, float z)
{
	m_vec.x *= x;
	m_vec.y *= y;
	m_vec.z *= z;
}

float Vector3f::GetX() const
{
	return m_vec.x;
}

float Vector3f::GetY() const
{
	return m_vec.y;
}

float Vector3f::GetZ() const
{
	return m_vec.z;
}

void Vector3f::SetX(float x)
{
	m_vec.x = x;
}

void Vector3f::SetY(float y)
{
	m_vec.y = y;
}

void Vector3f::SetZ(float z)
{
	m_vec.z = z;
}

float Vector3f::Magnitude() const
{
	return glm::length(m_vec);
}

void Vector3f::SetMagnitude(float length)
{
	m_vec = (length / glm::length(m_vec)) * m_vec;
}

Vector3f Vector3f::crossProduct(Vector3f oVec) const
{
	return glm::cross(m_vec, oVec.m_vec);
}

float Vector3f::dotProduct(Vector3f oVec) const
{
	return glm::dot(m_vec, oVec.m_vec);
}

Vector3f Vector3f::Normalised()
{
	return glm::normalize(m_vec);
}

Vector3f Vector3f::Mix(Vector3f oVec, float scale)
{
	return glm::mix(m_vec, oVec.m_vec, scale);
}

Vector3f Vector3f::Rad2Deg()
{
	Vector3f temp = m_vec;
	Vector3f newVec;
	newVec.SetX(RadToDegrees(temp.GetX()));
	newVec.SetY(RadToDegrees(temp.GetY()));
	newVec.SetZ(RadToDegrees(temp.GetZ()));
	return newVec;
}

Vector3f Vector3f::operator*(const Vector3f &oVec)
{
	return m_vec * oVec.m_vec;
}

Vector3f Vector3f::operator*(const float &num)
{
	return glm::vec3(m_vec.x * num, m_vec.y * num, m_vec.z * num);
}

Vector3f Vector3f::operator/(const Vector3f &oVec)
{
	return m_vec / oVec.m_vec;
}

Vector3f Vector3f::operator-(const Vector3f &oVec)
{
	return m_vec - oVec.m_vec;
}

Vector3f &Vector3f::operator-=(const Vector3f &oVec)
{
	m_vec -= oVec.m_vec;
	return *this;
}

Vector3f Vector3f::operator=(const Vector3f &oVec)
{
	return m_vec = oVec.m_vec;
}

Vector3f Vector3f::operator*(const Quaternion &quat)
{
	return m_vec * quat.m_quat;
}

Vector3f::Vector3f(glm::vec3 v)
	:m_vec(v)
{}

Vector3f Vector3f::operator+(Vector3f oVec)
{
	return m_vec + oVec.m_vec;
}

Vector3f Vector3f::operator+(const Vector3f rhs) const
{
	return m_vec + rhs.m_vec;
}

Matrix4f Vector3f::TranslationMatrix() const
{
	Matrix4f t;
	t.ValuePtr()[3] = m_vec.x;
	t.ValuePtr()[7] = m_vec.y;
	t.ValuePtr()[11] = m_vec.z;
	return t;
}

Matrix4f Vector3f::ScaleMatrix() const
{
	Matrix4f t;
	t.ValuePtr()[0] = m_vec.x;
	t.ValuePtr()[5] = m_vec.y;
	t.ValuePtr()[10] = m_vec.z;
	return t;
}
