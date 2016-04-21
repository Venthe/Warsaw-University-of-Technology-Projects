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
	// Sort Polygons by Y
	if (p[0][1] > p[1][1]) std::swap(p[1], p[0]);
	if (p[0][1] > p[2][1]) std::swap(p[2], p[0]);
	if (p[1][1] > p[2][1]) std::swap(p[1], p[2]);

	int TotalHeight = p[2][1] - p[0][1];

	for (int y = p[0][1]; y != p[2][1]; y++)
	{
		float CurrentLongX = static_cast<float>((y - p[0][1])) / TotalHeight;
		Vector2<int> a;
		Vector2<int> b;
		if (y < p[1][1])
		{
			int SegmentHeight = p[1][1] - p[0][1];
			if (SegmentHeight == 0) SegmentHeight++;
			float CurrentShortX = static_cast<float>((y - p[0][1])) / SegmentHeight;
			a(p[0][0] + static_cast<int>((p[1][0] - p[0][0]) * CurrentShortX), y);
			b(p[0][0] + static_cast<int>((p[2][0] - p[0][0]) * CurrentLongX), y);
		}
		else
		{
			int SegmentHeight = p[2][1] - p[1][1];
			if (SegmentHeight == 0) SegmentHeight++;
			float CurrentShortX = static_cast<float>((y - p[1][1])) / SegmentHeight;
			a(p[1][0] + static_cast<int>((p[2][0] - p[1][0]) * CurrentShortX), y);
			b(p[0][0] + static_cast<int>((p[2][0] - p[0][0]) * CurrentLongX), y);
		}
		DrawLine(a, b, color);
	}
}

void Projection(double c) {
	std::array<double,16> t = IdentityMatrix<double, 4>();
	t[14] = c;
	config.Projection = t;
}

void LookAt(Vector3<double> lookat, Vector3<double> up, Vector3<double> cameraOrigin)
{
	Vector3<double> z = (cameraOrigin - lookat).Normalize();
	Vector3<double> x = CrossProduct(up, z).Normalize();
	Vector3<double> y = CrossProduct(z, x).Normalize();
	auto Minv = IdentityMatrix<double,4>();
	auto Tr = IdentityMatrix<double, 4>();
	for (int i = 0; i<3; i++) {
		Minv[0*4 + i] = x[i];
		Minv[1*4 + i] = y[i];
		Minv[2*4 + i] = z[i];
		Tr[i*4 + 3] = -lookat[i];
	}
	config.ModelView = ArrayMultiplication(Minv,Tr);
}
void Viewport(int x, int y, int w, int h) {
	config.Viewport = IdentityMatrix<double, 4>();
	config.Viewport[0 * 4 + 3] = x + w / 2.f;
	config.Viewport[1 * 4 + 3] = y + h / 2.f;
	config.Viewport[2 * 4 + 3] = 1.f;

	config.Viewport[0 * 4 + 0] = w / 2.f;
	config.Viewport[1 * 4 + 1] = h / 2.f;
	config.Viewport[2 * 4 + 2] = 0;
}

void DrawModel(Model model, bool fill_polygon)
{
	// Viewport * Projection * ModelView * v.
	config.TransformationMatrix = IdentityMatrix<double,4>();
	config.TransformationMatrix = ArrayMultiplication(config.TransformationMatrix, config.Viewport);
	config.TransformationMatrix = ArrayMultiplication(config.TransformationMatrix, config.Projection);
	config.TransformationMatrix = ArrayMultiplication(config.TransformationMatrix, config.ModelView);
	
	Vector3<double> current_vertex[3];
	for (unsigned int i = 0; i < model.Face.size(); i++)
	{
		for (int j = 0; j<3; j++) current_vertex[j](model.Vertex.at(model.Face.at(i)[j] - 1)[0], model.Vertex.at(model.Face.at(i)[j] - 1)[1], model.Vertex.at(model.Face.at(i)[j] - 1)[2]);

		//View with perspective
		for(int j = 0; j<3;j++){
			transformVectorByArray(config.TransformationMatrix, current_vertex[j],true);
		}

		//Scale the model and move it by it's origin point with respect to scene
		Vector3<int> pixel_vertex[3];
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++) pixel_vertex[j][k] = static_cast<int>(model.Origin[k] + current_vertex[j][k]*model.Scale[k]);//
		}

		// TODO: SHADING
		Vector3<unsigned char> color;
		color = Vector3<unsigned char>(0, 0, 0);
		//color = _RandomPixelColor(); // Temp Random color

		// TODO: SquashDimensions
		Vector2<int> triangle[3];
		for (int j=0;j<3;j++) triangle[j] = Vector2<int>(pixel_vertex[j][0]+350 , pixel_vertex[j][1]+500);
		
		DrawPolygon(triangle, color, fill_polygon);
	}
}