#pragma once
#include "types.h"
#include "object_handler.h"

class Camera : public ObjectData
{
public:
	float focalLength;
	float clipNear;
	float clipFar;

	void ShiftFocalLength(float change);
	void ShiftLocation(Vector3f shift);
	void ShiftRotation(Vector3f rotate);

	float getFov() const;
};
