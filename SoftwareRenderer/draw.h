#pragma once
#include "object_handler.h"

void DrawModel(Model model, bool fill_polygons = true);
void Projection(float fov = config.camera.FocalLength, float aspectW = config.bufferSize[0], float aspectH = config.bufferSize[1], float clippingNear = config.clippingNear, float clippingFar = config.clippingFar);
void LookAt(Vector<float, 3> up = Vector3::Up<float>(), Vector<float, 3> cameraOrigin = config.camera.Origin);
void Viewport(int x = 0, int y = 0, int w = config.bufferSize[0], int h = config.bufferSize[1]);

