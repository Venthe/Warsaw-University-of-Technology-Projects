#pragma once
#include "object_handler.h"

void FillRect(bool random); // Fills drawing area with noise
void FillRect(Vector2<int> a, Vector2<int> b, Vector3<unsigned char> color);
void FillRect(Vector3<unsigned char> color = Vector3<unsigned char>(0, 0, 0)); // Fills whole drawing area with a certain color

void DrawModel(Model model, Camera camera, bool fill_polygons = false);
void DrawGrid(int density = 32, Vector3<unsigned char> color = Vector3<unsigned char>(32, 32, 32));