#include <random>
#include "config.h"

_SETTINGS settings;

void SetSettings(int x, int y)
{
	srand(time_t(NULL));
	settings.bufferSize[0] = x;
	settings.bufferSize[1] = y;
	settings.intBytesize = sizeof(int);
	settings.backbuffer = malloc(x * y * settings.intBytesize);
}

