/*****************************************************************//**
 * \file   Quaternion.h
 *
 * \date   September 2021
 *********************************************************************/

#pragma once

#include <glm/glm/gtc/quaternion.hpp>

class Matrix4f;
class Matrix3f;
class Vector3f;

	/**
	 * quaternion class, used for orientation and rotations. interacts with Vector3f and Matrix4f
	 */
class Quaternion
{
public:
		/**
		 * constructs an identity quaternion
		 */
	Quaternion();

	/**
	 * constructs an identity quaternion using individual w,x,y,z values
	 */
	Quaternion(float x, float y, float z, float w);

		/**
		 * Conjugation of a quaternian
		 *
		 * \return Conjugation of a quaternian
		 */
	Quaternion Conjugate() const;

		/**
		 * Rotates around a given axis
		 *
		 * \param Rotates around a given axis
		 * \param Rotates around a given axis
		 */
	void Rotate(float degrees, const Vector3f &axis);

		/**
		 * get the axis of rotation. use GetAxisAngleRadians() to get the corresponding angle
		 *
		 * \return axis of rotation
		 */
	Vector3f GetAxis() const;

		/**
		 * get the angle in radians. use GetAxis() to get the corresponding axis
		 *
		 * \return angle in radians
		 */
	float GetAxisAngleRadians() const;

		/**
		* get euler angles in degrees
		*
		* \return
		*/
	Vector3f GetEulerAnglesDegrees() const;

		/**
		* set orientation based on euler angles in degrees
		*
		* \param x
		* \param y
		* \param z
		*/
	void SetEulerAnglesDegrees(float x, float y, float z);

		/**
		* @brief x value accessor
		* @return the value of X
		*/
	float GetX() const;

		/**
		* @brief y value accessor
		* @return the value of Y
		*/
	float GetY() const;

		/**
		 * @brief z value accessor
		 * @return the value of W
		*/
	float GetZ() const;

		/**
		* @brief w value accessor
		* @return the value of W
		*/
	float GetW() const;

		/**
		* @brief x value mutator
		* @param x desired value of X
		*/
	void SetX(float x);

		/**
		* @brief y value mutator
		* @param y desired value of Y
		*/
	void SetY(float y);

		/**
		* @brief z value mutator
		* @param z desired value of Z
		*/
	void SetZ(float z);

		/**
		* @brief w value mutator
		* @param w desired value of W
		*/
	void SetW(float w);

		/**
		 * get quaternion inverse
		 *
		 * \return inverse
		 */
	Quaternion GetInverse();

		/**
		 * cast this quaternions orientation to a matrix 4
		 *
		 * \return
		 */
	Matrix4f Mat4Cast() const;

	Matrix3f Mat3Cast() const;


	/**
	 * Spherical interperolation between 2 quaternions.
	 *
	 * \param one
	 * \param two
	 * \param scaleFactor
	 * \return
	 */
	Quaternion Slerp(const Quaternion &two, float scaleFactor);

	Quaternion Normalized() const;

	void Normalize();

	void IntegrateAngVel(const Vector3f &v, float scale);

	Quaternion &operator+=(const Quaternion &other);

	Quaternion operator*(float scalar);

	Quaternion operator*(const Quaternion &rhs);

	Quaternion operator+(const Quaternion &rhs);

private:
	friend class Vector3f;
	friend class Matrix4f;
	friend Quaternion operator*(float lhs, const Quaternion &rhs);

	/** quaternion value */
	glm::quat m_quat;

	/**
	 * private constructor. so math library type is not exposed
	 *
	 * \param q quaternion to copy from
	 */
	Quaternion(glm::quat q)
		:m_quat(q)
	{}
};
