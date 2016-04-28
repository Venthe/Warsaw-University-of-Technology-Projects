#include <array>
#include "mymath.h"
#include "config.h"
#include "draw.h"
#include "object_handler.h"

void _PutPixel(Vector2<int> a, Vector3<unsigned char> color)
{
	// Out of bounds checking
	if (a[0] < 0 || a[1] < 0) return;
	if (a[0] >= config.bufferSize[0] || a[1] >= config.bufferSize[1]) return;

	int* buffer = static_cast<int*> (config.backbuffer);

	buffer += (a[1] * config.bufferSize[0]) + (a[0]);
	*buffer = (color[0] << 16) + (color[1] << 8) + (color[2]);
}

Vector3<unsigned char> _RandomPixelColor()
{
	return Vector3<unsigned char>(rand() % 0xff, rand() % 0xFF, rand() % 0xFF);
}

void _MyFillRect(Vector2<int> a, Vector2<int> b, Vector3<unsigned char> color, bool full_size, bool fillMarked)
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
	if (random) _MyFillRect(Vector2<int>(0, 0), Vector2<int>(0, 0), _RandomPixelColor(), true, false);
	else FillRect();
}

void FillRect(Vector2<int> a, Vector2<int> b, Vector3<unsigned char> color) { _MyFillRect(a, b, color, false, false); } // Fill a rect with a color
void FillRect(Vector3<unsigned char> color) { _MyFillRect(Vector2<int>(0, 0), Vector2<int>(0, 0), color, true, false); } // Fill whole drawing space with a color

void DrawLine(Vector2<int> a, Vector2<int> b, Vector3<unsigned char> color)
{
	if (b[1] < a[1]) std::swap(a, b); // Sort by y value

	int delta_x = b[0] - a[0]; //deltax==0 -> vertical
	int delta_y = b[1] - a[1]; //deltay==0 -> horizontal
	if (delta_x == 0 && delta_y == 0) { _PutPixel(a, color); }
	else if (delta_x == 0 || delta_y == 0)
	{
		int current_value;
		int target_value;
		int constant;
		if (delta_x == 0) { current_value = a[1]; target_value = b[1]; constant = a[0]; }
		else { current_value = a[0]; target_value = b[0]; constant = a[1]; }
		if (current_value > target_value) std::swap(current_value, target_value);
		Vector2<int> pixel;

		for (; current_value < target_value; current_value++)
		{
			if (delta_x == 0) pixel(constant, current_value);
			else pixel(current_value, constant);
			pixel(pixel[0] - 1, pixel[1] - 1);
			_PutPixel(pixel, color);
		}
		return;
	}

	double delta_error = static_cast<double>(delta_y) / static_cast<double>(delta_x); // real deltaerr : = abs(deltay / deltax)
	if (delta_error < 0.0) delta_error *= -1.0;
	double error = 0.0f;

	int current_y = a[1];

	for (int current_x = a[0]; current_x != b[0];)
	{
		_PutPixel(Vector2<int>(current_x, current_y), color);
		error += delta_error;
		while (error >= 0.5 && current_y != b[1])
		{
			_PutPixel(Vector2<int>(current_x, current_y), color);
			current_y++;
			error -= 1.0;
		}
		if (delta_x > 0) current_x++;
		else current_x--;
	}
}

void DrawGrid(int density, Vector3<unsigned char> color)
{
	for (int i = 0; i < ((config.bufferSize[0]) / density) + 1; i++)
	{
		DrawLine(Vector2<int>(i * density, 0), Vector2<int>(i * density, config.bufferSize[1]), color);
		DrawLine(Vector2<int>(0, i * density), Vector2<int>(config.bufferSize[0], i * density), color);
	}
}

void DrawPolygon(Vector2<int> p[3], Vector3<unsigned char> color, bool fill_polygon)
{
	//TODO: COLORS
	if (!fill_polygon) {
		DrawLine(p[0], p[1], Vector3<unsigned char>(0, 0xff, 0));
		DrawLine(p[1], p[2], Vector3<unsigned char>(0, 0xff, 0));
		DrawLine(p[2], p[0], Vector3<unsigned char>(0xff, 0, 0));
		return;
	}
	// Sort Polygons by y
	if (p[0][1] > p[1][1]) std::swap(p[1], p[0]);
	if (p[0][1] > p[2][1]) std::swap(p[2], p[0]);
	if (p[1][1] > p[2][1]) std::swap(p[1], p[2]);

	int TotalHeight = p[2][1] - p[0][1];

	for (int y = p[0][1]; y != p[2][1]; y++)
	{
		float CurrentLongx = static_cast<float>((y - p[0][1])) / TotalHeight;
		Vector2<int> a;
		Vector2<int> b;
		if (y < p[1][1])
		{
			int SegmentHeight = p[1][1] - p[0][1];
			if (SegmentHeight == 0) SegmentHeight++;
			float CurrentShortx = static_cast<float>((y - p[0][1])) / SegmentHeight;
			a(p[0][0] + static_cast<int>((p[1][0] - p[0][0]) * CurrentShortx), y);
			b(p[0][0] + static_cast<int>((p[2][0] - p[0][0]) * CurrentLongx), y);
		}
		else
		{
			int SegmentHeight = p[2][1] - p[1][1];
			if (SegmentHeight == 0) SegmentHeight++;
			float CurrentShortx = static_cast<float>((y - p[1][1])) / SegmentHeight;
			a(p[1][0] + static_cast<int>((p[2][0] - p[1][0]) * CurrentShortx), y);
			b(p[0][0] + static_cast<int>((p[2][0] - p[0][0]) * CurrentLongx), y);
		}
		DrawLine(a, b, color);
	}
}

