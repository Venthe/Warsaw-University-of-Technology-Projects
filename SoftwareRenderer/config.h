#pragma once

#define DIRECTORY_LENGTH 256

#include <array>
#include "types.h"
#include "object_handler.h"

const int intBytesize = sizeof(int);
const unsigned char ucharBytesize = sizeof(unsigned char);
const int floatBytesize = sizeof(float);

class _CONFIG
{
private:
	unsigned short _drawMode = 0;

	void changePerspective()
	{
		if (!Perspective)Perspective = true;
		else Perspective = false;
	}
	void changeLookAt()
	{
		if (!LookAt) LookAt = true;
		else LookAt = false;
	}
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

	void changeDrawMode()
	{
		if (++_drawMode > 1) _drawMode = 0;
	}

	void changeHudDisplay()
	{
		if (!hideHUD) hideHUD = true;
		else hideHUD = false;
	}

	int getDrawMode()
	{
		return _drawMode;
	}

	_CONFIG(int x = 640, int y = 480, Vector<float, 3> Origin = Vector<float, 3>({ 0.f, 0.f, -5.f }), Vector<float, 3> Rotation = Vector<float, 3>(), float FocalLength = 60., float clipNear = 0.02f, float clipFar = 600.);
};

extern _CONFIG config;