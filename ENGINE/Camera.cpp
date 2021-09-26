#include "Camera.h"

Camera::Camera()
	:
	FOV{ 80.f },
	NearClip{ 0.1f },
	FarClip{ 30 },
	Projection{ CameraProjection::PERSPECTIVE }
{
}
