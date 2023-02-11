/*****************************************************************//**
 * \file   Matrix3f.h
 *
 * \date   30 September 2021
 *********************************************************************/

#pragma once

#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/gtx/matrix_decompose.hpp>
#include <glm/glm/mat3x3.hpp>

class Vector3f;
class Quaternion;

	/**
	 * matrix 3x3 float class
	 */
class Matrix3f
{
public:
		/**
		 * constructs identity matrix
		 *
		 */
	Matrix3f();

		/**
		 * constructs diagonal matrix.
		 *
		 * \param n all diagonal values
		 */
	Matrix3f(float n);

		/**
		 * get value pointer of this matrix, essentially pointer to the first element of this matrix array
		 *
		 * \return first element of matrix array
		 */
	float *ValuePtr();

		/**
		 * get inverse of matrix.
		 *
		 * \return
		 */
	Matrix3f Inverse() const;

		/**
		 * get transposed matrix.
		 *
		 * \return
		 */
	Matrix3f Transpose() const;

		/**
		 * multiply 2 matrix4f's together
		 *
		 * \param other right hand side matrix
		 * \return value of result matrix
		 */
	Matrix3f operator*(const Matrix3f &other);

		/**
		 * multiply 2 matrix4f's together
		 *
		 * \param other right hand side matrix
		 * \return value of result matrix
		 */
	Matrix3f operator*(const Matrix3f &other) const;

		/**
		 * multiply this matrix by another and assign the value to this matrix
		 *
		 * \param other right hand side matrix
		 * \return reference to this matrix object
		 */
	Matrix3f &operator*=(Matrix3f other);

private:
	/**
	 * constructs based on glm mat3x3.
	 *
	 * \param m
	 */
	Matrix3f(glm::mat3x3 m);

	/**
	 * wrapped matrix data scructure.
	 */
	glm::mat3x3 m_mat;

	friend class Quaternion;
	friend Vector3f operator/(const Vector3f &lhs, const Matrix3f &rhs);
	friend Vector3f operator*(const Matrix3f &lhs, const Vector3f &rhs);
	friend Vector3f operator*(const Vector3f &lhs, const Matrix3f &rhs);
	friend Matrix3f operator*(float lhs, const Matrix3f &rhs);
};
