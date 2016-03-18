#pragma once
#include "file_handler.h"
/// Fill set part of buffer with color
void FillRect(int x, int y, int maxX, int maxY, unsigned char red, unsigned char green, unsigned char blue);
/// Fill whole buffer with random color
void FillRect(bool random);
/// Fill whole buffer with set color
void FillRect(unsigned char red, unsigned char green, unsigned char blue);
/// Fill whole buffer with black
void FillRect();
/// Draws line, Bresenham's line algorithm
void DrawLine(int x, int y, int tx, int ty,unsigned char r=0xff, unsigned char g=0xff, unsigned char b=0xff);
void DrawCircle(int x, int y, int radius, double step, unsigned char r = 0xff, unsigned char g = 0xff, unsigned char b = 0xff);
void DrawFan(int x, int y, int radius, double step, unsigned char r = 0xff, unsigned char g = 0xff, unsigned char b = 0xff);
void DrawObj(ObjModel model, ThreeTuple<double> ShiftOrigin = ThreeTuple<double>(0.0,0.0,0.0));
void DrawGrid(int density=32, unsigned char r=32, unsigned char g=32, unsigned char b=32);