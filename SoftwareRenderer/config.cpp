#include <random>
#include "config.h"

_SETTINGS settings;
void SetSettings(int x, int y) {
	srand(time_t(NULL));
	settings.bufferSizeX = x;
	settings.bufferSizeY = y;
	settings.intBytesize = sizeof(int);
	settings.backbuffer = malloc(x * y * settings.intBytesize);
	settings.isRunning = true;
}
