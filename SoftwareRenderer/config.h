#pragma once
#include <array>
#include "types.h"
#include "object_handler.h"
#include "platform_specific.h"

struct _CONFIG
{
	Vector<int,2> bufferSize;
	void* backbuffer;
	Camera camera;
	Camera defaultCamera;

	int intBytesize = sizeof(int);
	bool LookAt = false;
	bool hideHUD = false;
	bool Perspective = true;

	std::array<double, 16> ViewMatrix = MyMath::IdentityMatrix<double, 16>();
	std::array<double, 16> ViewportMatrix = MyMath::IdentityMatrix<double, 16>();
	std::array<double, 16> ProjectionMatrix = MyMath::IdentityMatrix<double, 16>();
	char * CurrentDirectory = static_cast<char*>(std::malloc(sizeof(char)*DIRECTORY_LENGTH));
};

extern _CONFIG config;

void SetSettings(int x = 640, int y = 480, Vector<double, 3> Origin = Vector<double, 3>({ -0.0, 0.0, -5.0 }), Vector<double, 3> Rotation = Vector<double, 3>(), double FocalLength = 25.);

