#pragma once
#include <array>
#include "types.h"
#include "object_handler.h"

struct _CONFIG
{
	Vector2<int> bufferSize;
	int intBytesize;
	void* backbuffer;
	Camera camera;
	std::array<double, 16> ViewMatrix;
	std::array<double, 16> Viewport;
	std::array<double, 16> Projection;
} extern config;

//extern _CONFIG config;

void SetSettings(int x = 640, int y = 480);

