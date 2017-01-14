#pragma once
#include "types.h"
#include "object_handler.h"

class Camera : public ObjectData
{
public:
	float FocalLength;
	float clipNear;
	float clipFar;

	void ShiftFocalLength(float change);
	void ShiftLocation(Vector<float, 3> shift);
	void ShiftRotation(Vector<float, 3> rotate);
};
