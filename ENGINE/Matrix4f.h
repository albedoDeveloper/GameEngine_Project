/*****************************************************************//**
 * \file   Matrix4f.h
 *
 * \date   September 2021
 *********************************************************************/

#pragma once

#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/gtx/matrix_decompose.hpp>
#include <assimp/matrix4x4.h>

class Vector3f;

	/**
	 * matrix 4 float class
	 */
class Matrix4f
{
public:
		/**
		 * constructs identity matrix
		 *
		 */
	Matrix4f();

		/**
		 * apply translation to this matrix
		 *
		 * \param v translation to apply
		 */
	void Translate(const Vector3f &v);

		/**
		 * extract the translation from this matrix.
		 *
		 * \param v
		 * \return
		 */
	Matrix4f GetTranslate(const Vector3f &v) const;

		/**
		 * extract the rotation from this matrix.
		 *
		 * \param q
		 * \return
		 */
	Matrix4f GetRotate(const Quaternion &q) const;

		/**
		 * apply scale to this matrix
		 *
		 * \param v scale to apply
		 */
	void Scale(Vector3f v);

		/**
		 * apply rotation to this matrix.
		 *
		 * \param q
		 */
	void Rotate(const Quaternion &q);


		/**
		 * Get inverse of this matrix.
		 */
	Matrix4f Inverse();

		/**
		 * Extract scale from matrix.
		 *
		 * \param v
		 * \return
		 */
	Matrix4f GetScale(const Vector3f &v) const;

		/**
		 * get value pointer of this matrix, essentially pointer to the first element of this matrix array
		 *
		 * \return first element of matrix array
		 */
	float *ValuePtr();

		/**
		 * Remove translation from this matrix.
		 *
		 */
	void RemoveTranslation();

		/**
		 * Convert orientation aprt of matrix to quaternion.
		 */
	Quaternion ToQuat();

		/**
		 * multiply 2 matrix4f's together
		 *
		 * \param other right hand side matrix
		 * \return value of result matrix
		 */
	Matrix4f operator*(const Matrix4f &other);

		/**
		 * multiply 2 matrix4f's together
		 *
		 * \param other right hand side matrix
		 * \return value of result matrix
		 */
	Matrix4f operator*(const Matrix4f &other) const;

		/**
		 * multiply this matrix by another and assign the value to this matrix
		 *
		 * \param other right hand side matrix
		 * \return reference to this matrix object
		 */
	Matrix4f &operator*=(Matrix4f other);

		/**
		 * construct diagonal matrix.
		 *
		 * \param m diagonal values
		 */
	Matrix4f(glm::mat4 m);

		/// @brief Converts matrix from an assimp matrix to our facaded matrix
		/// @param from 
		/// @return 
	Matrix4f ConvertAiMatrixToMatrix4f(const aiMatrix4x4 &from);
private:
		/// @brief wrapped data structure
	glm::mat4 m_mat;

	friend void Decompose(const Matrix4f &m, Vector3f &scaleOut, Quaternion &rotationOut, Vector3f &positionOut);
	friend Matrix4f Perspective(float fovyDegrees, float aspect, float near, float far);
	friend Matrix4f LookAt(const Vector3f &eye, const Vector3f &centre, const Vector3f &up);
	friend Matrix4f Ortho(float left, float right, float bottom, float top, float near, float far);
	friend class Quaternion;
};
