#pragma once
#include "types.h"

Vector<unsigned char, 3> _RandomPixelColor();
void _PutPixel(Vector<int, 2> a, Vector<unsigned char, 3> color);
void _DrawLine(Vector<int, 2> a, Vector<int, 2> b, Vector<unsigned char, 3> color);
void _DrawPolygon(Vector<int, 2> p[3], Vector<unsigned char, 3> color, bool fill_polygon);