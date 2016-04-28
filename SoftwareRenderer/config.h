#pragma once
#include <array>
#include "types.h"
#include "object_handler.h"
#include "platform_specific.h"

struct _CONFIG
{
	Vector2<int> bufferSize;
	int intBytesize = sizeof(int);
	void* backbuffer;
	Camera camera;
	Camera defaultCamera;
	bool LookAt = true;
	bool Perspective = true;
	std::array<double, 16> ViewMatrix = MyMath::IdentityMatrix<double, 16>();
	std::array<double, 16> ViewportMatrix = MyMath::IdentityMatrix<double, 16>();
	std::array<double, 16> ProjectionMatrix = MyMath::IdentityMatrix<double, 16>();
	char * CurrentDirectory = static_cast<char*>(std::malloc(sizeof(char)*DIRECTORY_LENGTH));
};

extern _CONFIG config;

void SetSettings(int x = 640, int y = 480, Vector3<double> Origin = Vector3<double>(-0.0, 0.0, -5.0), Vector3<double> Rotation = Vector3<double>(0.0, 0.0, 0.0), double FocalLength = 25.);

