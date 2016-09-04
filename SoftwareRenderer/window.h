#pragma once
#include <windows.h>
#include "config.h"

void DrawMyWindow(HWND hwndMain);
void TypeText(HWND hwndMain, std::string text);
void PlatformSpecificInitialization();
void OverlayHUD(HWND hwnd);

LRESULT CALLBACK WndProcedure(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

class _WINDOW
{
private:
	RECT drawing_area_rect;
	WNDCLASSEX wc;
	LPSTR className = "MainClass";
	bool _isInitialized = false;
public:
	MSG msg;
	HWND hwndMain;

	_WINDOW(HINSTANCE _hInstance, LPSTR _windowName, LPSTR _className = "MainClass");

	bool isInitialized() const
	{
		return _isInitialized;
	}

	void setDrawingAreaRect(LONG l = 0, LONG t = 0, LONG r = config.bufferSize[0], long b = config.bufferSize[1]);
	void setWC(HINSTANCE _hInstance);
};

extern BITMAPINFO bmi;
