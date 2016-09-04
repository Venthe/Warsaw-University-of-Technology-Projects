#include "draw_internal.h"
#include "config.h"

void DrawInternal::_PutPixel(Vector<int, 2> a, Vector<unsigned char, 3> color)
{
	// Out of bounds checking
	if (a[0] < 0 || a[1] < 0) return;
	if (a[0] >= config.bufferSize[0] || a[1] >= config.bufferSize[1]) return;

	int* buffer = static_cast<int*>(config.backbuffer);

	buffer += (a[1] * config.bufferSize[0]) + (a[0]);
	*buffer = (color[0] << 16) + (color[1] << 8) + (color[2]);
}

void DrawInternal::_PutPixelWithZBuffer(Vector<int, 2> a, Vector<unsigned char, 3> color, float zValue)
{
	// Out of bounds checking
	if (a[0] < 0 || a[1] < 0) return;
	if (a[0] >= config.bufferSize[0] || a[1] >= config.bufferSize[1]) return;

	float* zbuffer = static_cast<float*>(config.zbackbuffer);
	zbuffer += (a[1] * config.bufferSize[0]) + (a[0]);
	if (*zbuffer != 0 && *zbuffer < zValue) return;
	*zbuffer = zValue;

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

void DrawInternal::_DrawPolygon(Vector<float, 3> input[3], Vector<unsigned char, 3> color, int drawMode)
{

	if (drawMode != 1)
	{
		Point3D point[3];
		for (int i = 0; i < 3; i++)
		{
			point[i].x = static_cast<int>(input[i][0]);
			point[i].y = static_cast<int>(input[i][1]);
			point[i].z = static_cast<int>(input[i][2]);
		}

		// Bounding box
		int minX = static_cast<int>(fmin(point[0].x, fmin(point[1].x, point[2].x)));
		int maxX = static_cast<int>(fmax(point[0].x, fmax(point[1].x, point[2].x)));
		int minY = static_cast<int>(fmin(point[0].y, fmin(point[1].y, point[2].y)));
		int maxY = static_cast<int>(fmax(point[0].y, fmax(point[1].y, point[2].y)));

		Point3D p;

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
					float zValue = (1 - s - t)*input[0][2] + s*input[1][2] + t*input[2][2];
					_PutPixelWithZBuffer(Vector<int, 2>({ p.x,p.y }), color, zValue);
				}
			}
		}
	}
	else {
		Vector<int, 2> VerticiesIn2D[3];
		VerticiesIn2D[0] = Vector<int, 2>({ (int)input[0][0], (int)input[0][1] });
		VerticiesIn2D[1] = Vector<int, 2>({ (int)input[1][0], (int)input[1][1] });
		VerticiesIn2D[2] = Vector<int, 2>({ (int)input[2][0], (int)input[2][1] });

		_DrawLine(VerticiesIn2D[0], VerticiesIn2D[1], Vector<unsigned char, 3>({ 0, 0xff, 0 }));
		_DrawLine(VerticiesIn2D[1], VerticiesIn2D[2], Vector<unsigned char, 3>({ 0, 0xff, 0 }));
		_DrawLine(VerticiesIn2D[2], VerticiesIn2D[0], Vector<unsigned char, 3>({ 0xff, 0, 0 }));
	}
}