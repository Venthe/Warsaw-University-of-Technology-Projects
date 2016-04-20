#include "config.h"
#include "platform_specific.h"
#include "draw.h"
#include "object_handler.h"

#ifdef _WIN32
#include <windows.h>

Camera camera;

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
		switch (wParam)
		{
		case 'Z': camera.ShiftFocalLength(0.01); break;
		case 'X': camera.ShiftFocalLength(-0.01); break;
		case 'A': camera.ShiftLocation(Vector3<double>(-0.25,0,0)); break;
		case 'D': camera.ShiftLocation(Vector3<double>(0.25,0,0)); break;
		case 'W': camera.ShiftLocation(Vector3<double>(0,0.25,0)); break;
		case 'S': camera.ShiftLocation(Vector3<double>(0,-0.25,0)); break;
		case 'Q': camera.ShiftLocation(Vector3<double>(0,0,0.25)); break;
		case 'E': camera.ShiftLocation(Vector3<double>(0,0,-0.25)); break;
		default: break;
		}
		break;
	}
	return DefWindowProc(hWnd, Msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) // HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow
{
	SetSettings();
	PlatformSpecificInitialization();

	LPSTR className = "MainClass";
	MSG msg;
	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX); // The size, in bytes, of this structure. Set this member to sizeof(WNDCLASSEX)
	wc.cbClsExtra = 0; // The number of extra bytes to allocate following the window-class structure.
	wc.cbWndExtra = 0; // The number of extra bytes to allocate following the window instance. 
	wc.hInstance = hInstance; // A handle to the instance that contains the window procedure for the class. 
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_GLOBALCLASS; // The class style(s).
	wc.lpfnWndProc = WndProcedure; // A pointer to the window procedure. You must use the CallWindowProc function to call the window procedure.
	wc.hIcon = nullptr; // A handle to the class icon
	wc.hCursor = nullptr; // A handle to the class cursor. 
	wc.hbrBackground = nullptr; // A handle to the class background brush. 
	wc.lpszClassName = className; // A pointer to a null-terminated string or is an atom. 
	wc.lpszMenuName = nullptr; // Pointer to a null-terminated character string that specifies the resource name of the class menu
	wc.hIconSm = nullptr; // A handle to a small icon that is associated with the window class. 
	if (!RegisterClassEx(&wc)) // If hwnd is null; it means that the RegisterClassEx failed
		return GetLastError();
	RECT drawing_area_rect;
	drawing_area_rect.left = 0;
	drawing_area_rect.top = 0;
	drawing_area_rect.right = settings.bufferSize[0];
	drawing_area_rect.bottom = settings.bufferSize[1];
	AdjustWindowRectEx(&drawing_area_rect, WS_BORDER | WS_CAPTION | WS_SYSMENU, false, 0);
	HWND hwndMain = CreateWindowEx(
		0, // no extended styles           
		className, // class name                   
		"Main Window", // window name                  
		WS_BORDER | WS_CAPTION | WS_SYSMENU, // overlapped window                   
		CW_USEDEFAULT, // default horizontal position  
		CW_USEDEFAULT, // default vertical position    
		drawing_area_rect.right - drawing_area_rect.left, // default width                
		drawing_area_rect.bottom - drawing_area_rect.top, // default height               
		static_cast<HWND>(nullptr), // no parent or owner window    
		static_cast<HMENU>(nullptr), // class menu used              
		nullptr, // instance handle              
		nullptr); // no window creation data  

	if (hwndMain == nullptr) // If hwnd is null; it means that the window was not created
		return GetLastError();
	ShowWindow(hwndMain, SW_SHOW);
	UpdateWindow(hwndMain);

	//load file
	//TODO: Model name from command line?
	Model object("C:\\Users\\jacek\\Source\\Repos\\SoftwareRenderer\\Debug\\teapot.obj");
	object.Scale = Vector3<double>(100, -100, 100);
	object.Origin = Vector3<double>(320.0, 440.0, 0.0);

	camera.Origin = Vector3<double>(0, 0, 0);
	camera.FocalLength = -0.12;
	double RotationAngle = 0.0;

	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		FillRect();
		DrawGrid();
		DrawModel(object,camera,false);

		Draw(hwndMain);

		if (RotationAngle >= 360.0) { RotationAngle = 0.0; }
		else RotationAngle += 1.0;
		object.Rotation = Vector3 <double>(RotationAngle, 0.0, 0.0);

		std::string str = std::string("Ortographic\n\n") + "Model:\n" + "o:" + camera.Origin.ToString() + "\n" + "s:" + camera.Scale.ToString() + "\n" + "r:" + camera.Rotation.ToString() + "\n" + "Camera focal length: " + std::to_string(camera.FocalLength);
		TypeText(hwndMain, str);
		//InvalidateRect(hwndMain, nullptr, FALSE);
	}
	return EXIT_SUCCESS;
}

#endif // _WIN32


