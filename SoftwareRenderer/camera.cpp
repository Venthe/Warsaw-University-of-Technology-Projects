#include "camera.h"
#include "types.h"
#include "mymath.h"

void Camera::ShiftFocalLength(float change)
{
	FocalLength += change;
}

void Camera::ShiftLocation(Vector<float, 3> shift)
{
	Origin[0] += shift[0];
	Origin[1] += shift[1];
	Origin[2] += shift[2];
}

void Camera::ShiftRotation(Vector<float, 3> rotate)
{
	Rotation[0] += rotate[0];
	Rotation[1] += rotate[1];
	Rotation[2] += rotate[2];
}