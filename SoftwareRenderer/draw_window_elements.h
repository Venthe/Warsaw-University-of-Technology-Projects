#ifndef __DRAW_WINDOW_ELEMENTS_H
#define __DRAW_WINDOW_ELEMENTS_H

class WindowElements
{
private:
	void _MyFillRect(Vector<int, 2> a, Vector<int, 2> b, Vector<unsigned char, 3> color, bool full_size, bool fillMarked) const;
public:
	void FillRect(bool random) const; // Fills drawing area with noise
	void FillRect(Vector<int, 2> a, Vector<int, 2> b, Vector<unsigned char, 3> color) const;
	void FillRect(Vector<unsigned char, 3> color = Vector<unsigned char, 3>({ 0, 0, 0 })) const; // Fills whole drawing area with a certain color
	static void DrawGrid(int density = 32, Vector<unsigned char, 3> color = Vector<unsigned char, 3>({ 32, 32, 32 }));
};

#endif