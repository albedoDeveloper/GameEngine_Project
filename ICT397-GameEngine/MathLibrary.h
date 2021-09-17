#pragma once

#include <glm/glm/glm.hpp>

#include <glm/glm/common.hpp>
#include <glm/glm/gtx/matrix_decompose.hpp>

/**
 * @brief A coordinate or vector in 3D space, with unsigned integer data
*/
class Vector3u
{
private:
	/// <summary>
	/// Member Variable vector
	/// </summary>
	glm::uvec3 m_vec;

	/// <summary>
	/// Copy Constructor
	/// </summary>
	/// <param name="v"></param>
	Vector3u(glm::uvec3 v)
		:m_vec(v)
	{

	}

public:
	/**
	 * @brief default constructor
	*/
	Vector3u()
		:m_vec(1, 1, 1)
	{}

	/// <summary>
	/// Non-default Constructor
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="z"></param>
	Vector3u(unsigned x, unsigned y, unsigned z)
		:m_vec(x, y, z)
	{

	}

	/**
	 * @brief x accessor
	 * @return the value of X
	*/
	unsigned GetX() const
	{
		return m_vec.x;
	}
	/**
	 * @brief y accessor
	 * @return the value of Y
	*/
	unsigned GetY() const
	{
		return m_vec.y;
	}
	/**
	 * @brief z accessor
	 * @return the value of Z
	*/
	unsigned GetZ() const
	{
		return m_vec.z;
	}
	/**
	 * @brief x mutator
	 * @param x desired value of X
	*/
	void SetX(unsigned x)
	{
		m_vec.x = x;
	}
	/**
	 * @brief y mutator
	 * @param y desired value of Y
	*/
	void SetY(unsigned y)
	{
		m_vec.y = y;
	}
	/**
	 * @brief z mutator
	 * @param z despired value of Z
	*/
	void SetZ(unsigned z)
	{
		m_vec.z = z;
	}

	/// <summary>
	/// Cross product of two vectors
	/// </summary>
	/// <param name="oVec"></param>
	/// <returns></returns>
	//Vector3u crossProduct(Vector3u oVec)
	//{
	//	Vector3u rVec(glm::cross(m_vec, oVec.m_vec));
	//	return rVec;
	//}

	/// <summary>
	/// Dot Product of two vectors
	/// </summary>
	/// <param name="oVec"></param>
	/// <returns></returns>
	//float dotProduct(Vector3u oVec)
	//{
	//	float result(glm::dot(m_vec, oVec.m_vec));

	//	return result;
	//}

	/// <summary>
	/// Operator + overload
	/// </summary>
	/// <param name="oVec"></param>
	/// <returns></returns>
	Vector3u operator+(const Vector3u &oVec)
	{
		Vector3u addedVec(m_vec + oVec.m_vec);

		return addedVec;
	}

	/// <summary>
	/// Operator * overload
	/// </summary>
	/// <param name="oVec"></param>
	/// <returns></returns>
	Vector3u operator*(const Vector3u &oVec)
	{
		Vector3u multipliedVec(m_vec * oVec.m_vec);

		return multipliedVec;
	}

	/// <summary>
	/// Operator - overload
	/// </summary>
	/// <param name="oVec"></param>
	/// <returns></returns>
	Vector3u operator-(const Vector3u &oVec)
	{
		Vector3u subtractedVec(m_vec - oVec.m_vec);

		return subtractedVec;
	}
};

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
		:m_vec(1, 1)
	{}

	/// <summary>
	/// Non-default Constructor
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="z"></param>
	Vector2f(float x, float y)
		:m_vec(x, y)
	{

	}

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

//unsigned chars
struct Vector3uc
{
	unsigned char x;
	unsigned char y;
	unsigned char z;

	Vector3uc(unsigned char newX, unsigned char newY, unsigned char newZ)
		:x{ newX }, y{ newY }, z{ newZ }
	{
	}
};



////////////////////////////////////////////////////////////
//					Standalone math funcs				 //
///////////////////////////////////////////////////////////

void Decompose(const Matrix4f &m, Vector3f &scaleOut, Quaternion &rotationOut, Vector3f &positionOut);

/**
	 * @brief returns a point between the start and end determined by strength
*/
float Lerp(float start, float end, float time);

/**
	 * @brief returns a value determined by 4 points and the x and z positions
	 * first the liner interpolation of the a->b->x triangle then the c->d->x triangles are determined
	 * Then the results of the lerps are compared to the z value
*/
float BiLerp(float a, float b, float c, float d, float x, float z);

float RadToDegrees(float rads);

float DegreesToRad(float degrees);
