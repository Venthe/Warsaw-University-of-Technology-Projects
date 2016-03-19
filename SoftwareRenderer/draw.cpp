#include "config.h"
#include "draw.h"
#include "file_handler.h"

void _PutPixel(Vector2<int> a, Vector3<unsigned char> color)
{
	// Out of bounds checking
	if (a[0] < 0 || a[1] < 0)
		return;
	if (a[0] > settings.bufferSize[0] || a[1] > settings.bufferSize[1])
		return;

	int* buffer = static_cast<int*> (settings.backbuffer);
	buffer += (a[1] * settings.bufferSize[0]) + a[0]; // Move to pixel
	*buffer = (color[0] << 16) + (color[1] << 8) + (color[2]);
}

int _RandomPixelColor()
{
	return (rand() % 0xFF << 16) + (rand() % 0xFF << 8) + rand() % 0xFF;
}

void _MyFillRect(Vector2<int> a, Vector2<int> b, Vector3<unsigned char> color, bool random, bool fullsize)
{
	// Bounds checking
	if (a[0] < 0 || a[1] < 0 || b[0] < 0 || b[1] < 0) return; 
	if (a[0] > settings.bufferSize[0] || a[1] > settings.bufferSize[1] || b[0] > settings.bufferSize[0] || b[1] > settings.bufferSize[1]) return; 

	if ((a[0] == b[0] && a[1] == b[1]) && !fullsize)
	{
		_PutPixel(Vector2<int>(a[0], a[1]), color);
		return;
	}

	int* windowbuffer = static_cast<int*>( settings.backbuffer);
	if (fullsize)
	{
		for (int height = 0; height < settings.bufferSize[0]; height++)
		{ // Height
			for (int width = 0; width < settings.bufferSize[1]; width++)
			{ // Width
				if (random) *windowbuffer++ = _RandomPixelColor();
				else *windowbuffer++ = (color[0] << 16) + (color[1] << 8) + color[2];
			}
		}
	}
	else
	{
		// move to initial x,y point
		int deltaX = a[0] - b[0];
		if (deltaX < 0) deltaX *= -1; 
		windowbuffer += (settings.bufferSize[0] * a[1]) + a[0];
		for (int height = a[1]; height < b[1]; height++)
		{ // Height
			for (int width = a[0]; width < b[1]; width++) *windowbuffer++ = (color[0] << 16) + (color[1] << 8) + color[2]; 
			windowbuffer += settings.bufferSize[0] - deltaX;
		}
	}
}

void FillRect(Vector2<int> a, Vector2<int> b, Vector3<unsigned char> color)
{
	_MyFillRect(a, b, color, false, false);
}

void FillRect(bool random)
{
	if (random) _MyFillRect(Vector2<int>(0, 0), Vector2<int>(0, 0), Vector3<unsigned char>(0, 0, 0), true, true); 
	else  FillRect(); 
}

void FillRect(Vector3<unsigned char> color)
{
	_MyFillRect(Vector2<int>(0, 0), Vector2<int>(0, 0), color, false, true);
}

