/*****************************************************************//**
 * \file   MiscMath.h
 * \brief  standalone math functions
 *
 * \date   September 2021
 *********************************************************************/

#pragma once

#include "Quaternion.h"
#include "Vector3f.h"

	/**
	 * decompose a matrix into its scale, rotation and translation components
	 */
void Decompose(const Matrix4f &m, Vector3f &scaleOut, Quaternion &rotationOut, Vector3f &translationOut);

	/**
	 * returns a point between the start and end determined by the interpolant (0.0f to 1.0f)
	 */
float Lerp(float start, float end, float interpolant);

	/**
	 * returns a value determined by 4 points and the x and z positions
	 * first the liner interpolation of the a->b->x triangle then the c->d->x triangles are determined
	 * Then the results of the lerps are compared to the z value
	 */
float BiLerp(float a, float b, float c, float d, float x, float z);

	/**
	 * convert radians to degrees
	 */
float RadToDegrees(float rads);

	/**
	 * convert degrees to radians
	 */
float DegreesToRad(float degrees);

	/**
	 * create a perspective matrix from field of view Y, aspect ratio, near and far clip planes
	 */
Matrix4f Perspective(float fovyDegrees, float aspect, float near, float far);

	/**
	 * create a look at view matrix from eye position lookat point and up vector
	 */
Matrix4f LookAt(const Vector3f &eyePos, const Vector3f &lookAtPoint, const Vector3f &upVec);
