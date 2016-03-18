#pragma once
struct _SETTINGS {
	int bufferSizeX;
	int bufferSizeY;
	int intBytesize;
	void * backbuffer;
	bool isRunning;
};
extern _SETTINGS settings;

void SetSettings(int x = 640, int y = 480);