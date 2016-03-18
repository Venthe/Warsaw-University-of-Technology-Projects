#include "config.h"
#include "draw.h"
#include <random>

void _PutPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b)
{
	if (x < 0 || y < 0)
		return;
	if (x > settings.bufferSizeX || y > settings.bufferSizeY)
		return;

	int* buffer = (int*)settings.backbuffer;
	buffer += (y*settings.bufferSizeX) + x;
	//unsigned char * color = (r << 16) + (g << 8) + (b);
	*buffer = (r << 16) + (g << 8) + (b);
}
int _RandomPixelColor() {
	return (((unsigned char)(rand() % 0xFF) << 16) | ((unsigned char)(rand() % 0xFF) << 8) | ((unsigned char)(rand() % 0xFF)));
}
void _MyFillRect(int x, int y, int maxX, int maxY, unsigned char r, unsigned char g, unsigned char b, bool random, bool fullsize) {
	if (x<0 || y<0 || maxX < 0 || maxY < 0)
		return;
	if (x > settings.bufferSizeX || y > settings.bufferSizeY || maxX>settings.bufferSizeX || maxY>settings.bufferSizeY)
		return;
	if ((x == maxX&&y == maxY) && !fullsize) {
		_PutPixel(x, y, r, g, b);
		return;
	}
	int * windowbuffer = (int*)settings.backbuffer;
	if (fullsize) {
		for (int height = 0; height < settings.bufferSizeX; height++) { // Height
			for (int width = 0; width < settings.bufferSizeY; width++) { // Width
				if (random) *windowbuffer++ = _RandomPixelColor();
				else *windowbuffer++ = (r << 16) + (g << 8) + (b);
			}
		}
	}
	else
	{
		// move to initial x,y point
		int deltaX = x - maxX;
		if (deltaX < 0) deltaX *= -1;
		windowbuffer += (settings.bufferSizeX*y) + (x);
		for (int height = y; height < maxY; height++) { // Height
			for (int width = x; width < maxX; width++) { // Width
				*windowbuffer++ = (r << 16) + (g << 8) + (b);
			}
			windowbuffer += settings.bufferSizeX-deltaX;
		}
	}
}
void FillRect(int x, int y, int maxX, int maxY, unsigned char red, unsigned char green, unsigned char blue)
{
	_MyFillRect(x, y, maxX, maxY, red, green, blue, false, false);
}
void FillRect(bool random)
{
	if (random) _MyFillRect(0, 0, 0, 0, (unsigned char)0, (unsigned char)0, (unsigned char)0, true, true);
	else FillRect();
}
void FillRect(unsigned char red, unsigned char green, unsigned char blue) {
	_MyFillRect(0, 0, 0, 0, red, green, blue, false, true);
}
void FillRect() {
	_MyFillRect(0, 0, 0, 0, (unsigned char)0, (unsigned char)0, (unsigned char)0, false, true);
}
void DrawLine(int x, int y, int tx, int ty, unsigned char r, unsigned char g, unsigned char b) {
	// Bounds checking
	if (x < 0 || y < 0 || tx < 0 || ty < 0)
		return;
	if (x > settings.bufferSizeX || y > settings.bufferSizeY || tx>settings.bufferSizeX || ty>settings.bufferSizeY)
		return;

	// This precious little bit of optimalization
	if (x == tx && y == ty) {
		_PutPixel(x, y, r, g, b);
		return;
	}

	int deltax = tx - x; //deltax==0 -> vertical
	if (deltax == 0) {
		for (int cury = y; cury != ty;) {
			_PutPixel(x, cury, r, g, b);
			if (cury < ty) cury++;
			else cury--;
		}
		return;
	}

	int deltay = ty - y; //deltay==0 -> horizontal
	if (deltay == 0) {
		for (int curx = x; curx != tx;) {
			_PutPixel(curx, y, r, g, b);
			if (curx < tx) curx++;
			else curx--;
		}
		return;
	}

	//TODO: Bersenham's algorithm is broken past this point
	double error = 0.0f; //	real error : = 0
	double deltaerr = (double) deltay / (double) deltax; //	real deltaerr : = abs(deltay / deltax)
	if (deltaerr < 0.0) deltaerr *= -1.0;

	int cury = y; //	int y : = y0

	for (int curx = x; curx != tx;) { // for x from x0 to x1
		_PutPixel(curx, cury,r,g,b); // plot(x, y)
		error += deltaerr; // error : = error + deltaerr
		while (error >= 0.5 && cury!=ty) { // while error ≥ 0.5 then
			_PutPixel(curx, cury,r,g,b); // plot(x, y)
			if (deltay > 0) { cury++; } // y : = y + sign(y1 - y0)
			else { cury--; }
			error -= 1.0; // error := error - 1.0
		}
		if (deltax > 0) { curx++; }
		else { curx--; }
	}
}
void DrawCircle(int x, int y, int radius,double step, unsigned char r, unsigned char g, unsigned char b)
{
	const double pi = 3.14159265358979323846;
	for (double angle = 0.0; angle < 360.0;angle += step)
		_PutPixel(x+radius*sin((angle / 360.0)*2*pi), y+radius*cos((angle / 360.0) * 2 *pi), r, g, b);
}
void DrawFan(int x, int y, int radius, double step, unsigned char r, unsigned char g, unsigned char b)
{
	const double pi = 3.14159265358979323846;
	for (double angle = 0.0; angle < 360.0; angle += step)
		DrawLine(x, y, x + radius*sin((angle/360.0)*2*pi), y + radius*cos((angle / 360.0)*2*pi), r, g, b);
}