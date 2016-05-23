#include "config.h"

_CONFIG config;

void SetSettings(int x, int y, Vector<double,3> Origin , Vector<double,3> Rotation, double FocalLength)
{
	srand(time_t(NULL));
	config.bufferSize[0] = x;
	config.bufferSize[1] = y;
	config.backbuffer = malloc(x * y * config.intBytesize);

	config.ViewMatrix = MyMath::IdentityMatrix<double, 16>();
	config.ViewportMatrix = MyMath::IdentityMatrix<double, 16>();
	config.ProjectionMatrix = MyMath::IdentityMatrix<double, 16>();

	config.camera.Origin = Origin;
	config.camera.Rotation = Rotation;
	config.camera.FocalLength = FocalLength;
	config.defaultCamera = config.camera;
	GetCurrentDirectory(DIRECTORY_LENGTH, config.CurrentDirectory);
}