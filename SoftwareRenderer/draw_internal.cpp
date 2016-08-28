#include "types.h"
#include "config.h"
#include "draw_internal.h"
#include "main.h"

void DrawInternal::_PutPixel(Vector<int, 2> a, Vector<unsigned char, 3> color)
{
	// Out of bounds checking
	if (a[0] < 0 || a[1] < 0) return;
	if (a[0] >= config.bufferSize[0] || a[1] >= config.bufferSize[1]) return;

	int* buffer = static_cast<int*>(config.backbuffer);

	buffer += (a[1] * config.bufferSize[0]) + (a[0]);
	*buffer = (color[0] << 16) + (color[1] << 8) + (color[2]);
}

Vector<unsigned char, 3> DrawInternal::_RandomPixelColor()
{
	return Vector<unsigned char, 3>({ static_cast<unsigned char>(rand() % 0xff), static_cast<unsigned char>(rand() % 0xff), static_cast<unsigned char>(rand() % 0xff) });
}

void DrawInternal::_DrawLine(Vector<int, 2> a, Vector<int, 2> b, Vector<unsigned char, 3> color)
{
	if (b[1] < a[1]) std::swap(a, b); // Sort by y value

	int delta_x = b[0] - a[0]; //deltax==0 -> vertical
	int delta_y = b[1] - a[1]; //deltay==0 -> horizontal
	if (delta_x == 0 && delta_y == 0)
	{
		_PutPixel(a, color);
	}
	else if (delta_x == 0 || delta_y == 0)
	{
		int current_value;
		int target_value;
		int constant;
		if (delta_x == 0)
		{
			current_value = a[1];
			target_value = b[1];
			constant = a[0];
		}
		else
		{
			current_value = a[0];
			target_value = b[0];
			constant = a[1];
		}
		if (current_value > target_value) std::swap(current_value, target_value);
		Vector<int, 2> pixel;

		for (; current_value < target_value; current_value++)
		{
			if (delta_x == 0) pixel({ constant, current_value });
			else pixel({ current_value, constant });
			pixel({ pixel[0] - 1, pixel[1] - 1 });
			_PutPixel(pixel, color);
		}
		return;
	}

	float delta_error = static_cast<float>(delta_y) / static_cast<float>(delta_x); // real deltaerr : = abs(deltay / deltax)
	if (delta_error < 0.0) delta_error *= -1.0;
	float error = 0.0f;

	int current_y = a[1];

	for (int current_x = a[0]; current_x != b[0];)
	{
		_PutPixel(Vector<int, 2>({ current_x, current_y }), color);
		error += delta_error;
		while (error >= 0.5 && current_y != b[1])
		{
			_PutPixel(Vector<int, 2>({ current_x, current_y }), color);
			current_y++;
			error -= 1.0;
		}
		if (delta_x > 0) current_x++;
		else current_x--;
	}
}

void DrawInternal::_DrawPolygon(Vector<float, 3> _p[3], Vector<unsigned char, 3> color, bool fill_polygon)
{
	Vector<int, 2> p[3];

	for (int i = 0; i < 3; i++)
	{
		p[i][0] = static_cast<int>(_p[i][0]);
		p[i][1] = static_cast<int>(_p[i][1]);
	}

	if (fill_polygon)
	{
		// Sort Polygons by y
		if (p[0][1] > p[1][1]) std::swap(p[1], p[0]);
		if (p[0][1] > p[2][1]) std::swap(p[2], p[0]);
		if (p[1][1] > p[2][1]) std::swap(p[1], p[2]);

		int TotalHeight = p[2][1] - p[0][1];

		for (int y = p[0][1]; y != p[2][1]; y++)
		{
			float CurrentLongx = static_cast<float>((y - p[0][1])) / TotalHeight;
			Vector<int, 2> a;
			Vector<int, 2> b;
			if (y < p[1][1])
			{
				int SegmentHeight = p[1][1] - p[0][1];
				if (SegmentHeight == 0) SegmentHeight++;
				float CurrentShortx = static_cast<float>((y - p[0][1])) / SegmentHeight;
				a({ p[0][0] + static_cast<int>((p[1][0] - p[0][0]) * CurrentShortx), y });
				b({ p[0][0] + static_cast<int>((p[2][0] - p[0][0]) * CurrentLongx), y });
			}
			else
			{
				int SegmentHeight = p[2][1] - p[1][1];
				if (SegmentHeight == 0) SegmentHeight++;
				float CurrentShortx = static_cast<float>((y - p[1][1])) / SegmentHeight;
				a({ p[1][0] + static_cast<int>((p[2][0] - p[1][0]) * CurrentShortx), y });
				b({ p[0][0] + static_cast<int>((p[2][0] - p[0][0]) * CurrentLongx), y });
			}
			_DrawLine(a, b, color);
		}
	}

	else {
		_DrawLine(p[0], p[1], Vector<unsigned char, 3>({ 0, 0xff, 0 }));
		_DrawLine(p[1], p[2], Vector<unsigned char, 3>({ 0, 0xff, 0 }));
		_DrawLine(p[2], p[0], Vector<unsigned char, 3>({ 0xff, 0, 0 }));
	}
}
