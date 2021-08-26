#include "MathLibrary.h"

// void Vector3f::testFunction()
// {
// 	Vector3f vec(10.0f, 10.0f, 10.0f);
// 	Vector3f vecTwo(10.0f, 15.0f, 20.0f);

// 	vec = vec + vecTwo;
// 	vec = vec - vecTwo;
// 	vec = vec * vecTwo;

// 	Quaternion quat;
// 	Quaternion::Conjugate(quat);

// }

/// <summary>
	/// Operator * overload
	/// </summary>
	/// <param name="quat"></param>
//	/// <returns></returns>
Vector3f Vector3f::operator*(const Quaternion& quat)
{
	return m_vec * quat.m_quat;
}

Matrix4f::Matrix4f()
	:m_mat{ glm::identity<glm::mat4>() }
{
}

const glm::mat4 Matrix4f::GetGLMmat4() const
{
	return m_mat;
}

Matrix4f::Matrix4f(glm::mat4 m)
	: m_mat{ m }
{
}

void Matrix4f::Translate(Vector3f v)
{
	m_mat = glm::translate(m_mat, glm::vec3(v.GetX(), v.GetY(), v.GetZ()));
}

//void Matrix4f::Rotate(Quaternion q)
//{
//	m_mat = glm::rotate(m_mat, q.GetAngleDegrees(), glm::vec3(q.GetAxis().GetX(), q.GetAxis().GetY(), q.GetAxis().GetZ()));
//}

void Matrix4f::Scale(Vector3f v)
{
	m_mat = glm::scale(m_mat, glm::vec3(v.GetX(), v.GetY(), v.GetZ()));
}

Matrix4f Matrix4f::Cast(const Quaternion& q)
{
	return glm::mat4_cast(q.m_quat);
}

Matrix4f Matrix4f::operator*(Matrix4f other) const
{
	return m_mat * other.m_mat;
}

void Decompose(const Matrix4f& m, Vector3f& scaleOut, Quaternion& rotationOut, Vector3f& positionOut)
{
	glm::mat4 mat(m.GetGLMmat4());
	glm::vec3 scale(scaleOut.GetX(), scaleOut.GetY(), scaleOut.GetZ());
	glm::quat rot(rotationOut.GetW(), rotationOut.GetX(), rotationOut.GetY(), rotationOut.GetZ());
	glm::vec3 pos(positionOut.GetX(), positionOut.GetY(), positionOut.GetZ());
	glm::vec3 temp1;
	glm::vec4 temp2;

	glm::decompose(
		mat, 
		scale, 
		rot,
		pos,
		temp1, 
		temp2
	);

	scaleOut.SetX(scale.x);
	scaleOut.SetY(scale.y);
	scaleOut.SetZ(scale.z);
	rotationOut.SetX(rot.x);
	rotationOut.SetY(rot.y);
	rotationOut.SetZ(rot.z);
	rotationOut.SetW(rot.w);
	positionOut.SetX(pos.x);
	positionOut.SetY(pos.y);
	positionOut.SetZ(pos.z);
}

float Lerp(float start, float end, float time)
{
	return start + time * (end - start);
}

float BiLerp(float a, float b, float c, float d, float x, float z)
{
	float abx = Lerp(a, b, x);
	float dcx = Lerp(d, c, x);
	return Lerp(abx, dcx, z);
}

float RadToDegrees(float rads)
{
	return glm::degrees(rads);
}

float DegreesToRad(float degrees)
{
	return glm::radians(degrees);
}
