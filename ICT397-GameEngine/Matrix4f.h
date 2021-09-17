#pragma once

#include "Vector3f.h"
#include <glm/glm/gtc/type_ptr.hpp>

class Matrix4f
{
public:
	Matrix4f();

	const glm::mat4 GetGLMmat4() const;

	void Translate(Vector3f v);
	//void Rotate(Quaternion q);
	void Scale(Vector3f v);

	float *GetTypePtr()
	{
		return glm::value_ptr(m_mat);
	}

	static Matrix4f Cast(const Quaternion &q);

	Matrix4f operator*(Matrix4f other) const;

private:
	glm::mat4 m_mat;
	Matrix4f(glm::mat4);
};

