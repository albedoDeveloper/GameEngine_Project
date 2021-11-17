/*****************************************************************//**
 * \file   Vector2f.h
 *
 * \date   September 2021
 *********************************************************************/

#pragma once

#include <glm/glm/vec2.hpp>

	/**
	 * @brief A point or vector in 2d space, stored with float data
	*/
class Vector2f
{
public:
		/**
		 * @brief default constructor. default value of 0,0 in x,y
		*/
	Vector2f();

		/**
		 * constructor set x and y
		 *
		 * \param x
		 * \param y
		 */
	Vector2f(float x, float y);

		/**
		 * get x value
		 *
		 * \return
		 */
	float GetX() const;

		/**
		 * get y value
		 *
		 * \return
		 */
	float GetY() const;

		/**
		 * set x value
		 *
		 * \param x
		 */
	void SetX(float x);

		/**
		 * set y value
		 *
		 * \param y
		 */
	void SetY(float y);

		/**
		 * add another vector to this one and get the new value
		 *
		 * \param oVec other vector
		 * \return new value of added vectors
		 */
	Vector2f operator+(const Vector2f &oVec);

		/**
		 * multiply another vector to this one and get the result value
		 *
		 * \param oVec other vector
		 * \return value of mulitplication
		 */
	Vector2f operator*(const Vector2f &oVec);

		/**
		 * subtract another vector from this one and get the result value.
		 *
		 * \param oVec other vector
		 * \return result value of subtraction
		 */
	Vector2f operator-(const Vector2f &oVec);

private:
		/** vector 2 value */
	glm::vec2 m_vec;

		/**
		 * made private to prevent clients know about glm type.
		 *
		 * \param v vector to copy the values from
		 */
	Vector2f(glm::vec2 v);
};
