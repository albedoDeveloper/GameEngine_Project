#pragma once

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/constants.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include "Quaternion.h"

	/**
	 * @brief Stores information about a vector or point in three dimensions as floats
	*/
class Vector3f
{
public:
		/**
		 * @brief Default constructor
		*/
	Vector3f()
		:m_vec(1, 1, 1)
	{}

		/// <summary>
		/// Non-default Constructor
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <param name="z"></param>
	Vector3f(float x, float y, float z)
		:m_vec(x, y, z)
	{

	}

		/**
		 * @brief Moves the vector by a relative amount
		 * @param v The vector to add to this vector
		*/
	void Translate(const Vector3f &v)
	{
		m_vec += glm::vec3(v.GetX(), v.GetY(), v.GetZ());
	}

	float *ValuePtr()
	{
		return glm::value_ptr(m_vec);
	}

		/**
		 * @brief Scales the vector by a relative amount
		 * @param x X component of the scaling factor
		 * @param y Y component of the scaling factor
		 * @param z Z component of the scaling factor
		*/
	void Scale(float x, float y, float z)
	{
		m_vec.x *= x;
		m_vec.y *= y;
		m_vec.z *= z;
	}

		/**
		 * @brief x value accessor
		 * @return the value of X
		*/
	float GetX() const
	{
		return m_vec.x;
	}

		/**
		 * @brief y value accessor
		 * @return the value of Y
		*/
	float GetY() const
	{
		return m_vec.y;
	}

		/**
		 * @brief z value accessor
		 * @return the value of Z
		*/
	float GetZ() const
	{
		return m_vec.z;
	}

		/**
		 * @brief x value mutator
		 * @param x the desired value of X
		*/
	void SetX(float x)
	{
		m_vec.x = x;
	}

		/**
		 * @brief y value mutator
		 * @param y the desired value of Y
		*/
	void SetY(float y)
	{
		m_vec.y = y;
	}

		/**
		 * @brief z value mutator
		 * @param z the desired value of Z
		*/
	void SetZ(float z)
	{
		m_vec.z = z;
	}

	float Magnitude() const
	{
		return glm::length(m_vec);
	}

	void SetMagnitude(float length)
	{
		m_vec = (length / glm::length(m_vec)) * m_vec;
	}

		/// <summary>
		/// Cross product of two vectors
		/// </summary>
		/// <param name="oVec"></param>
		/// <returns></returns>
	Vector3f crossProduct(Vector3f oVec)
	{
		return glm::cross(m_vec, oVec.m_vec);
	}

		/// <summary>
		/// Dot Product of two vectors
		/// </summary>
		/// <param name="oVec"></param>
		/// <returns></returns>
	float dotProduct(Vector3f oVec)
	{
		return glm::dot(m_vec, oVec.m_vec);
	}

		/// <summary>
		/// Normalise a vector
		/// </summary>
		/// <param name="oVec"></param>
		/// <returns></returns>
	Vector3f Normalise(Vector3f oVec)
	{
		return glm::normalize(oVec.m_vec);
	}

	float Rad2Deg(float rad)
	{
		return rad * 180 / glm::pi<float>();
	}

	Vector3f Rad2Deg()
	{
		Vector3f temp = m_vec;
		Vector3f newVec;
		newVec.SetX(Rad2Deg(temp.GetX()));
		newVec.SetY(Rad2Deg(temp.GetY()));
		newVec.SetZ(Rad2Deg(temp.GetZ()));
		return newVec;
	}

		/// <summary>
		/// Operator + overload
		/// </summary>
		/// <param name="oVec"></param>
		/// <returns></returns>
	Vector3f operator+(Vector3f oVec)
	{
		return m_vec + oVec.m_vec;
	}

		/// <summary>
		/// Operator * overload
		/// </summary>
		/// <param name="oVec"></param>
		/// <returns></returns>
	Vector3f operator*(const Vector3f &oVec)
	{
		return m_vec * oVec.m_vec;
	}

		/// <summary>
		/// Operator * overload
		/// </summary>
		/// <param name="num"></param>
		/// <returns></returns>
	Vector3f operator*(const float &num)
	{
		return glm::vec3(m_vec.x * num, m_vec.y * num, m_vec.z * num);
	}

		/**
		 * @brief division operator
		 * @param oVec the vector to divide by
		 * @return result of division
		*/
	Vector3f operator/(const Vector3f &oVec)
	{
		return m_vec / oVec.m_vec;
	}

		/// <summary>
		/// Operator - overload
		/// </summary>
		/// <param name="oVec"></param>
		/// <returns></returns>
	Vector3f operator-(const Vector3f &oVec)
	{
		return m_vec - oVec.m_vec;
	}

		/**
		 * @brief assignment operator
		 * @param oVec the vector to set this vector to
		 * @return the value of the vector
		*/
	Vector3f operator=(const Vector3f &oVec)
	{
		return m_vec = oVec.m_vec;
	}


	Vector3f operator*(const Quaternion &quat)
	{
		return m_vec * quat.m_quat;
	}

private:
		/// <summary>
		/// Member Variable vector
		/// </summary>
	glm::vec3 m_vec;

		/// <summary>
		/// Copy Constructor
		/// </summary>
		/// <param name="v"></param>
	Vector3f(glm::vec3 v)
		:m_vec(v)
	{}

	friend Matrix4f LookAt(const Vector3f &eye, const Vector3f &centre, const Vector3f &up);
};
