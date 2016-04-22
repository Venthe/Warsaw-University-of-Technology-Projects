#pragma once
#include "object_handler.h"

void FillRect(bool random); // Fills drawing area with noise
void FillRect(Vector2<int> a, Vector2<int> b, Vector3<unsigned char> color);
void FillRect(Vector3<unsigned char> color = Vector3<unsigned char>(0, 0, 0)); // Fills whole drawing area with a certain color

void DrawModel(Model model, bool fill_polygons = false);
void DrawGrid(int density = 32, Vector3<unsigned char> color = Vector3<unsigned char>(32, 32, 32));

void Projection(double fov=config.camera.FocalLength, double aspectW=config.bufferSize[0], double aspectH = config.bufferSize[1], double clippingNear=0.1, double clippingFar=100.);
//void Viewport(int x, int y, int w, int h);
void LookAt(Vector3<double> lookat, Vector3<double> up, Vector3<double> cameraOrigin = config.camera.Origin);