#include "config.h"
#include "platform_specific.h"
#include "draw.h"
#include "file_handler.h"

#ifdef _WIN32
#include <windows.h>


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
	default:
		return DefWindowProc(hWnd, Msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetSettings();
	PlatformSpecificInitialization();

	LPSTR className = "MainClass";
	MSG msg;
	BOOL bRet;
	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX); // The size, in bytes, of this structure. Set this member to sizeof(WNDCLASSEX)
	wc.cbClsExtra = 0; // The number of extra bytes to allocate following the window-class structure.
	wc.cbWndExtra = 0; // The number of extra bytes to allocate following the window instance. 
	wc.hInstance = hInstance; // A handle to the instance that contains the window procedure for the class. 
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_GLOBALCLASS; // The class style(s).
	wc.lpfnWndProc = WndProcedure; // A pointer to the window procedure. You must use the CallWindowProc function to call the window procedure.
	wc.hIcon = NULL; // A handle to the class icon
	wc.hCursor = NULL; // A handle to the class cursor. 
	wc.hbrBackground = NULL; // A handle to the class background brush. 
	wc.lpszClassName = className; // A pointer to a null-terminated string or is an atom. 
	wc.lpszMenuName = NULL; // Pointer to a null-terminated character string that specifies the resource name of the class menu
	wc.hIconSm = NULL; // A handle to a small icon that is associated with the window class. 
	if (!RegisterClassEx(&wc)) // If hwnd is null; it means that the RegisterClassEx failed
		return GetLastError();
	RECT drawing_area_rect;
	drawing_area_rect.left = 0;
	drawing_area_rect.top = 0;
	drawing_area_rect.right = settings.bufferSizeX;
	drawing_area_rect.bottom = settings.bufferSizeY;
	AdjustWindowRectEx(&drawing_area_rect, WS_BORDER | WS_CAPTION | WS_SYSMENU, false, 0);
	HWND hwndMain = CreateWindowEx(
		0,                      // no extended styles           
		className,           // class name                   
		"Main Window",          // window name                  
		WS_BORDER | WS_CAPTION | WS_SYSMENU,   // overlapped window                   
		CW_USEDEFAULT,          // default horizontal position  
		CW_USEDEFAULT,          // default vertical position    
		drawing_area_rect.right - drawing_area_rect.left,          // default width                
		drawing_area_rect.bottom - drawing_area_rect.top,          // default height               
		(HWND)NULL,             // no parent or owner window    
		(HMENU)NULL,            // class menu used              
		NULL,				    // instance handle              
		NULL);                  // no window creation data  

	if (hwndMain == NULL) // If hwnd is null; it means that the window was not created
		return GetLastError();
	ShowWindow(hwndMain, SW_SHOW);
	UpdateWindow(hwndMain);

	//load file
	ObjModel obj;
	bool modelLoaded = false;
	obj.ReadObj("model.obj");
	obj.Scale = 80.0;
	obj.Origin(320.0, 240.0, 0.0);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		FillRect();
		DrawGrid();
		////DrawCircle(320, 240, 200, 0.1);
		//DrawFan(320, 240, 150, 5.0, 0, 0xff, 0);
		DrawObj(obj,ThreeTuple<double>(0.0,100.0,0.0));
		Draw(hwndMain);
		std::string str = "Ortographic";
		TypeText(hwndMain, str);
	}
	return EXIT_SUCCESS;
}

#endif // _WIN32