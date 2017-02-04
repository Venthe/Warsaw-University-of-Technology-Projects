#pragma once
#include <array>
#include "types.h"
#include "camera.h"

#define DIRECTORY_LENGTH 256

const int intBytesize = sizeof(int);
const unsigned char ucharBytesize = sizeof(unsigned char);
const int floatBytesize = sizeof(float);

class _CONFIG
{
private:
	unsigned short _drawMode = 0;
public:
	char* CurrentDirectory = static_cast<char*>(std::malloc(sizeof(char) * DIRECTORY_LENGTH));
	bool LookAt = false;
	bool hideHUD = false;
	bool Perspective = true;

	Vector2i bufferSize;
	void* backbuffer;
	void* zbackbuffer;

	Camera camera;
	Camera defaultCamera;

	Matrix4f ViewMatrix;
	Matrix4f ViewportMatrix;
	Matrix4f ProjectionMatrix;

	_CONFIG(int x = 640, int y = 480, Vector3f Origin = {0.f, 0.f, -5.f}, Vector3f Rotation = Vector3f(), float FocalLength = 60., float clipNear = 0.02f, float clipFar = 600.);

	void changeDrawMode();
	int getDrawMode() const;
	void changeHudDisplay();
	void changePerspective();
	int getPerspective() const;
};

extern _CONFIG config;
