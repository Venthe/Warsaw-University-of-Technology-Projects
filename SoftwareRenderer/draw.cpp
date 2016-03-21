#include "config.h"
#include "draw.h"
#include "file_handler.h"

void _PutPixel(Vector2<int> a, Vector3<unsigned char> color, bool markToFill = false);

void _PutPixel(Vector2<int> a, Vector3<unsigned char> color, bool markToFill)
{
	// Out of bounds checking
	if (a[0] < 0 || a[1] < 0) return;
	if (a[0] > settings.bufferSize[0] || a[1] > settings.bufferSize[1]) return;

	int* buffer = static_cast<int*> (settings.backbuffer);

	buffer += (a[1] * settings.bufferSize[0]) + a[0]; // Move to a pixel in a buffer
	// If markToFill is present, mark unused byte to white (Mark as edge of polygon)
	if (markToFill) *buffer = (0xff << 24);
	else *buffer = (color[0] << 16) + (color[1] << 8) + (color[2]);
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

			if(fillMarked)
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
					if(((*window_buffer >> 24) & 0xff) == 0xff) scan_line++;
					if(scan_line>0)
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

void FillPolygon(Vector3<int> p[3], Vector3<unsigned char> color){
	//bounding box
	int BoundingBox[4]; // x,y,maxx,maxy
	BoundingBox[0] = settings.bufferSize[0];
	BoundingBox[1] = settings.bufferSize[1];
	BoundingBox[2] = 0;
	BoundingBox[3] = 0;
	for (int i = 0; i<3; i++)
	{
		if (p[i][0] < BoundingBox[0]) BoundingBox[0] = p[i][0];
		if (p[i][0] > BoundingBox[2]) BoundingBox[2] = p[i][0];

		if (p[i][1] < BoundingBox[1]) BoundingBox[1] = p[i][1];
		if (p[i][1] > BoundingBox[3]) BoundingBox[3] = p[i][1];
	}
	_MyFillRect(
		Vector2<int>(BoundingBox[0], BoundingBox[1]),
		Vector2<int>(BoundingBox[2], BoundingBox[3]),
		color,
		false, true);
}

// Fill a rect with a color
void FillRect(Vector2<int> a, Vector2<int> b, Vector3<unsigned char> color)
{
	_MyFillRect(a, b, color,false,false);
}

void FillRect(bool random)
{
	if (random) _MyFillRect(Vector2<int>(0, 0), Vector2<int>(0, 0), _RandomPixelColor(),true,false);
	else FillRect(); 
}

// Fill whole drawing space with a color
void FillRect(Vector3<unsigned char> color)
{
	_MyFillRect(Vector2<int>(0, 0), Vector2<int>(0, 0), color,true,false);
}

void DrawLine(Vector2<int> a, Vector2<int> b, Vector3<unsigned char> color, bool markToFill)
{
	if (b[1] < a[1]) std::swap(a,b); // Sort by y value

	int delta_x = b[0] - a[0]; //deltax==0 -> vertical
	int delta_y = b[1] - a[1]; //deltay==0 -> horizontal
	if (delta_x == 0 && delta_y == 0) { _PutPixel(a,color,markToFill); }
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
			_PutPixel(pixel, color, markToFill);
		}
		return;
	}

	double delta_error = static_cast<double>(delta_y) / static_cast<double>(delta_x); // real deltaerr : = abs(deltay / deltax)
	if (delta_error < 0.0) delta_error *= -1.0;
	double error = 0.0f;

	int current_y = a[1];

	for (int current_x = a[0]; current_x != b[0];)
	{ 
		_PutPixel(Vector2<int>(current_x, current_y), color, markToFill);
		error += delta_error;
		while (error >= 0.5 && current_y!=b[1])
		{
			_PutPixel(Vector2<int>(current_x, current_y), color, markToFill);
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

void DrawPolygon(Vector3<int> p[3], bool fill_polygon=false)
{
	//TODO: COLORS
	DrawLine(Vector2<int>(p[0][0], p[0][1]), Vector2<int>(p[1][0], p[1][1]), _RandomPixelColor(), fill_polygon); // v1 to v2
	DrawLine(Vector2<int>(p[1][0], p[1][1]), Vector2<int>(p[2][0], p[2][1]), _RandomPixelColor(), fill_polygon); // v2 to v3
	DrawLine(Vector2<int>(p[2][0], p[2][1]), Vector2<int>(p[0][0], p[0][1]), _RandomPixelColor(), fill_polygon); // v3 to v4

	if (fill_polygon) FillPolygon(p, _RandomPixelColor());
}

void DrawObj(ObjModel model, Vector3<double> ShiftOrigin, bool filled_polygons)
{
	//TODO: Round doubles properly
	Vector3<int> CurrentVertex3[3];
	for (unsigned int i = 0; i < model.Face.size(); i++)
	{
		CurrentVertex3[0](
			static_cast<int>(round(model.Origin[0] + ShiftOrigin[0] + model.Vertex.at(model.Face.at(i)[0] - 1)[0] * model.Scale[0]       )),
			static_cast<int>(round(model.Origin[1] + ShiftOrigin[1] + model.Vertex.at(model.Face.at(i)[0] - 1)[1] * model.Scale[1] * -1.0)),
			static_cast<int>(round(model.Origin[2] + ShiftOrigin[2] + model.Vertex.at(model.Face.at(i)[0] - 1)[2] * model.Scale[2]       ))
		);																														      
		CurrentVertex3[1](																										      
			static_cast<int>(round(model.Origin[0] + ShiftOrigin[0] + model.Vertex.at(model.Face.at(i)[1] - 1)[0] * model.Scale[0]       )),
			static_cast<int>(round(model.Origin[1] + ShiftOrigin[1] + model.Vertex.at(model.Face.at(i)[1] - 1)[1] * model.Scale[1] * -1.0)),
			static_cast<int>(round(model.Origin[2] + ShiftOrigin[2] + model.Vertex.at(model.Face.at(i)[1] - 1)[2] * model.Scale[2]       ))
		);																														       
		CurrentVertex3[2](																										       
			static_cast<int>(round(model.Origin[0] + ShiftOrigin[0] + model.Vertex.at(model.Face.at(i)[2] - 1)[0] * model.Scale[0]       )),
			static_cast<int>(round(model.Origin[1] + ShiftOrigin[1] + model.Vertex.at(model.Face.at(i)[2] - 1)[1] * model.Scale[1] * -1.0)),
			static_cast<int>(round(model.Origin[2] + ShiftOrigin[2] + model.Vertex.at(model.Face.at(i)[2] - 1)[2] * model.Scale[2]       ))
		);

		//TODO: Z depth. Temp solution? Draw half of the model
		if (CurrentVertex3[0][2] < 0.0 || CurrentVertex3[1][2] < 0.0 || CurrentVertex3[2][2] < 0.0) continue; 

		if(filled_polygons)	DrawPolygon(CurrentVertex3, true);
		else DrawPolygon(CurrentVertex3, false);
	}
}

//TEST: Test code
void TestDrawCircle(Vector2<int> a, int radius, double step, Vector3<unsigned char> color)
{
	const double pi = 3.14159265358979323846;
	for (double angle = 0.0; angle < 360.0; angle += step) {
		double _Angle = (angle / 360.0) * 2.0 * pi;		
		_PutPixel(Vector2<int>(a[0] + static_cast<int>(radius * sin(_Angle)), a[1] + static_cast<int>(radius * cos(_Angle))), color);
	}
}
void TestDrawFan(Vector2<int> a, int radius, double step,Vector3<unsigned char> color)
{
	const double pi = 3.14159265358979323846;
	for (double angle = 0.0; angle < 360.0; angle += step) {
		double _Angle = (angle / 360.0) * 2.0 * pi;
		DrawLine(a,Vector2<int>(a[0] + static_cast<int>(radius * sin(_Angle)), a[1] + static_cast<int>(radius * cos(_Angle))), color);
	}
}
void TestDrawFilledPolygons()
{
	Vector3<int> p[3];
	p[0](300, 300, 100);
	p[1](10, 30, 100);
	p[2](50, 250, 100);
	DrawPolygon(p,true);
	p[0](200, 10, 100);
	p[1](110, 30, 100);
	p[2](300, 50, 100);
	DrawPolygon(p, true);
	p[0](400, 100, 100);
	p[1](200, 400, 100);
	p[2](400, 70, 100);
	DrawPolygon(p, true);
}