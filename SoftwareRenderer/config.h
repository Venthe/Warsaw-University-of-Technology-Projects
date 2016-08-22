#pragma once
#include <array>
#include "types.h"
#include "object_handler.h"
#include "platform_specific.h"

const int intBytesize = sizeof(int);
const unsigned char ucharBytesize = sizeof(unsigned char);

struct _CONFIG
{
	Vector<int, 2> bufferSize;
	void* backbuffer;
	void* zbackbuffer;
	Camera camera;
	Camera defaultCamera;
	bool LookAt = true;
	bool hideHUD = false;
	bool Perspective = true;

	std::array<float, 16> ViewMatrix;
	std::array<float, 16> ViewportMatrix;
	std::array<float, 16> ProjectionMatrix;
	char* CurrentDirectory = static_cast<char*>(std::malloc(sizeof(char) * DIRECTORY_LENGTH));

	float clippingNear, clippingFar;
};

extern _CONFIG config;

void SetSettings(int x = 640, int y = 480,
	Vector<float, 3> Origin = Vector<float, 3>({ 1.4f, -0.8f, -5.0f }),
	Vector<float, 3> Rotation = Vector<float, 3>(), float FocalLength = 60.,
	float clippingNear = 0.005, float clippingFar = 500.);

