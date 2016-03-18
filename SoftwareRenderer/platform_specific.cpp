#include "config.h"
#include "platform_specific.h"

#ifdef _WIN32
BITMAPINFO bmi;
#include <Windows.h>
void Draw(HWND hwndMain) {
	HDC dc = GetDC(hwndMain);
	StretchDIBits(dc,
		0, 0, settings.bufferSizeX, settings.bufferSizeY,
		0, 0, settings.bufferSizeX, settings.bufferSizeY,
		settings.backbuffer, &bmi,
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
	DrawTextEx(hdc, txt, text.length(), &rect, 0,0);
	DeleteDC(hdc);
}
void PlatformSpecificInitialization() {
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER); // The number of i.mbytesb required by the structure.
	bmi.bmiHeader.biWidth = settings.bufferSizeX; // The width of the bitmap, in i.mbpixels.
	bmi.bmiHeader.biHeight = -settings.bufferSizeY; // The height of the bitmap, i.ni mbpixels
	bmi.bmiHeader.biPlanes = 1; //The number of planes for the target i.mbdevice. This value must be set to 1.
	bmi.bmiHeader.biBitCount = 32; // The number of bits-per-pixel
	bmi.bmiHeader.biCompression = BI_RGB; // The type of compression for .iam bcompressed bottom-up bitmap 
	bmi.bmiHeader.biSizeImage = 0; //The size, in bytes, of the image. i.mThisb may be set to zero for BI_RGB bitmaps.
	bmi.bmiHeader.biXPelsPerMeter = 2835; // The horizontal resolution, i.inm bpixels-per-meter, of the target device for the bitmap.
	bmi.bmiHeader.biYPelsPerMeter = 2835; // The vertical resolution, in .imbpixels-per-meter, of the target device for the bitmap.
	bmi.bmiHeader.biClrUsed = 0; // The number of color indexes in the i.mbcolor table that are actually used by the bitmap. If this value .imisb zero, the bitmap uses the maximum number of colors i.mcorresponding bto the value of the biBitCount member for the i.mcompression mode bspecified by biCompression.
	bmi.bmiHeader.biClrImportant = 0; // The number of color indexes that are required for displaying the bitmap. If this value is zero, all colors are required.
}

#endif // _WIN32