#include <iostream>
#include "window.h"
#include "controller.h"

BITMAPINFO bmi;

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


void OverlayHUD(HWND hwnd)
{
	if (!config.hideHUD)
	{
		//Overlaying data
		std::string str = "Camera:\no:" + config.camera.Origin.ToString() + "\nr:" + config.camera.Rotation.ToString() + "\nCamera focal length: " + std::to_string(config.camera.FocalLength);
		if (config.LookAt) str.append("\n").append("Looking at center");
		else str.append("\n").append("Looking in front");
		if (config.Perspective) str.append("\n").append("Perspective");
		else str.append("\n").append("Ortho");

		//Keybindings
		str.append("\n");

		//Focal length
		str.append("\n").append("Z: Increase Focal Length");
		str.append("\n").append("X: Decrease Focal Length");

		//Translation
		str.append("\n").append("A: Translate X decrease");
		str.append("\n").append("D: Translate X increase");
		str.append("\n").append("S: Translate Y decrease");
		str.append("\n").append("W: Translate Y increase");
		str.append("\n").append("Q: Translate Z increase");
		str.append("\n").append("E: Translate Z decrease");
		//Pitch, Yaw,Roll
		str.append("\n").append("Y: Rotate X decrease");
		str.append("\n").append("U: Rotate X increase");
		str.append("\n").append("H: Rotate Y increase");
		str.append("\n").append("J: Rotate Y decrease");
		str.append("\n").append("N: Rotate Z increase");
		str.append("\n").append("M: Rotate Z decrease");

		//Misc
		str.append("\n").append("F: Switch perspective");
		str.append("\n").append("R: Reset camera");
		str.append("\n").append("T: Change target of camera");
		str.append("\n").append("C: Hide the HUD");
		str.append("\n").append("G: Change drawing mode, current: " + config.getDrawMode());

		TypeText(hwnd, str);
	}
}


void DrawMyWindow(HWND hwndMain)
{
	HDC dc = GetDC(hwndMain);
	StretchDIBits(dc,
		0, 0, config.bufferSize[0], config.bufferSize[1],
		0, 0, config.bufferSize[0], config.bufferSize[1],
		config.backbuffer, &bmi,
		DIB_RGB_COLORS, SRCCOPY
	);
	DeleteDC(dc);
}

void TypeText(HWND hwndMain, std::string text)
{
	LPSTR txt = const_cast<char *>(text.c_str());
	HDC hdc = GetDC(hwndMain);
	RECT rect;
	GetClientRect(hwndMain, &rect);
	DrawTextEx(hdc, txt, static_cast<int>(text.length()), &rect, 0, nullptr);
	DeleteDC(hdc);
}

void PlatformSpecificInitialization()
{
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER); // The number of i.mbytesb required by the structure.
	bmi.bmiHeader.biWidth = config.bufferSize[0]; // The width of the bitmap, in i.mbpixels.
	bmi.bmiHeader.biHeight = -config.bufferSize[1]; // The height of the bitmap, i.ni mbpixels
	bmi.bmiHeader.biPlanes = 1; //The number of planes for the target i.mbdevice. This value must be set to 1.
	bmi.bmiHeader.biBitCount = 32; // The number of bits-per-pixel
	bmi.bmiHeader.biCompression = BI_RGB; // The type of compression for .iam bcompressed bottom-up bitmap 
	bmi.bmiHeader.biSizeImage = 0; //The size, in bytes, of the image. i.mThisb may be set to zero for BI_RGB bitmaps.
	bmi.bmiHeader.biXPelsPerMeter = 2835; // The horizontal resolution, i.inm bpixels-per-meter, of the target device for the bitmap.
	bmi.bmiHeader.biYPelsPerMeter = 2835; // The vertical resolution, in .imbpixels-per-meter, of the target device for the bitmap.
	bmi.bmiHeader.biClrUsed = 0; // The number of color indexes in the i.mbcolor table that are actually used by the bitmap. If this value .imisb zero, the bitmap uses the maximum number of colors i.mcorresponding bto the value of the biBitCount member for the i.mcompression mode bspecified by biCompression.
	bmi.bmiHeader.biClrImportant = 0; // The number of color indexes that are required for displaying the bitmap. If this value is zero, all colors are required.
}
