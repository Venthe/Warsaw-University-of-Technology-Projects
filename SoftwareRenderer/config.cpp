#include "config.h"

_CONFIG config;

void SetSettings(int x, int y, Vector<float, 3> Origin, Vector<float, 3> Rotation, float FocalLength)
{
	srand(time_t(NULL));
	config.bufferSize[0] = x;
	config.bufferSize[1] = y;
	config.backbuffer = malloc(x * y * intBytesize);
	config.zbackbuffer = malloc(x * y * ucharBytesize);

	config.camera.Origin = Origin;
	config.camera.Rotation = Rotation;
	config.camera.FocalLength = FocalLength;
	config.defaultCamera = config.camera;

	std::array<float, 16> ViewMatrix = MyMath::IdentityMatrix<float, 16>();
	std::array<float, 16> ViewportMatrix = MyMath::IdentityMatrix<float, 16>();
	std::array<float, 16> ProjectionMatrix = MyMath::IdentityMatrix<float, 16>();

	GetCurrentDirectory(DIRECTORY_LENGTH, config.CurrentDirectory);
}

