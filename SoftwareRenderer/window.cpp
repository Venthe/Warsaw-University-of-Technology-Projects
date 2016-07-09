#include "control.h"
#include "window.h"
#include <iostream>

LRESULT CALLBACK WndProcedure(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_DESTROY:
		PostQuitMessage(WM_QUIT);
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_KEYUP:
		Controller(wParam);
		break;
	}
	return DefWindowProc(hWnd, Msg, wParam, lParam);
}

void _WINDOW::setDrawingAreaRect(LONG l, LONG t, LONG r, LONG b)
{
	drawing_area_rect.left = l;
	drawing_area_rect.top = t;
	drawing_area_rect.right = r;
	drawing_area_rect.bottom = b;
}

void _WINDOW::setWC(HINSTANCE _hInstance)
{
	wc.cbSize = sizeof(WNDCLASSEX); // The size, in bytes, of this structure. Set this member to sizeof(WNDCLASSEx)
	wc.cbClsExtra = 0; // The number of extra bytes to allocate following the window-class structure.
	wc.cbWndExtra = 0; // The number of extra bytes to allocate following the window instance. 
	wc.hInstance = _hInstance; // A handle to the instance that contains the window procedure for the class. 
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_GLOBALCLASS; // The class style(s).
	wc.lpfnWndProc = WndProcedure; // A pointer to the window procedure. you must use the CallWindowProc function to call the window procedure.
	wc.hIcon = nullptr; // A handle to the class icon
	wc.hCursor = nullptr; // A handle to the class cursor. 
	wc.hbrBackground = nullptr; // A handle to the class background brush. 
	wc.lpszClassName = className; // A pointer to a null-terminated string or is an atom. 
	wc.lpszMenuName = nullptr; // Pointer to a null-terminated character string that specifies the resource name of the class menu
	wc.hIconSm = nullptr; // A handle to a small icon that is associated with the window class.
}

_WINDOW::_WINDOW(HINSTANCE _hInstance, LPSTR _windowName, LPSTR _className)
{
	className = _className;

	PlatformSpecificInitialization();
	setWC(_hInstance);
	setDrawingAreaRect();

	if (!RegisterClassEx(&wc)) // If hwnd is null; it means that the RegisterClassEx failed
	{
		std::cout << GetLastError();
		return;
	}

	AdjustWindowRectEx(&drawing_area_rect, WS_BORDER | WS_CAPTION | WS_SYSMENU, false, 0);

	hwndMain = CreateWindowEx(
		0, // no extended styles           
		className, // class name                   
		_windowName, // window name                  
		WS_BORDER | WS_CAPTION | WS_SYSMENU, // overlapped window                   
		CW_USEDEFAULT, // default horizontal position  
		CW_USEDEFAULT, // default vertical position    
		drawing_area_rect.right - drawing_area_rect.left, // default width                
		drawing_area_rect.bottom - drawing_area_rect.top, // default height               
		static_cast<HWND>(nullptr), // no parent or owner window    
		static_cast<HMENU>(nullptr), // class menu used              
		nullptr, // instance handle              
		nullptr); // no window creation data  

	if (hwndMain == nullptr)// If hwnd is null; it means that the window was not created
	{
		std::cout << GetLastError();
		return;
	}
	ShowWindow(hwndMain, SW_SHOW);
	UpdateWindow(hwndMain);
	_isInitialized = true;
}

