#include "types.h"
#include "config.h"
#include "draw_internal.h"
#include "main.h"
#include <iostream>

void DrawInternal::_PutPixel(Vector<int, 2> a, Vector<unsigned char, 3> color)
{
	// Out of bounds checking
	if (a[0] < 0 || a[1] < 0) return;
	if (a[0] >= config.bufferSize[0] || a[1] >= config.bufferSize[1]) return;

	int* buffer = static_cast<int*>(config.backbuffer);

	buffer += (a[1] * config.bufferSize[0]) + (a[0]);
	*buffer = (color[0] << 16) + (color[1] << 8) + (color[2]);
}

void DrawInternal::_PutPixelWithZBuffer(Vector<int, 2> a, Vector<unsigned char, 3> color, unsigned char zcolor)
{
	zcolor += 1;
	// Out of bounds checking
	if (a[0] < 0 || a[1] < 0) return;
	if (a[0] >= config.bufferSize[0] || a[1] >= config.bufferSize[1]) return;


	unsigned char* zbuffer = static_cast<unsigned char*>(config.zbackbuffer);
	zbuffer += (a[1] * config.bufferSize[0]) + (a[0]);
	if (*zbuffer != 0 && *zbuffer > zcolor) return;
	*zbuffer = zcolor;

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

float _normalizationToUnity(float value, float min = config.clipNear, float max = config.clipFar)
{
	return ((value - min) / (max - min));
}

struct Point3D
{
	int x, y, z;
	Point3D() {}
	Point3D(int a, int b, int c) { x = a; y = b; z = c; }
	Point3D(int a, int b) { x = a; y = b; }
};

float CrossProductIn2D(Point3D v1, Point3D v2)
{
	return static_cast<float>(v1.x * v2.y) - static_cast<float>(v1.y * v2.x);
}

int orient2d(const Point3D& a, const Point3D& b, const Point3D& c)
{
	return (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x);
}

void DrawInternal::_DrawPolygon(Vector<float, 3> input[3], Vector<unsigned char, 3> color, bool fill_polygon)
{

	if (fill_polygon)
	{
		Point3D point[3];
		for (int i = 0; i < 3; i++)
		{
			point[i].x = input[i][0];
			point[i].y = input[i][1];
			point[i].z = _normalizationToUnity(input[i][2]) * 254;
		}

		// Bounding box
		int minX = fmin(point[0].x, fmin(point[1].x, point[2].x));
		int maxX = fmax(point[0].x, fmax(point[1].x, point[2].x));
		int minY = fmin(point[0].y, fmin(point[1].y, point[2].y));
		int maxY = fmax(point[0].y, fmax(point[1].y, point[2].y));

		Point3D p;

		/* spanning vectors of edge (v1,v2) and (v1,v3) */
		Point3D vs1 = Point3D(point[1].x - point[0].x, point[1].y - point[0].y);
		Point3D vs2 = Point3D(point[2].x - point[0].x, point[2].y - point[0].y);

		for (p.x = minX; p.x <= maxX; p.x++)
		{
			for (p.y = minY; p.y <= maxY; p.y++)
			{
				Point3D q = Point3D(p.x - point[0].x, p.y - point[0].y);

				float s = CrossProductIn2D(q, vs2) / CrossProductIn2D(vs1, vs2);
				float t = CrossProductIn2D(vs1, q) / CrossProductIn2D(vs1, vs2);

				if ((s >= 0) && (t >= 0) && (s + t <= 1))
				{
					unsigned char ZCOLOR = ((1 - s - t)*point[0].z + s*point[1].z + t*point[2].z);
					_PutPixelWithZBuffer(Vector<int, 2>({ p.x,p.y }), color, ZCOLOR);
				}
			}
		}
	}
	else {
		Vector<int, 2> VerticiesIn2D[3];
		VerticiesIn2D[0] = Vector<int, 2>({ (int)input[0][0], (int)input[0][1] });
		VerticiesIn2D[1] = Vector<int, 2>({ (int)input[1][0], (int)input[1][1] });
		VerticiesIn2D[2] = Vector<int, 2>({ (int)input[2][0], (int)input[2][1] });
		if (false)//bersenham
		{
			// Sort VerticiesIn2Dolygons by y
			if (VerticiesIn2D[0][1] > VerticiesIn2D[1][1]) std::swap(VerticiesIn2D[1], VerticiesIn2D[0]);
			if (VerticiesIn2D[0][1] > VerticiesIn2D[2][1]) std::swap(VerticiesIn2D[2], VerticiesIn2D[0]);
			if (VerticiesIn2D[1][1] > VerticiesIn2D[2][1]) std::swap(VerticiesIn2D[1], VerticiesIn2D[2]);

			int TotalHeight = VerticiesIn2D[2][1] - VerticiesIn2D[0][1];

			for (int y = VerticiesIn2D[0][1]; y != VerticiesIn2D[2][1]; y++)
			{
				float CurrentLongx = static_cast<float>((y - VerticiesIn2D[0][1])) / TotalHeight;
				Vector<int, 2> a;
				Vector<int, 2> b;
				if (y < VerticiesIn2D[1][1])
				{
					int SegmentHeight = VerticiesIn2D[1][1] - VerticiesIn2D[0][1];
					if (SegmentHeight == 0) SegmentHeight++;
					float CurrentShortx = static_cast<float>((y - VerticiesIn2D[0][1])) / SegmentHeight;
					a({ VerticiesIn2D[0][0] + static_cast<int>((VerticiesIn2D[1][0] - VerticiesIn2D[0][0]) * CurrentShortx), y });
					b({ VerticiesIn2D[0][0] + static_cast<int>((VerticiesIn2D[2][0] - VerticiesIn2D[0][0]) * CurrentLongx), y });
				}
				else
				{
					int SegmentHeight = VerticiesIn2D[2][1] - VerticiesIn2D[1][1];
					if (SegmentHeight == 0) SegmentHeight++;
					float CurrentShortx = static_cast<float>((y - VerticiesIn2D[1][1])) / SegmentHeight;
					a({ VerticiesIn2D[1][0] + static_cast<int>((VerticiesIn2D[2][0] - VerticiesIn2D[1][0]) * CurrentShortx), y });
					b({ VerticiesIn2D[0][0] + static_cast<int>((VerticiesIn2D[2][0] - VerticiesIn2D[0][0]) * CurrentLongx), y });
				}
				_DrawLine(a, b, color);
			}
		}
		else {
			_DrawLine(VerticiesIn2D[0], VerticiesIn2D[1], Vector<unsigned char, 3>({ 0, 0xff, 0 }));
			_DrawLine(VerticiesIn2D[1], VerticiesIn2D[2], Vector<unsigned char, 3>({ 0, 0xff, 0 }));
			_DrawLine(VerticiesIn2D[2], VerticiesIn2D[0], Vector<unsigned char, 3>({ 0xff, 0, 0 }));
		}
	}
}