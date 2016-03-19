#pragma once
#include "types.h"

struct _SETTINGS
{
	Vector2<int> bufferSize;
	int intBytesize;
	void* backbuffer;
};

extern _SETTINGS settings;

void SetSettings(int x = 640, int y = 480);