void DrawLine(Vector2<int> a, Vector2<int> b, Vector3<unsigned char> color)
{
	// Bounds checking
	//TODO: Might not be needed as for now. _PutPixel should handle it.
	if (a[0] < 0 || a[1] < 0 || b[0] < 0 || b[1] < 0)
	{
		return;
	}
	if (a[0] > settings.bufferSize[0] || a[1] > settings.bufferSize[1] || b[0] > settings.bufferSize[0] || b[1] > settings.bufferSize[1])
		return;

	// This precious little bit of optimization
	if (a[0] == b[0] && a[1] == b[1])
	{
		_PutPixel(a, color);
		return;
	}

	int deltax = b[0] - a[0]; //deltax==0 -> vertical
	if (deltax == 0)
	{
		for (int cury = a[1]; cury != b[1];)
		{
			_PutPixel(Vector2<int>(a[0], cury), color);
			if (cury < b[1]) cury++;
			else cury--;
		}
		return;
	}

	int deltay = b[1] - a[1]; //deltay==0 -> horizontal
	if (deltay == 0)
	{
		for (int curx = a[0]; curx != b[0];)
		{
			_PutPixel(Vector2<int>(curx, b[1]), color);
			if (curx < b[0]) curx++;
			else curx--;
		}
		return;
	}

	double error = 0.0f; //	real error : = 0
	double deltaerr = static_cast<double>(deltay) / static_cast<double>(deltax); //	real deltaerr : = abs(deltay / deltax)
	if (deltaerr < 0.0) deltaerr *= -1.0;

	int cury = a[1]; //	int a[1] : = y0

	for (int curx = a[0]; curx != b[0];)
	{ // for x from x0 to x1
		_PutPixel(Vector2<int>(curx, cury), color); // plot(a[0], y)
		error += deltaerr; // error : = error + deltaerr
		while (error >= 0.5 && cury != b[1])
		{ // while error ≥ 0.5 then
			_PutPixel(Vector2<int>(curx, cury), color); // plot(a[0], y)
			if (deltay > 0) cury++; 
			else cury--; 
			error -= 1.0; // error := error - 1.0
		}
		if (deltax > 0) curx++; 
		else curx--; 
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

void DrawPolygon(Vector3<int> a, Vector3<int> b, Vector3<int> c, Vector3<unsigned char> color)
{
	//Sort by Y
	if (a[1] > b[1]) std::swap(a, b);
	if (a[1] > c[1]) std::swap(a, c);
	if (b[1] > c[1]) std::swap(b, c);
	//TODO: Fix colors. Debug values.
	DrawLine(Vector2<int>(a[0], a[1]), Vector2<int>(b[0], b[1]), Vector3<unsigned char>(0, 0xff, 0)); // v1 to v2
	DrawLine(Vector2<int>(b[0], b[1]), Vector2<int>(c[0], c[1]), Vector3<unsigned char>(0, 0xff, 0)); // v2 to v3
	DrawLine(Vector2<int>(c[0], c[1]), Vector2<int>(a[0], a[1]), Vector3<unsigned char>(0xFF, 0, 0)); // v3 to v4

	//TODO: Fill the poly
}

void DrawObj(ObjModel model, Vector3<double> ShiftOrigin)
{
	Vector3<int> CurrentVertex3[3];
	for (unsigned int i = 0; i < model.Face.size(); i++)
	{
		CurrentVertex3[0](
			static_cast<int>(model.Origin[0] + ShiftOrigin[0] + model.Vertex.at(model.Face.at(i)[0] - 1)[0] * model.Scale[0]),
			static_cast<int>(model.Origin[1] + ShiftOrigin[1] + model.Vertex.at(model.Face.at(i)[0] - 1)[1] * model.Scale[1] * -1.0),
			static_cast<int>(model.Origin[2] + ShiftOrigin[2] + model.Vertex.at(model.Face.at(i)[0] - 1)[2] * model.Scale[2])
		);
		CurrentVertex3[1](
			static_cast<int>(model.Origin[0] + ShiftOrigin[0] + model.Vertex.at(model.Face.at(i)[1] - 1)[0] * model.Scale[0]),
			static_cast<int>(model.Origin[1] + ShiftOrigin[1] + model.Vertex.at(model.Face.at(i)[1] - 1)[1] * model.Scale[1] * -1.0),
			static_cast<int>(model.Origin[2] + ShiftOrigin[2] + model.Vertex.at(model.Face.at(i)[1] - 1)[2] * model.Scale[2])
		);
		CurrentVertex3[2](
			static_cast<int>(model.Origin[0] + ShiftOrigin[0] + model.Vertex.at(model.Face.at(i)[2] - 1)[0] * model.Scale[0]),
			static_cast<int>(model.Origin[1] + ShiftOrigin[1] + model.Vertex.at(model.Face.at(i)[2] - 1)[1] * model.Scale[1] * -1.0),
			static_cast<int>(model.Origin[2] + ShiftOrigin[2] + model.Vertex.at(model.Face.at(i)[2] - 1)[2] * model.Scale[2])
		);

		//TODO: Z depth. Temp solution? Draw half of the model
		if (CurrentVertex3[0][2] < 0.0 || CurrentVertex3[1][2] < 0.0 || CurrentVertex3[2][2] < 0.0) continue; 
		DrawPolygon(CurrentVertex3[0], CurrentVertex3[1], CurrentVertex3[2]);
	}
}

//TEST: Test code

//void DrawCircle(Vector2<int> a, int radius, double step, Vector3<unsigned char> color)
//{
//	const double pi = 3.14159265358979323846;
//	for (double angle = 0.0; angle < 360.0; angle += step) {
//		double _Angle = (angle / 360.0) * 2.0 * pi;		
//		_PutPixel(Vector2<int>(a[0] + static_cast<int>(radius * sin(_Angle)), a[1] + static_cast<int>(radius * cos(_Angle))), color);
//	}
//}
//void DrawFan(Vector2<int> a, int radius, double step,Vector3<unsigned char> color)
//{
//	const double pi = 3.14159265358979323846;
//	for (double angle = 0.0; angle < 360.0; angle += step) {
//		double _Angle = (angle / 360.0) * 2.0 * pi;
//		DrawLine(a,Vector2<int>(a[0] + static_cast<int>(radius * sin(_Angle)), a[1] + static_cast<int>(radius * cos(_Angle))), color);
//	}
//}


