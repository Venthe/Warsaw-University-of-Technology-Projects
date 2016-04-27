#pragma once
#include <string>
#ifdef _WIN32
#include <Windows.h>
#define DIRECTORY_LENGTH 256

/// Draws the backbuffer onto window
void Draw(HWND hwndMain);
void TypeText(HWND hwndMain, std::string text);
/// Sets BMI
void PlatformSpecificInitialization();

extern BITMAPINFO bmi;
#endif

