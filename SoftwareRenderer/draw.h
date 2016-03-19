#pragma once
#include "file_handler.h"

void FillRect(bool random); // Fills drawing area with noise
void FillRect(Vector2<int> a, Vector2<int> b, Vector3<unsigned char> color);
void FillRect(Vector3<unsigned char> color = Vector3<unsigned char>(0, 0, 0)); // Fills whole drawing area with a certain color

void DrawObj(ObjModel model, Vector3<double> ShiftOrigin = Vector3<double>(0.0, 0.0, 0.0));
void DrawPolygon(Vector3<int> a, Vector3<int> b, Vector3<int> c, Vector3<unsigned char> color = Vector3<unsigned char>(0xff, 0xff, 0xff));
void DrawLine(Vector2<int> a, Vector2<int> b, Vector3<unsigned char> color = Vector3<unsigned char>(0xff, 0xff, 0xff)); // Draws line, Bresenham's line algorithm
void DrawGrid(int density = 32, Vector3<unsigned char> color = Vector3<unsigned char>(32, 32, 32));


// TEST: Test code for Bersenham's validity
//void DrawCircle(Vector2<int> a, int radius, double step, Vector3<unsigned char> color = Vector3<unsigned char>(0xff, 0xff, 0xff));
//void DrawFan(Vector2<int> a, int radius, double step, Vector3<unsigned char> color = Vector3<unsigned char>(0xff, 0xff, 0xff));


