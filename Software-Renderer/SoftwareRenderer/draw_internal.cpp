#include "draw_internal.h"
#include "types.h"
#include "config.h"

namespace DrawInternal
{
	void drawPolygons(Facef input, const Color& color);
	void drawWireframe(Facef input);
	void PutPixel(Vector2i a, Vector3uc color);
	void PutPixelWithZValue(Vector2i a, Vector3uc color, float zValue);
}

void DrawInternal::DrawPolygon(Facef input, Color color, int drawMode)
{
	switch (drawMode)
	{
	case 0:
		drawPolygons(input, color);
		break;
	default:
		drawWireframe(input);
	}
}

void DrawInternal::drawPolygons(Facef input, const Color& color)
{
	Point2i::Structure point[3];
	for (int i = 0; i < 3; i++)
	{
		point[i].x = int(input[i][0]);
		point[i].y = int(input[i][1]);
	}

	// Bounding box
	int minX = int(fmin(point[0].x, fmin(point[1].x, point[2].x)));
	int maxX = int(fmax(point[0].x, fmax(point[1].x, point[2].x)));
	int minY = int(fmin(point[0].y, fmin(point[1].y, point[2].y)));
	int maxY = int(fmax(point[0].y, fmax(point[1].y, point[2].y)));

	Point2i::Structure p;

	Point2i::Structure vs1 = Point2i::Structure(point[1].x - point[0].x, point[1].y - point[0].y);
	Point2i::Structure vs2 = Point2i::Structure(point[2].x - point[0].x, point[2].y - point[0].y);

	for (p.x = minX; p.x <= maxX; p.x++)
	{
		for (p.y = minY; p.y <= maxY; p.y++)
		{
			Point2i::Structure q = Point2i::Structure(p.x - point[0].x, p.y - point[0].y);

			float s = Point2i::CrossProduct(q, vs2) / Point2i::CrossProduct(vs1, vs2);
			float t = Point2i::CrossProduct(vs1, q) / Point2i::CrossProduct(vs1, vs2);

			if ((s >= 0) && (t >= 0) && (s + t <= 1))
			{
				float zValue = (1 - s - t) * input[0][2] + s * input[1][2] + t * input[2][2];
				PutPixelWithZValue(Vector2i({p.x,p.y}), color, zValue);
			}
		}
	}
}

void DrawInternal::drawWireframe(Facef input)
{
	Vector2i VerticiesIn2D[3];
	VerticiesIn2D[0] = Vector2i({int(input[0][0]), int(input[0][1])});
	VerticiesIn2D[1] = Vector2i({int(input[1][0]), int(input[1][1])});
	VerticiesIn2D[2] = Vector2i({int(input[2][0]), int(input[2][1])});

	DrawLine(VerticiesIn2D[0], VerticiesIn2D[1], Color({0, 0xff, 0}));
	DrawLine(VerticiesIn2D[1], VerticiesIn2D[2], Color({0, 0xff, 0}));
	DrawLine(VerticiesIn2D[2], VerticiesIn2D[0], Color({0xff, 0, 0}));
}

void DrawInternal::PutPixel(Vector2i a, Vector3uc color)
{
	// Out of bounds checking
	if (a[0] < 0 || a[1] < 0) return;
	if (a[0] >= config.bufferSize[0] || a[1] >= config.bufferSize[1]) return;

	int* buffer = static_cast<int*>(config.backbuffer);

	buffer += (a[1] * config.bufferSize[0]) + (a[0]);
	*buffer = (color[0] << 16) + (color[1] << 8) + (color[2]);
}

void DrawInternal::PutPixelWithZValue(Vector2i a, Color color, float zValue)
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

void DrawInternal::DrawLine(Vector2i a, Vector2i b, Color color)
{
	if (b[1] < a[1]) std::swap(a, b); // Sort by y value

	int delta_x = b[0] - a[0]; //deltax==0 -> vertical
	int delta_y = b[1] - a[1]; //deltay==0 -> horizontal
	if (delta_x == 0 && delta_y == 0)
	{
		PutPixel(a, color);
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
		Vector2i pixel;

		for (; current_value < target_value; current_value++)
		{
			if (delta_x == 0) pixel({constant, current_value});
			else pixel({current_value, constant});
			pixel({pixel[0] - 1, pixel[1] - 1});
			PutPixel(pixel, color);
		}
		return;
	}

	float delta_error = float(delta_y) / float(delta_x); // real deltaerr : = abs(deltay / deltax)
	if (delta_error < 0.0) delta_error *= -1.0;
	float error = 0.0f;

	int current_y = a[1];

	for (int current_x = a[0]; current_x != b[0];)
	{
		PutPixel(Vector2i({current_x, current_y}), color);
		error += delta_error;
		while (error >= 0.5 && current_y != b[1])
		{
			PutPixel(Vector2i({current_x, current_y}), color);
			current_y++;
			error -= 1.0;
		}
		if (delta_x > 0) current_x++;
		else current_x--;
	}
}
