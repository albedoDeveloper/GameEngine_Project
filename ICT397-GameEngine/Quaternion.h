#pragma once

#include <glm/glm/gtc/quaternion.hpp>
#include "Vector3f.h"
#include "Matrix4f.h"

class Quaternion
{
public:
	Quaternion()
		:m_quat(glm::identity<glm::quat>())
	{}

		/// <summary>
		/// dot product of two Quaternions
		/// </summary>
		/// <param name="oQuat"></param>
		/// <returns></returns>
	float DotProduct(Quaternion oQuat)
	{
		return glm::dot(m_quat, oQuat.m_quat);
	}

		/// <summary>
		/// Conjugation of a quaternian
		/// </summary>
		/// <param name="oQuat"></param>
		/// <returns></returns>
	Quaternion Conjugate() const
	{
		return glm::conjugate(m_quat);
	}

		/**
		 * @brief Rotates around a given axis
		 * @param degrees number of degrees to turn
		 * @param axis the axis to rotate around
		*/
	void Rotate(float degrees, const Vector3f &axis)
	{
		m_quat = glm::rotate(m_quat, glm::radians(degrees), glm::vec3(axis.GetX(), axis.GetY(), axis.GetZ()));
	}

	Vector3f GetAxis() const
	{
		glm::vec3 axis = glm::axis(m_quat);
		return Vector3f(
			axis.x,
			axis.y,
			axis.z
		);
	}

	float GetAxisAngleRadians() const
	{
		return glm::angle(m_quat);
	}

	Vector3f GetEulerAngles() const
	{
		glm::vec3 axis = glm::eulerAngles(m_quat);
		return Vector3f(
			axis.x,
			axis.y,
			axis.z
		);
	}

	// x,y,z in rads
	void SetEulerAngles(float x, float y, float z)
	{
		m_quat = glm::quat(glm::vec3(x, y, z));
	}

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

	Quaternion GetInverse()
	{
		return glm::inverse(m_quat);
	}

private:
		/// <summary>
		/// Quaternion Member variable
		/// </summary>
	glm::quat m_quat;

	friend Vector3f;
	friend Matrix4f;

		/// <summary>
		/// Copy Constructor
		/// </summary>
		/// <param name="q"></param>
	Quaternion(glm::quat q)
		:m_quat(q)
	{}
};