void Projection(double fov, double aspectW, double aspectH, double clippingNear, double clippingFar)
{
	config.ProjectionMatrix = MyMath::IdentityMatrix<double, 16>();
	double aspectRatio = aspectW / aspectH;

	double yScale = 1.0 / tan(MyMath::DegreesToRadians(fov) / 2);
	double xScale = yScale / aspectRatio;
	double clippingDistance = clippingNear - clippingFar;

	config.ProjectionMatrix[0] = xScale;
	config.ProjectionMatrix[5] = yScale;
	config.ProjectionMatrix[10] = (clippingFar + clippingNear) / clippingDistance;
	config.ProjectionMatrix[11] = -1;
	config.ProjectionMatrix[14] = (2 * clippingFar * clippingNear) / clippingDistance;
}

void LookAt(Vector3<double> lookat, Vector3<double> up, Vector3<double> cameraOrigin)
{
	config.ViewMatrix = MyMath::IdentityMatrix<double, 16>();

	auto z = (cameraOrigin - lookat).Normalize();
	auto x = CrossProduct(up, z).Normalize();
	auto y = CrossProduct(z, x).Normalize();
	auto M = MyMath::IdentityMatrix<double, 16>();
	auto T = MyMath::IdentityMatrix<double, 16>();
	for (int i = 0; i<3; i++) {
		M[0*4+i] = x[i];
		M[1*4+i] = y[i];
		M[2*4+i] = z[i];
		T[i*4+3] = -lookat[i];
	}

	config.ViewMatrix = MyMath::ArrayMultiplication(M, T);
	config.ViewMatrix = MyMath::ArrayMultiplication(config.ViewMatrix, MyMath::TranslateMatrix<double, 16>((-1.)*config.camera.Origin));
}

void LookAtNothing(Vector3<double>, Vector3<double>)
{
	config.ViewMatrix = MyMath::IdentityMatrix<double, 16>();

	config.ViewMatrix = MyMath::ArrayMultiplication(config.ViewMatrix, MyMath::RotateMatrix<double, 16>(config.camera.Rotation));
	config.camera.Origin[0] *= -1.;
	config.ViewMatrix = MyMath::ArrayMultiplication(config.ViewMatrix, MyMath::TranslateMatrix<double, 16>(config.camera.Origin));
	config.camera.Origin[0] *= -1.;
}

void Viewport(int x, int y, int w, int h) {
	config.ViewportMatrix = MyMath::IdentityMatrix<double, 16>();
	//config.ViewportMatrix.fill(0);
	double depth = 256.;
	config.ViewportMatrix[0 * 4 + 3] = x + w / 2.;
	config.ViewportMatrix[1 * 4 + 3] = y + h / 2.;
	if(!config.Perspective) config.ViewportMatrix[2 * 4 + 3] = depth / 2.;
	else config.ViewportMatrix[2 * 4 + 3] = 1;

	config.ViewportMatrix[0 * 4 + 0] = w / 2.f;
	config.ViewportMatrix[1 * 4 + 1] = h / 2.f;
	if (!config.Perspective) config.ViewportMatrix[2 * 4 + 3] = depth / 2.;
	else config.ViewportMatrix[2 * 4 + 3] = 0;
}

void DrawModel(Model model, bool fill_polygon)
{
	Vector3<double> current_vertex[3];
	int doNotDraw = 0;
	Vector2<int> triangle[3];

	for (unsigned int i = 0; i < model.Face.size(); i++, doNotDraw = 0)
	{
		for (int j = 0; j<3; j++) current_vertex[j](model.Vertex.at(model.Face.at(i)[j] - 1)[0], model.Vertex.at(model.Face.at(i)[j] - 1)[1], model.Vertex.at(model.Face.at(i)[j] - 1)[2]);

		//View with perspective
		for(int j = 0; j<3;j++){
			MyMath::transformVectorByArray(model.GetModelMatrix(), current_vertex[j]);
			MyMath::transformVectorByArray(config.ViewMatrix, current_vertex[j]);
			if (config.Perspective)
				if (MyMath::transformVectorByArray(config.ProjectionMatrix, current_vertex[j], true) == 1) doNotDraw++;
			MyMath::transformVectorByArray(config.ViewportMatrix, current_vertex[j]);

		}

		if (doNotDraw == 3 && config.Perspective) continue;

		doNotDraw = 0;
		for (int j = 0; j < 3; j++)
		{
			if (current_vertex[j][2] < config.camera.Origin[2]) doNotDraw++;
			triangle[j] = Vector2<int>(static_cast<int>(current_vertex[j][0]), static_cast<int>(current_vertex[j][1]));
		}

		if (doNotDraw == 3 && config.Perspective) continue;
		DrawPolygon(triangle, Vector3<unsigned char>(), fill_polygon);
	}
}