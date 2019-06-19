#pragma once
#include "types.h"

using namespace MyMath;

namespace DrawWindowElements
{
	void FillRectangle(Vector2i a, Vector2i b, Vector3uc color);
	void FillRectangle(Vector3uc color = {0, 0, 0}); // Fills whole drawing area with a certain color
	void DrawGrid(int density = 32, Vector3uc color = {32, 32, 32});
	void ClearZBuffer();
};
