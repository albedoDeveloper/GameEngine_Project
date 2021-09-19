#include "Camera.h"

Camera::Camera()
	:
	FOV{ 80.f },
	NearClip{ 0.02f },
	FarClip{ 2000 },
	Projection{ CameraProjection::PERSPECTIVE }
{
}