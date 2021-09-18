#pragma once

#include "Quaternion.h"
#include "Vector3f.h"

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

Matrix4f Perspective(float fovyDegrees, float aspect, float near, float far);

Matrix4f LookAt(const Vector3f &eye, const Vector3f &centre, const Vector3f &up);

