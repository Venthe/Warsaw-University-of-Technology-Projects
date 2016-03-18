#pragma once
#ifdef _WIN32
#include <Windows.h>

/// Draws the backbuffer onto window
void Draw(HWND hwndMain);
void TypeText(HWND hwndMain, char * text);
/// Sets BMI
void PlatformSpecificInitialization();

extern BITMAPINFO bmi;
#endif