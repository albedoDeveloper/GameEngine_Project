#pragma once

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/quaternion.hpp>
#include <glm/glm/vec3.hpp>
#include <glm/glm/common.hpp>
#include <glm/glm/gtx/matrix_decompose.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

class Quaternion;

/**
 * @brief Stores information about a vector or point in three dimensions as floats
*/
class Vector3f
{
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
	{
	}

public:
	/**
	 * @brief Default constructor
	*/
	Vector3f()
		:m_vec(1,1,1)
	{
	}

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
	void Translate(const Vector3f& v)
	{
		m_vec += glm::vec3(v.GetX(), v.GetY(), v.GetZ());
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
		return rad*180/ glm::pi<float>();
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
	Vector3f operator*(const Vector3f& oVec)
	{
		return m_vec * oVec.m_vec;
	}

	/// <summary>
	/// Operator * overload
	/// </summary>
	/// <param name="num"></param>
	/// <returns></returns>
	Vector3f operator*(const float& num)
	{
		return glm::vec3(m_vec.x * num, m_vec.y* num, m_vec.z* num);
	}

	/**
	 * @brief division operator
	 * @param oVec the vector to divide by
	 * @return result of division
	*/
	Vector3f operator/(const Vector3f& oVec)
	{
		return m_vec / oVec.m_vec;
	}

	/// <summary>
	/// Operator - overload
	/// </summary>
	/// <param name="oVec"></param>
	/// <returns></returns>
	Vector3f operator-(const Vector3f& oVec)
	{
		return m_vec - oVec.m_vec;
	}

	/**
	 * @brief assignment operator
	 * @param oVec the vector to set this vector to
	 * @return the value of the vector
	*/
	Vector3f operator=(const Vector3f& oVec)
	{
		return m_vec = oVec.m_vec;
	}


	Vector3f operator*(const Quaternion& quat);

};

class Vector4f
{
private:
	/// <summary>
	/// Member variable
	/// </summary>
	glm::vec4 m_vec;

	/// <summary>
	/// copy constuctor
	/// </summary>
	/// <param name="v"></param>
	Vector4f(glm::vec4 v)
		:m_vec(v)
	{

	}

public:

	/// <summary>
	/// Non default constructor
	/// </summary>
	/// <param name="w"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="z"></param>
	Vector4f(float w, float x, float y, float z)
		:m_vec(x, y, z, w)
	{

	}

	float operator[](int index)
	{
		return m_vec[index];
	}
};

class Matrix4f
{
private:
	glm::mat4 m_mat;
	Matrix4f(glm::mat4);

public:
	Matrix4f();

	const glm::mat4 GetGLMmat4() const;

	void Translate(Vector3f v);
	//void Rotate(Quaternion q);
	void Scale(Vector3f v);

	float* GetTypePtr()
	{
		return glm::value_ptr(m_mat);
	}

	static Matrix4f Cast(const Quaternion &q);

	Matrix4f operator*(Matrix4f other) const;
};

class Quaternion
{
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
	{
	}

public:
	///// <summary>
	///// Non Default Constructor
	///// </summary>
	///// <param name="w"></param>
	///// <param name="x"></param>
	///// <param name="y"></param>
	///// <param name="z"></param>
	//Quaternion(float w, float x, float y, float z)
	//	:m_quat(w, x, y, z)
	//{
	//}

	Quaternion()
		:m_quat(glm::identity<glm::quat>())
	{
	}

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
	void Rotate(float degrees, const Vector3f& axis)
	{
		m_quat = glm::rotate(m_quat, degrees, glm::vec3(axis.GetX(), axis.GetY(), axis.GetZ()));
	}
	
	//float GetAngleDegrees() const
	//{
	//	glm::quat aa(1, 1, 0, 0);
	//	float test = glm::angle(aa);
	//	return glm::degrees(glm::angle(m_quat));
	//}

	Vector3f GetAxis() const
	{
		glm::vec3 axis = glm::axis(m_quat);
		return Vector3f(
			axis.x,
			axis.y,
			axis.z
		);
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
};

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
	{
	}

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
	Vector3u operator+(const Vector3u& oVec)
	{
		Vector3u addedVec(m_vec + oVec.m_vec);

		return addedVec;
	}

	/// <summary>
	/// Operator * overload
	/// </summary>
	/// <param name="oVec"></param>
	/// <returns></returns>
	Vector3u operator*(const Vector3u& oVec)
	{
		Vector3u multipliedVec(m_vec * oVec.m_vec);

		return multipliedVec;
	}

	/// <summary>
	/// Operator - overload
	/// </summary>
	/// <param name="oVec"></param>
	/// <returns></returns>
	Vector3u operator-(const Vector3u& oVec)
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
	{
	}

public:
	/**
	 * @brief default constructor
	*/
	Vector2f()
		:m_vec(1, 1)
	{
	}

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
	Vector2f operator+(const Vector2f& oVec)
	{
		Vector2f addedVec(m_vec + oVec.m_vec);

		return addedVec;
	}

	/// <summary>
	/// Operator * overload
	/// </summary>
	/// <param name="oVec"></param>
	/// <returns></returns>
	Vector2f operator*(const Vector2f& oVec)
	{
		Vector2f multipliedVec(m_vec * oVec.m_vec);

		return multipliedVec;
	}

	/// <summary>
	/// Operator - overload
	/// </summary>
	/// <param name="oVec"></param>
	/// <returns></returns>
	Vector2f operator-(const Vector2f& oVec)
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

void Decompose(const Matrix4f& m, Vector3f& scaleOut, Quaternion& rotationOut, Vector3f& positionOut);


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