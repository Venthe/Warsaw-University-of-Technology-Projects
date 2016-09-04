#pragma once
#include "types.h"

namespace DrawWindowElements {
	void FillRectangle(bool random); // Fills drawing area with noise
	void FillRectangle(Vector<int, 2> a, Vector<int, 2> b, Vector<unsigned char, 3> color);
	void FillRectangle(Vector<unsigned char, 3> color = Vector<unsigned char, 3>({ 0, 0, 0 })); // Fills whole drawing area with a certain color
	void DrawGrid(int density = 32, Vector<unsigned char, 3> color = Vector<unsigned char, 3>({ 32, 32, 32 }));
	void ClearZBuffer();
};