#include <windows.h>
#include "config.h"
#include "my_math.h"

_CONFIG config;

_CONFIG::_CONFIG(int x, int y, Vector3f Origin, Vector3f Rotation, float FocalLength, float _clipNear, float _clipFar)
{
	srand(time_t(NULL));
	bufferSize[0] = x;
	bufferSize[1] = y;
	backbuffer = malloc(x * y * intBytesize);
	zbackbuffer = malloc(x * y * floatBytesize);

	camera.Origin = Origin;
	camera.Rotation = Rotation;
	camera.focalLength = FocalLength;
	camera.clipFar = _clipFar;
	camera.clipNear = _clipNear;

	defaultCamera = camera;

	ViewMatrix = IdentityMatrix<float, 16>();
	ViewportMatrix = IdentityMatrix<float, 16>();
	ProjectionMatrix = IdentityMatrix<float, 16>();

	GetCurrentDirectory(DIRECTORY_LENGTH, CurrentDirectory);
}

void _CONFIG::changePerspective() { Perspective = !Perspective; }
void _CONFIG::changeDrawMode() { if (++_drawMode > 1) _drawMode = 0; }
void _CONFIG::changeHudDisplay() { hideHUD = !hideHUD; }
int _CONFIG::getDrawMode() const { return _drawMode; }
int _CONFIG::getPerspective() const { return Perspective; }
