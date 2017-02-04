#include "camera.h"
#include "types.h"
#include "my_math.h"
#include "config.h"

float Camera::getFov() const { return tanf(ArcDegreesToRadians(focalLength) / 2.0f); }
void Camera::ShiftFocalLength(float change) { focalLength += change; }

void Camera::ShiftLocation(Vector3f shift)
{
	Vector4f vectorAdjustedForRotation = Vector3::toVector4(shift, 0.f);
	transformVectorByArray(constructRotationMatrix<float>(config.camera.Rotation), vectorAdjustedForRotation);

	Origin[0] += vectorAdjustedForRotation[0];
	Origin[1] += vectorAdjustedForRotation[1];
	Origin[2] += vectorAdjustedForRotation[2];
}

void Camera::ShiftRotation(Vector3f rotate)
{
	Rotation[0] += rotate[0];
	Rotation[1] += rotate[1];
	Rotation[2] += rotate[2];
}
