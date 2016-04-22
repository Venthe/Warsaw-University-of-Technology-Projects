#include <random>
#include <array>
#include "config.h"

_CONFIG config;

void SetSettings(int x, int y)
{
	srand(time_t(NULL));
	config.bufferSize[0] = x;
	config.bufferSize[1] = y;
	config.intBytesize = sizeof(int);
	config.backbuffer = malloc(x * y * config.intBytesize);
	config.camera.Origin = Vector3<double>(0.0, 0.0, 15.0);
	config.camera.Rotation = Vector3<double>(0.0, 0.0, 0.0);
	config.camera.FocalLength = 60.;
	config.ViewMatrix = IdentityMatrix<double,4>();
	config.Viewport = IdentityMatrix<double, 4>();
	config.Projection = IdentityMatrix<double, 4>();
}

