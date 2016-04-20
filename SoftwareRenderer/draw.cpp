#include <array>
#include "config.h"
#include "draw.h"
#include "object_handler.h"

void _PutPixel(Vector2<int> a, Vector3<unsigned char> color)
{
	// Out of bounds checking
	if (a[0] < 0 || a[1] < 0) return;
	if (a[0] > settings.bufferSize[0] || a[1] > settings.bufferSize[1]) return;

	int* buffer = static_cast<int*> (settings.backbuffer);

	buffer += (a[1] * settings.bufferSize[0]) + a[0]; // Move to a pixel in a buffer
	// If markToFill is present, mark unused byte to white (Mark as edge of polygon)
	*buffer = (color[0] << 16) + (color[1] << 8) + (color[2]);
}

Vector3<unsigned char> _RandomPixelColor()
{
	return Vector3<unsigned char>(rand() % 0xff, rand() % 0xFF, rand() % 0xFF);
}

void _MyFillRect(Vector2<int> a, Vector2<int> b, Vector3<unsigned char> color, bool full_size, bool fillMarked)
{
	int* window_buffer = static_cast<int*>(settings.backbuffer);

	// Sort corners.
	if (a[0] > b[0]) std::swap(a[0], b[0]);
	if (a[1] > b[1]) std::swap(a[1], b[1]);

	// If full_size, mark whole area as drawable
	if (full_size)
	{
		a[0] = 0;
		a[1] = 0;
		b[0] = settings.bufferSize[0];
		b[1] = settings.bufferSize[1];
	}

	int delta_x = b[0] - a[0]; // Specify shift to next line
	window_buffer += (settings.bufferSize[0] * a[1]) + a[0]; // move to initial x,y point

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
		if (!full_size) window_buffer += settings.bufferSize[0] - delta_x;
	}
}

// Fill a rect with a color
void FillRect(Vector2<int> a, Vector2<int> b, Vector3<unsigned char> color)
{
	_MyFillRect(a, b, color, false, false);
}

void FillRect(bool random)
{
	if (random) _MyFillRect(Vector2<int>(0, 0), Vector2<int>(0, 0), _RandomPixelColor(), true, false);
	else FillRect();
}

