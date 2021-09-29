/*****************************************************************//**
 * \file   Matrix4f.h
 *
 * \date   September 2021
 *********************************************************************/

#pragma once

#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/gtx/matrix_decompose.hpp>

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

	Matrix4f GetTranslate(const Vector3f &v) const;

	Matrix4f GetRotate(const Quaternion &q) const;

		/**
		 * apply scale to this matrix
		 *
		 * \param v scale to apply
		 */
	void Scale(Vector3f v);

	Matrix4f GetScale(const Vector3f &v) const;

		/**
		 * get value pointer of this matrix, essentially pointer to the first element of this matrix array
		 *
		 * \return first element of matrix array
		 */
	float *ValuePtr();

	void RemoveTranslation();

	float& SetMatrixElement(unsigned int row, unsigned int column);
	
		/**
		 * multiply 2 matrix4f's together
		 *
		 * \param other right hand side matrix
		 * \return value of result matrix
		 */
	Matrix4f operator*(const Matrix4f &other);

	Matrix4f operator*(const Matrix4f &other) const;

		/**
		 * multiply this matrix by another and assign the value to this matrix
		 *
		 * \param other right hand side matrix
		 * \return reference to this matrix object
		 */
	Matrix4f &operator*=(Matrix4f other);

	glm::mat4 GetMatrix() { return m_mat; }
	Matrix4f(glm::mat4 m);
private:


	glm::mat4 m_mat;

	friend void Decompose(const Matrix4f &m, Vector3f &scaleOut, Quaternion &rotationOut, Vector3f &positionOut);
	friend Matrix4f Perspective(float fovyDegrees, float aspect, float near, float far);
	friend Matrix4f LookAt(const Vector3f &eye, const Vector3f &centre, const Vector3f &up);
	friend Matrix4f Ortho(float left, float right, float bottom, float top, float near, float far);
	friend class Quaternion;
};
