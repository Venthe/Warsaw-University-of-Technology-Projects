#pragma once
#include "color.h"
#include "types.h"

namespace DrawInternal
{
	void DrawLine(Vector2i a, Vector2i b, Vector3uc color = MyColor::RED);
	void DrawPolygon(Facef p, Color color = MyColor::GRAY, int drawMode = 0);
}
