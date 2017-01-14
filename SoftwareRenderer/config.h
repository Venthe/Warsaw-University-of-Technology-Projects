#pragma once

#define DIRECTORY_LENGTH 256

#include <array>
#include "types.h"
#include "object_handler.h"
#include "camera.h"

const int intBytesize = sizeof(int);
const unsigned char ucharBytesize = sizeof(unsigned char);
const int floatBytesize = sizeof(float);

class _CONFIG
{
private:
	unsigned short _drawMode = 0;

	void changePerspective();
	void changeLookAt();
public:
	char* CurrentDirectory = static_cast<char*>(std::malloc(sizeof(char) * DIRECTORY_LENGTH));
	bool LookAt = false;
	bool hideHUD = false;
	bool Perspective = true;

	Vector<int, 2> bufferSize;
	void* backbuffer;
	void* zbackbuffer;

	Camera camera;
	Camera defaultCamera;

	std::array<float, 16> ViewMatrix;
	std::array<float, 16> ViewportMatrix;
	std::array<float, 16> ProjectionMatrix;
	
	_CONFIG(int x = 640, int y = 480, Vector<float, 3> Origin = Vector<float, 3>({ 0.f, 0.f, -5.f }), Vector<float, 3> Rotation = Vector<float, 3>(), float FocalLength = 60., float clipNear = 0.02f, float clipFar = 600.);

	void changeDrawMode();
	void changeHudDisplay();
	int getDrawMode() const;
};

extern _CONFIG config;