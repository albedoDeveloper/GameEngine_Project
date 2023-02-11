#include <glm/glm/gtc/quaternion.hpp>
#include "Quaternion.h"
#include "Matrix3f.h"
#include "Vector3f.h"

Matrix3f &Matrix3f::operator*=(Matrix3f other)
{
	m_mat = m_mat * other.m_mat;
	return *this;
}

Matrix3f::Matrix3f(glm::fmat3x3 m)
	:m_mat{ m }
{}

Matrix3f::Matrix3f()
	: m_mat{ glm::fmat3x3(1.0f) }
{}

Matrix3f::Matrix3f(float n)
	: m_mat{ glm::fmat3x3(n) }
{}

float *Matrix3f::ValuePtr()
{
	return glm::value_ptr(m_mat);
}

Matrix3f Matrix3f::Inverse() const
{
	return glm::inverse(m_mat);
}

Matrix3f Matrix3f::Transpose() const
{
	return glm::transpose(m_mat);
}


Matrix3f Matrix3f::operator*(const Matrix3f &other)
{
	return m_mat * other.m_mat;
}

Matrix3f Matrix3f::operator*(const Matrix3f &other) const
{
	return m_mat * other.m_mat;
}
