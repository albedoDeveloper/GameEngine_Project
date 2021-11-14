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

void Matrix4f::Rotate(const Quaternion &q)
{
	m_mat = glm::rotate(m_mat, q.GetAxisAngleRadians(), q.GetAxis().m_vec);
}

Matrix4f Matrix4f::GetScale(const Vector3f &v) const
{
	return glm::scale(m_mat, v.m_vec);
}


float *Matrix4f::ValuePtr()
{
	return glm::value_ptr(m_mat);
}

void Matrix4f::RemoveTranslation()
{
	m_mat = glm::mat4(glm::mat3(m_mat));
}

float &Matrix4f::SetMatrixElement(unsigned int row, unsigned int column)
{
	return m_mat[row][column];
}

Matrix4f Matrix4f::operator*(const Matrix4f &other)
{
	return m_mat * other.m_mat;
}

Matrix4f Matrix4f::operator*(const Matrix4f &other) const
{
	return m_mat * other.m_mat;
}

Quaternion Matrix4f::ToQuat()
{
	return glm::quat_cast(m_mat);

}


Matrix4f Matrix4f::Inverse() 
{
	return glm::inverse(m_mat);
}


Matrix4f Matrix4f::ConvertAiMatrixToMatrix4f(const aiMatrix4x4 &from)
{
	auto aiToMatrix = m_mat;

	//the a,b,c,d in assimp is the row ; the 1,2,3,4 is the column
	m_mat[0][0] = from.a1; 	m_mat[1][0] = from.a2; 	m_mat[2][0] = from.a3; 	m_mat[3][0] = from.a4;
	m_mat[0][1] = from.b1; 	m_mat[1][1] = from.b2; 	m_mat[2][1] = from.b3;  m_mat[3][1] = from.b4;
	m_mat[0][2] = from.c1; 	m_mat[1][2] = from.c2;  m_mat[2][2] = from.c3; 	m_mat[3][2] = from.c4;
	m_mat[0][3] = from.d1; 	m_mat[1][3] = from.d2;  m_mat[2][3] = from.d3; 	m_mat[3][3] = from.d4;

	return m_mat;
}
