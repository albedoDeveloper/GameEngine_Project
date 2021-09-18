#pragma once

#include <glm/glm/gtc/quaternion.hpp>

class Matrix4f;
class Vector3f;

class Quaternion
{
public:
	Quaternion();

		/// <summary>
		/// dot product of two Quaternions
		/// </summary>
		/// <param name="oQuat"></param>
		/// <returns></returns>
	float DotProduct(Quaternion oQuat);

		/// <summary>
		/// Conjugation of a quaternian
		/// </summary>
		/// <param name="oQuat"></param>
		/// <returns></returns>
	Quaternion Conjugate() const;

		/**
		 * @brief Rotates around a given axis
		 * @param degrees number of degrees to turn
		 * @param axis the axis to rotate around
		*/
	void Rotate(float degrees, const Vector3f &axis);

	Vector3f GetAxis() const;

	float GetAxisAngleRadians() const;

	Vector3f GetEulerAngles() const;

	// x,y,z in rads
	void SetEulerAngles(float x, float y, float z);

		/**
		 * @brief x value accessor
		 * @return the value of X
		*/
	float GetX() const
	{
		return m_quat.x;
	}

		/**
		 * @brief y value accessor
		 * @return the value of Y
		*/
	float GetY() const
	{
		return m_quat.y;
	}

		/**
		 * @brief z value accessor
		 * @return the value of W
		*/
	float GetZ() const
	{
		return m_quat.z;
	}

		/**
		 * @brief w value accessor
		 * @return the value of W
		*/
	float GetW() const
	{
		return m_quat.w;
	}

		/**
		 * @brief x value mutator
		 * @param x desired value of X
		*/
	void SetX(float x)
	{
		m_quat.x = x;
	}

		/**
		 * @brief y value mutator
		 * @param y desired value of Y
		*/
	void SetY(float y)
	{
		m_quat.y = y;
	}

		/**
		 * @brief z value mutator
		 * @param z desired value of Z
		*/
	void SetZ(float z)
	{
		m_quat.z = z;
	}

		/**
		 * @brief w value mutator
		 * @param w desired value of W
		*/
	void SetW(float w)
	{
		m_quat.w = w;
	}

	Quaternion GetInverse();

	Matrix4f Mat4Cast() const;

private:
	friend class Vector3f;
	friend class Matrix4f;

		/// <summary>
		/// Quaternion Member variable
		/// </summary>
	glm::quat m_quat;

		/// <summary>
		/// Copy Constructor
		/// </summary>
		/// <param name="q"></param>
	Quaternion(glm::quat q)
		:m_quat(q)
	{}
};
