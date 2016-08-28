#pragma once
#include <array>
#include "types.h"
#include "object_handler.h"
#include "platform_specific.h"

const int intBytesize = sizeof(int);
const unsigned char ucharBytesize = sizeof(unsigned char);

class _CONFIG
{
public:
	Vector<int, 2> bufferSize;
	void* backbuffer;
	void* zbackbuffer;

	Camera camera;
	Camera defaultCamera;
	bool LookAt = false;
	bool hideHUD = false;
	bool Perspective = true;

	std::array<float, 16> ViewMatrix;
	std::array<float, 16> ViewportMatrix;
	std::array<float, 16> ProjectionMatrix;
	char* CurrentDirectory = static_cast<char*>(std::malloc(sizeof(char) * DIRECTORY_LENGTH));

	float clipNear;
	float clipFar;

	_CONFIG(int x = 640, int y = 480, Vector<float, 3> Origin = Vector<float, 3>({ 0.f, 0.f, -5.f }), Vector<float, 3> Rotation = Vector<float, 3>(), float FocalLength = 60., float clipNear = 0.02f, float clipFar = 600.);
};