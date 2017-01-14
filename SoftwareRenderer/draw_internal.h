#pragma once
#include "types.h"

namespace DrawInternal {
	void _DrawLine(Vector<int, 2> a, Vector<int, 2> b, Vector<unsigned char, 3> color);
	Vector<unsigned char, 3> _RandomPixelColor();
	void _PutPixel(Vector<int, 2> a, Vector<unsigned char, 3> color);
	void _PutPixelWithZBuffer(Vector<int, 2> a, Vector<unsigned char, 3> color, float zValue);
	void _DrawPolygon(Vector<float, 3> p[3], Vector<unsigned char, 3> color = Vector<unsigned char, 3>({ 0,0,0 }), int drawMode = 0);
}
