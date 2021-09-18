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
		* @brief Default constructor. makes a 0,0,0 vector
		*/
	Vector3f();

		/**
		 * constructor that sets vec values
		 *
		 * \param x
		 * \param y
		 * \param z
		 */
	Vector3f(float x, float y, float z);

		/**
		* @brief adds another vector to this one
		* @param v The vector to add to this vector by
		*/
	Vector3f &operator+= (const Vector3f &v);

		/**
		 * get first element of vector array of floats
		 *
		 * \return
		 */
	float *ValuePtr();

		/**
		* @brief Scales the vector by a relative amount
		* @param x X component of the scaling factor
		* @param y Y component of the scaling factor
		* @param z Z component of the scaling factor
		*/
	void Scale(float x, float y, float z);

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
		 * @return the value of Z
		*/
	float GetZ() const;

		/**
		 * @brief x value mutator
		 * @param x the desired value of X
		*/
	void SetX(float x);

		/**
		 * @brief y value mutator
		 * @param y the desired value of Y
		*/
	void SetY(float y);

		/**
		 * @brief z value mutator
		 * @param z the desired value of Z
		*/
	void SetZ(float z);

		/**
		 * get vectors magnitude
		 *
		 * \return
		 */
	float Magnitude() const;

		/**
		 * set vectors length
		 *
		 * \param length
		 */
	void SetMagnitude(float length);

		/**
		 * cross profuct between this and another vector. Left value is this vector, right is other
		 *
		 * \param oVec other vector
		 * \return cross product value
		 */
	Vector3f crossProduct(Vector3f oVec);

		/**
		 * dot product between two vectors
		 *
		 * \param oVec other vector
		 * \return dot product
		 */
	float dotProduct(Vector3f oVec);

		/**
		 * get a normalised version of this vector
		 *
		 * \return value of normalised vector
		 */
	Vector3f Normalised();

	Vector3f Rad2Deg();

		/// <summary>
		/// Operator + overload
		/// </summary>
		/// <param name="oVec"></param>
		/// <returns></returns>
	Vector3f operator+(Vector3f oVec);

		/// <summary>
		/// Operator * overload
		/// </summary>
		/// <param name="oVec"></param>
		/// <returns></returns>
	Vector3f operator*(const Vector3f &oVec);

		/// <summary>
		/// Operator * overload
		/// </summary>
		/// <param name="num"></param>
		/// <returns></returns>
	Vector3f operator*(const float &num);

		/**
		* @brief division operator
		* @param oVec the vector to divide by
		* @return result of division
		*/
	Vector3f operator/(const Vector3f &oVec);

		/// <summary>
		/// Operator - overload
		/// </summary>
		/// <param name="oVec"></param>
		/// <returns></returns>
	Vector3f operator-(const Vector3f &oVec);

		/**
		* @brief assignment operator
		* @param oVec the vector to set this vector to
		* @return the value of the vector
		*/
	Vector3f operator=(const Vector3f &oVec);

		/**
		* .
		*
		* \param quat
		* \return
		*/
	Vector3f operator*(const Quaternion &quat);

private:
		/// <summary>
		/// Member Variable vector
		/// </summary>
	glm::vec3 m_vec;

		/// <summary>
		/// Copy Constructor
		/// </summary>
		/// <param name="v"></param>
	Vector3f(glm::vec3 v);

		// friendship decleration
	friend Matrix4f LookAt(const Vector3f &eye, const Vector3f &centre, const Vector3f &up);
};
