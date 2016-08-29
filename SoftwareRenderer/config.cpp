#include "config.h"

_CONFIG::_CONFIG(int x, int y, Vector<float, 3> Origin, Vector<float, 3> Rotation, float FocalLength, float _clipNear, float _clipFar)
{
	srand(time_t(NULL));
	bufferSize[0] = x;
	bufferSize[1] = y;
	backbuffer = malloc(x * y * intBytesize);
	zbackbuffer = malloc(x * y * ucharBytesize);

	camera.Origin = Origin;
	camera.Rotation = Rotation;
	camera.FocalLength = FocalLength;
	defaultCamera = camera;

	clipFar = _clipFar;
	clipNear = _clipNear;

	ViewMatrix = MyMath::IdentityMatrix<float, 16>();
	ViewportMatrix = MyMath::IdentityMatrix<float, 16>();
	ProjectionMatrix = MyMath::IdentityMatrix<float, 16>();

	GetCurrentDirectory(DIRECTORY_LENGTH, CurrentDirectory);
}

