#pragma once
#include "types.h"

class ObjectData
{
public:
	Vector<float, 3> Origin = Vector<float, 3>({ 0.0, 0.0, 0.0 });
	Vector<float, 3> Rotation = Vector<float, 3>({ 0.0, 0.0, 0.0 });
	Vector<float, 3> Scale = Vector<float, 3>({ 1.0, 1.0, 1.0 });
};