#pragma once
#include "types.h"

namespace DrawInternal
{
	Vector<unsigned char, 3> _RandomPixelColor();
	void _PutPixel(Vector<int, 2> a, Vector<unsigned char, 3> color);
	void _PutPixelWithZBuffer(Vector<int, 2> a, Vector<unsigned char, 3> color, unsigned char zcolor);
	void _DrawLine(Vector<int, 2> a, Vector<int, 2> b, Vector<unsigned char, 3> color);
	void _DrawPolygon(Vector<float, 3> p[3], Vector<unsigned char, 3> color = Vector<unsigned char, 3>({ 0,0,0 }), bool fill_polygon = false);
};