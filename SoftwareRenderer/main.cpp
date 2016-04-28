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
			//Focal length
		case 'Z': config.camera.ShiftFocalLength(2.5); break;
		case 'X': config.camera.ShiftFocalLength(-2.5); break;
			//Translation
		case 'A': config.camera.ShiftLocation(Vector3<double>(-0.1,0,0)); break;
		case 'D': config.camera.ShiftLocation(Vector3<double>(0.1,0,0)); break;
		case 'W': config.camera.ShiftLocation(Vector3<double>(0,0.1,0)); break;
		case 'S': config.camera.ShiftLocation(Vector3<double>(0,-0.1,0)); break;
		case 'Q': config.camera.ShiftLocation(Vector3<double>(0,0,0.1)); break;
		case 'E': config.camera.ShiftLocation(Vector3<double>(0,0,-0.1)); break;
			//Rotation
		case 'Y': config.camera.ShiftRotation(Vector3<double>(-5, 0, 0)); break;
		case 'U': config.camera.ShiftRotation(Vector3<double>(5, 0, 0)); break;
		case 'H': config.camera.ShiftRotation(Vector3<double>(0, 5, 0)); break;
		case 'J': config.camera.ShiftRotation(Vector3<double>(0, -5, 0)); break;
		case 'N': config.camera.ShiftRotation(Vector3<double>(0, 0, 5)); break;
		case 'M': config.camera.ShiftRotation(Vector3<double>(0, 0, -5)); break;
			//Misc
		case 'F': //Perspective camera
			if (config.Perspective == false) { config.Perspective = true; }
			else { config.Perspective = false; }
			break;
		case 'R': //Reset camera
			config.camera = config.defaultCamera;
			break;
		case 'T': //change camera pointing method
			if (config.LookAt == false) { config.LookAt = true; }
			else { config.LookAt = false; }
			break;
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

	wc.cbSize = sizeof(WNDCLASSEX); // The size, in bytes, of this structure. Set this member to sizeof(WNDCLASSEx)
	wc.cbClsExtra = 0; // The number of extra bytes to allocate following the window-class structure.
	wc.cbWndExtra = 0; // The number of extra bytes to allocate following the window instance. 
	wc.hInstance = hInstance; // A handle to the instance that contains the window procedure for the class. 
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_GLOBALCLASS; // The class style(s).
	wc.lpfnWndProc = WndProcedure; // A pointer to the window procedure. you must use the CallWindowProc function to call the window procedure.
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
	Model object((std::string(config.CurrentDirectory) + std::string("\\teapot.obj")).c_str(),Vector3<double>(-3, 2, 1.5), Vector3<double>(50, 0, 0), Vector3<double>(.1, -.1, .1));
	Model ball((std::string(config.CurrentDirectory) + std::string("\\center.obj")).c_str(),Vector3<double>(),Vector3<double>(),Vector3<double>(.1,.1,.1));
	Model grid((std::string(config.CurrentDirectory) + std::string("\\grid.obj")).c_str(), Vector3<double>(), Vector3<double>(), Vector3<double>(.1, .1, .1));

	Viewport();
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		FillRect(Vector3<unsigned char>(70,70,70));
		DrawGrid();

		Projection();
		if(config.LookAt) LookAt();
		else LookAtNothing();
		DrawModel(object);

		for(int i = 0; i <4 ; i++)
		{
			ball.Origin(4, 0, -i*5);
			DrawModel(ball);
			ball.Origin(-4, 0, -i*5);
			DrawModel(ball);
		}
		for(int j= 0,a=36,b=36;j<a;j++)
		{
			for (int k = 0; k < b; k++)
			{
				grid.Origin(-static_cast<int>(b / 2) +k, 0, -static_cast<int>(a/2) + j);
				DrawModel(grid);
			}
		}

		Draw(hwndMain);

		std::string str = "Camera:\no:" + config.camera.Origin.ToString()+"\nr:" + config.camera.Rotation.ToString() + "\nCamera focal length: " + std::to_string(config.camera.FocalLength);
		TypeText(hwndMain, str);
		//InvalidateRect(hwndMain, nullptr, FALSE);
	}
	return EXIT_SUCCESS;
}

#endif // _WIN32


