#pragma once

#include <glm/glm/vec2.hpp>

/**
 * @brief A point or vector in 2d space, stored with float data
*/
class Vector2f
{
private:
	/// <summary>
	/// Member Variable vector
	/// </summary>
	glm::vec2 m_vec;

	/// <summary>
	/// Copy Constructor
	/// </summary>
	/// <param name="v"></param>
	Vector2f(glm::vec2 v)
		:m_vec(v)
	{}

public:
	/**
	 * @brief default constructor
	*/
	Vector2f()
		:m_vec(0.f, 0.f)
	{}

	/// <summary>
	/// Non-default Constructor
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="z"></param>
	Vector2f(float x, float y)
		:m_vec(x, y)
	{}

/**
 * @brief x accessor
 * @return value of X
*/
	float GetX() const
	{
		return m_vec.x;
	}
	/**
	 * @brief y accessor
	 * @return value of Y
	*/
	float GetY() const
	{
		return m_vec.y;
	}
	/**
	 * @brief x mutator
	 * @param x desired value of X
	*/
	void SetX(float x)
	{
		m_vec.x = x;
	}
	/**
	 * @brief y mutator
	 * @param y desired value of Y
	*/
	void SetY(float y)
	{
		m_vec.y = y;
	}

	/// <summary>
	/// Operator + overload
	/// </summary>
	/// <param name="oVec"></param>
	/// <returns></returns>
	Vector2f operator+(const Vector2f &oVec)
	{
		Vector2f addedVec(m_vec + oVec.m_vec);

		return addedVec;
	}

	/// <summary>
	/// Operator * overload
	/// </summary>
	/// <param name="oVec"></param>
	/// <returns></returns>
	Vector2f operator*(const Vector2f &oVec)
	{
		Vector2f multipliedVec(m_vec * oVec.m_vec);

		return multipliedVec;
	}

	/// <summary>
	/// Operator - overload
	/// </summary>
	/// <param name="oVec"></param>
	/// <returns></returns>
	Vector2f operator-(const Vector2f &oVec)
	{
		return (m_vec - oVec.m_vec);
	}
};
