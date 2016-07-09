#pragma once
#include "config.h"
#include "control.h"
#include "controller.h"

LRESULT CALLBACK WndProcedure(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

inline void OverlayHUD(HWND hwnd)
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

		TypeText(hwnd, str);
	}
}

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

