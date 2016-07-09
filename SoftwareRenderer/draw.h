#pragma once
#include "object_handler.h"

void DrawModel(Model model, bool fill_polygons = false);
void Projection(double fov=config.camera.FocalLength, double aspectW=config.bufferSize[0], double aspectH = config.bufferSize[1], double clippingNear=0.05, double clippingFar=50.);
void LookAt(Vector<double, 3> up = Vector3::Up<double>(), Vector<double, 3> cameraOrigin = config.camera.Origin);
void Viewport(int x = 0, int y = 0, int w = config.bufferSize[0], int h = config.bufferSize[1] );