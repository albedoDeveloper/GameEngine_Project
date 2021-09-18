#pragma once

#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/gtx/matrix_decompose.hpp>

class Vector3f;

class Matrix4f
{
public:
	Matrix4f()
		:m_mat{ glm::identity<glm::mat4>() }
	{}

	void Translate(Vector3f v);

	void Scale(Vector3f v);

	float *ValuePtr()
	{
		return glm::value_ptr(m_mat);
	}

	Matrix4f operator*(Matrix4f other);

	Matrix4f &operator*=(Quaternion other);

private:
	Matrix4f(glm::mat4);
	glm::mat4 m_mat;

	friend void Decompose(const Matrix4f &m, Vector3f &scaleOut, Quaternion &rotationOut, Vector3f &positionOut);
	friend Matrix4f Perspective(float fovyDegrees, float aspect, float near, float far);
	friend Matrix4f LookAt(const Vector3f &eye, const Vector3f &centre, const Vector3f &up);
	friend class Quaternion;
};
