#include "config.h"
#include "platform_specific.h"
#include "draw.h"
#include "object_handler.h"

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
	case WM_KEYUP:
		switch (wParam)
		{
		case 'Z': config.camera.ShiftFocalLength(0.01); break;
		case 'X': config.camera.ShiftFocalLength(-0.01); break;
		case 'A': config.camera.ShiftLocation(Vector3<double>(-5.0,0,0)); break;
		case 'D': config.camera.ShiftLocation(Vector3<double>(5.0,0,0)); break;
		case 'W': config.camera.ShiftLocation(Vector3<double>(0,5.0,0)); break;
		case 'S': config.camera.ShiftLocation(Vector3<double>(0,-5.0,0)); break;
		case 'Q': config.camera.ShiftLocation(Vector3<double>(0,0,5.0)); break;
		case 'E': config.camera.ShiftLocation(Vector3<double>(0,0,-5.0)); break;
		default: break;
		}
		break;
	}
	return DefWindowProc(hWnd, Msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) // HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow
{
	SetSettings(1024,768);
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
	drawing_area_rect.right = config.bufferSize[0];
	drawing_area_rect.bottom = config.bufferSize[1];
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
	object.Origin(0,0, 0);
	config.camera.Origin(45,75,100);
	object.Scale = Vector3<double>(0.1, -0.1, 0.1);

	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		FillRect(Vector3<unsigned char>(70,70,70));
		DrawGrid();
		Projection();
		LookAt(Vector3<double>(0,0,0), Vector3<double>::Up());
		Viewport(config.bufferSize[0], config.bufferSize[1], config.bufferSize[0], config.bufferSize[1]);
		DrawModel(object);

		Draw(hwndMain);

		std::string str = std::string("Ortographic\n\n") + "Model:\n" + "o:" + config.camera.Origin.ToString() + "\n" + "s:" + config.camera.Scale.ToString() + "\n" + "r:" + config.camera.Rotation.ToString() + "\n" + "Camera focal length: " + std::to_string(config.camera.FocalLength);
		TypeText(hwndMain, str);
		//InvalidateRect(hwndMain, nullptr, FALSE);
	}
	return EXIT_SUCCESS;
}

#endif // _WIN32


