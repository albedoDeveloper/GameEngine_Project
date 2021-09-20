#include "Vector2f.h"

Vector2f::Vector2f()
	:m_vec(0.f, 0.f)
{}

Vector2f::Vector2f(float x, float y)
	: m_vec(x, y)
{}

float Vector2f::GetX() const
{
	return m_vec.x;
}

float Vector2f::GetY() const
{
	return m_vec.y;
}

void Vector2f::SetX(float x)
{
	m_vec.x = x;
}

void Vector2f::SetY(float y)
{
	m_vec.y = y;
}

Vector2f Vector2f::operator+(const Vector2f &oVec)
{
	Vector2f addedVec(m_vec + oVec.m_vec);

	return addedVec;
}

Vector2f Vector2f::operator*(const Vector2f &oVec)
{
	Vector2f multipliedVec(m_vec * oVec.m_vec);

	return multipliedVec;
}

Vector2f Vector2f::operator-(const Vector2f &oVec)
{
	return (m_vec - oVec.m_vec);
}

Vector2f::Vector2f(glm::vec2 v)
	:m_vec(v)
{}