#pragma once
#include "config.h"

namespace DrawCommon
{
	void DrawModel(Model model);
	void SetProjection(float fov = config.camera.FocalLength, float aspectW = config.bufferSize[0], float aspectH = config.bufferSize[1], float clippingNear = config.clipNear, float clippingFar = config.clipFar);
	void LookAt(Vector<float, 3> up = Vector3::Up<float>(), Vector<float, 3> cameraOrigin = config.camera.Origin);
	void SetViewport(int x = 0, int y = 0, int w = config.bufferSize[0], int h = config.bufferSize[1]);
};