// Fill whole drawing space with a color
void FillRect(Vector3<unsigned char> color)
{
	_MyFillRect(Vector2<int>(0, 0), Vector2<int>(0, 0), color, true, false);
}

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

		for (; current_value <= target_value; current_value++)
		{
			if (delta_x == 0) pixel(constant, current_value);
			else pixel(current_value, constant);
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
	for (int i = 0; i < ((settings.bufferSize[0]) / density) + 1; i++)
	{
		DrawLine(Vector2<int>(i * density, 0), Vector2<int>(i * density, settings.bufferSize[1]), color);
		DrawLine(Vector2<int>(0, i * density), Vector2<int>(settings.bufferSize[0], i * density), color);
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

void transform(Vector3<double>& v, double t[16])
{
	double result[4] = {
		v[0] * t[0 ] + v[1] * t[1 ] + v[2] * t[2 ] + 1 * t[3 ] ,
		v[0] * t[4 ] + v[1] * t[5 ] + v[2] * t[6 ] + 1 * t[7 ] ,
		v[0] * t[8 ] + v[1] * t[9 ] + v[2] * t[10] + 1 * t[11],
		v[0] * t[12] + v[1] * t[13] + v[2] * t[14] + 1 * t[15]
	};

	//retro-projection
	v[0] = result[0] / result[3];
	v[1] = result[1] / result[3];
	v[2] = result[2] / result[3];

}

double test_value = -1.0;
//void transform_homogenous_aroundPoint(Vector2<double>& v, double transformation[4])
//{
//	v[0] = (transformation[0] * v[0]) + (transformation[1] * v[1]);
//	v[1] = (transformation[2] * v[0]) + (transformation[3] * v[1]);
//}
//void test_transform_vertex(Vector3<double>& v)
//{
//	//Test matrices
//	//rotation
//	double angle = (test_value)*(3.14159/180.0);
//	double rotation[4] = {std::cos(angle),std::sin(angle)*(-1.0),std::sin(angle),std::cos(angle) };
//	//skew
//	double skewX = 0.0;
//	double skewY = 0.0;
//	double skew[4] = { 1,test_value,skewY,1 };
//	//scale
//
//	//skew
//	double scaleX = 0.1;
//	double scaleY = 1.0;
//	double scale[4] = { test_value,0,0,scaleY };
//
//	Vector2<double> squash(v[0], v[1]);
//
//	transform(squash, scale);
//
//	v[0] = squash[0];
//	v[1] = squash[1];
//}

std::array<double,9> calculateRotationMatrix(Camera camera)
{
	std::array<double, 9> rotationMatrix;

	double rTemp[9];
	double rx[9] = {
		1,0,0,
		0,std::cos(camera.Rotation[0]),-std::sin(camera.Rotation[0]),
		0,std::sin(camera.Rotation[0]),std::cos(camera.Rotation[0])
	};
	double ry[9] = {
		std::cos(camera.Rotation[1]),0,std::sin(camera.Rotation[1]),
		0,1,0,
		-std::sin(camera.Rotation[1]),0,std::cos(camera.Rotation[1])
	};
	double rz[9] = {
		std::cos(camera.Rotation[2]),-std::sin(camera.Rotation[2]),0,
		std::sin(camera.Rotation[2]),std::cos(camera.Rotation[2]),0,
		0,0,1
	};
	for(int r = 0; r<3;r++)
	{
		for(int c=0;c<3;c++)
		{
			for(int inner = 0; inner<3;inner++)
			{
				rTemp[(r * 3) + c] += rx[(r*3) + inner] * ry[c+(inner*3)];
				rotationMatrix[(r * 3) + c] += rTemp[(r * 3) + inner] * rz[c + (inner * 3)];
			}
		}
	}


	return rotationMatrix;
}

void DrawModel(Model model, Camera camera, bool filled_polygons)
{
	if (test_value > 0.0) test_value = -1.0;
	else test_value += 0.1;
	//TODO: Round doubles properly
	Vector3<double> current_vertex[3];
	for (unsigned int i = 0; i < model.Face.size(); i++)
	{
		current_vertex[0](model.Vertex.at(model.Face.at(i)[0] - 1)[0], model.Vertex.at(model.Face.at(i)[0] - 1)[1], model.Vertex.at(model.Face.at(i)[0] - 1)[2]);
		current_vertex[1](model.Vertex.at(model.Face.at(i)[1] - 1)[0], model.Vertex.at(model.Face.at(i)[1] - 1)[1], model.Vertex.at(model.Face.at(i)[1] - 1)[2]);
		current_vertex[2](model.Vertex.at(model.Face.at(i)[2] - 1)[0], model.Vertex.at(model.Face.at(i)[2] - 1)[1], model.Vertex.at(model.Face.at(i)[2] - 1)[2]);
		

		//View in camera
		for(int j = 0; j<3;j++){
			//double angle = 0.0 * (3.14159 / 180.0);
			//computeRotatedVert(current;

			std::array<double, 9> rotational_matrix = calculateRotationMatrix(camera);

			



			double t[16] = {
				1,0,0,camera.Origin[0], /* 1 skewX perspective or rotX ShiftX */
				0,1,0,camera.Origin[1], /* SkewY 1 Perspective or rotZ ShiftY */
				0,0,1,camera.Origin[2], /* 0 0 1 ShiftZ */
				0,0,camera.FocalLength,1  /* 0 0 0 1 */
			};
			transform(current_vertex[j], t);
		}

		Vector3<int> pixel_vertex[3];
		for (int j = 0; j < 3; j++)
		{
			pixel_vertex[j][0] = static_cast<int>(model.Origin[0] + current_vertex[j][0] * model.Scale[0]);
			pixel_vertex[j][1] = static_cast<int>(model.Origin[1] + current_vertex[j][1] * model.Scale[1]);
			pixel_vertex[j][2] = static_cast<int>(model.Origin[2] + current_vertex[j][2] * model.Scale[2]);
		}

		//TODO: Z depth.
		if (current_vertex[0][2] < 0.0 || current_vertex[1][2] < 0.0 || current_vertex[2][2] < 0.0) continue; // Temp Draw half of the model

		// TODO: SHADING
		//Vector3<unsigned char> color = _RandomPixelColor(); // Temp Random color

		// TODO: SquashDimensions
		Vector2<int> triangle[3];
		triangle[0] = Vector2<int>(pixel_vertex[0][0], pixel_vertex[0][1]);
		triangle[1] = Vector2<int>(pixel_vertex[1][0], pixel_vertex[1][1]);
		triangle[2] = Vector2<int>(pixel_vertex[2][0], pixel_vertex[2][1]);
		
		DrawPolygon(triangle, Vector3<unsigned char>(0, 0, 0), filled_polygons);
	}
}