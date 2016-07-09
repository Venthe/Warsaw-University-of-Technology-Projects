#include "types.h"
#include "config.h"
#include "draw_window_elements.h"
#include "draw_commons.h"

void _MyFillRect(Vector<int, 2> a, Vector<int, 2> b, Vector<unsigned char, 3> color, bool full_size, bool fillMarked)
{
	int* window_buffer = static_cast<int*>(config.backbuffer);

	// Sort corners.
	if (a[0] > b[0]) std::swap(a[0], b[0]);
	if (a[1] > b[1]) std::swap(a[1], b[1]);

	// If full_size, mark whole area as drawable
	if (full_size)
	{
		a[0] = 0;
		a[1] = 0;
		b[0] = config.bufferSize[0];
		b[1] = config.bufferSize[1];
	}

	int delta_x = b[0] - a[0]; // Specify shift to next line
	window_buffer += (config.bufferSize[0] * a[1]) + a[0]; // move to initial x,y point

	for (int current_height = a[1]; current_height != b[1]; current_height++) // (Outer) Height
	{
		int scan_line = 0;
		int single_pixel = 0;
		for (int current_width = a[0]; current_width != b[0]; current_width++) { // (Inner) Width

			if (fillMarked)
			{
				if (single_pixel == 0) {
					int* single_pixel_window_buffer = window_buffer;
					for (int k = current_width; k <= b[0]; k++)
					{
						if (((*single_pixel_window_buffer >> 24) & 0xff) == 0xff) {
							single_pixel++;
						}
						*single_pixel_window_buffer++;
					}
				}
				if (scan_line != single_pixel)
				{
					if (((*window_buffer >> 24) & 0xff) == 0xff) scan_line++;
					if (scan_line > 0)
					{
						*window_buffer++ = (0 << 24) + (color[0] << 16) + (color[1] << 8) + color[2];
						continue;
					}
				}
				*window_buffer++;
			}
			else *window_buffer++ = (color[0] << 16) + (color[1] << 8) + color[2];
		}
		if (!full_size) window_buffer += config.bufferSize[0] - delta_x;
	}
}

void FillRect(bool random) // Fill with random noise
{
	if (random) _MyFillRect(Vector<int, 2>({ 0, 0 }), Vector<int, 2>({ 0, 0 }), _RandomPixelColor(), true, false);
	else FillRect();
}

void FillRect(Vector<int, 2> a, Vector<int, 2> b, Vector<unsigned char, 3> color) { _MyFillRect(a, b, color, false, false); } // Fill a rect with a color
void FillRect(Vector<unsigned char, 3> color) { _MyFillRect(Vector<int, 2>({ 0, 0 }), Vector<int, 2>({ 0, 0 }), color, true, false); } // Fill whole drawing space with a color

void DrawGrid(int density, Vector<unsigned char, 3> color)
{
	for (int i = 0; i < ((config.bufferSize[0]) / density) + 1; i++)
	{
		DrawLine(Vector<int, 2>({ i * density, 0 }), Vector<int, 2>({ i * density, config.bufferSize[1] }), color);
		DrawLine(Vector<int, 2>({ 0, i * density }), Vector<int, 2>({ config.bufferSize[0], i * density }), color);
	}
}