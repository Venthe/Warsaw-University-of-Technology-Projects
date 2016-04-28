#include "config.h"

_CONFIG config;

void SetSettings(int x, int y, Vector3<double> Origin , Vector3<double> Rotation, double FocalLength)
{
	srand(time_t(NULL));
	config.bufferSize[0] = x;
	config.bufferSize[1] = y;
	config.backbuffer = malloc(x * y * config.intBytesize);

	config.camera.Origin = Origin;
	config.camera.Rotation = Rotation;
	config.camera.FocalLength = FocalLength;
	config.defaultCamera = config.camera;
	GetCurrentDirectory(DIRECTORY_LENGTH, config.CurrentDirectory);
}