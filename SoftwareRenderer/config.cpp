#include "config.h"

_CONFIG config;

void SetSettings(int x, int y, Vector<double, 3> Origin, Vector<double, 3> Rotation, double FocalLength)
{
	srand(time_t(NULL));
	config.bufferSize[0] = x;
	config.bufferSize[1] = y;
	config.backbuffer = malloc(x * y * config.intBytesize);

	config.camera.Origin = Origin;
	config.camera.Rotation = Rotation;
	config.camera.FocalLength = FocalLength;
	config.defaultCamera = config.camera;

	std::array<double, 16> ViewMatrix = MyMath::IdentityMatrix<double, 16>();
	std::array<double, 16> ViewportMatrix = MyMath::IdentityMatrix<double, 16>();
	std::array<double, 16> ProjectionMatrix = MyMath::IdentityMatrix<double, 16>();

	GetCurrentDirectory(DIRECTORY_LENGTH, config.CurrentDirectory);
}

