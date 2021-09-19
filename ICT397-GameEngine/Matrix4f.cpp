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

void Matrix4f::Translate(const Vector3f &v)
{
	m_mat = glm::translate(m_mat, glm::vec3(v.GetX(), v.GetY(), v.GetZ()));
}

Matrix4f Matrix4f::GetTranslate(const Vector3f &v) const
{
	return glm::translate(m_mat, v.m_vec);
}

Matrix4f Matrix4f::GetRotate(const Quaternion &q) const
{
	return glm::rotate(m_mat, q.GetAxisAngleRadians(), q.GetAxis().m_vec);
}

void Matrix4f::Scale(Vector3f v)
{
	m_mat = glm::scale(m_mat, glm::vec3(v.GetX(), v.GetY(), v.GetZ()));
}

Matrix4f Matrix4f::GetScale(const Vector3f &v) const
{
	return glm::scale(m_mat, v.m_vec);
}

float *Matrix4f::ValuePtr()
{
	return glm::value_ptr(m_mat);
}

Matrix4f Matrix4f::operator*(const Matrix4f &other)
{
	return m_mat * other.m_mat;
}

Matrix4f Matrix4f::operator*(const Matrix4f &other) const
{
	return m_mat * other.m_mat;
}

