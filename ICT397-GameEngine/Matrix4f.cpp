#include <glm/glm/gtc/quaternion.hpp>
#include "Quaternion.h"
#include "Matrix4f.h"
#include "Vector3f.h"

Matrix4f &Matrix4f::operator*=(Matrix4f other)
{
	m_mat = m_mat * other.m_mat;
	return *this;
}

Matrix4f::Matrix4f(glm::mat4 m)
	:m_mat{ m }
{
}

Matrix4f::Matrix4f()
	: m_mat{ 1.0f }
{
}

void Matrix4f::Translate(Vector3f v)
{
	m_mat = glm::translate(m_mat, glm::vec3(v.GetX(), v.GetY(), v.GetZ()));
}

void Matrix4f::Scale(Vector3f v)
{
	m_mat = glm::scale(m_mat, glm::vec3(v.GetX(), v.GetY(), v.GetZ()));
}

float *Matrix4f::ValuePtr()
{
	return glm::value_ptr(m_mat);
}

Matrix4f Matrix4f::operator*(Matrix4f other)
{
	return m_mat * other.m_mat;
}

