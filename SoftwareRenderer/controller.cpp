#include "controller.h"
#include "config.h"
#include "window.h"

void Controller::Keymap(WPARAM wParam)
{
	switch (wParam)
	{
		//Focal length
	case 'Z': config.camera.ShiftFocalLength(2.5);
		break;
	case 'X': config.camera.ShiftFocalLength(-2.5);
		break;
		//Translation
	case 'A': config.camera.ShiftLocation(Vector<float, 3>({ -0.2f,0,0 }));
		break;
	case 'D': config.camera.ShiftLocation(Vector<float, 3>({ 0.2f,0,0 }));
		break;
	case 'E': config.camera.ShiftLocation(Vector<float, 3>({ 0,0.2f,0 }));
		break;
	case 'Q': config.camera.ShiftLocation(Vector<float, 3>({ 0,-0.2f,0 }));
		break;
	case 'W': config.camera.ShiftLocation(Vector<float, 3>({ 0,0,0.2f }));
		break;
	case 'S': config.camera.ShiftLocation(Vector<float, 3>({ 0,0,-0.2f }));
		break;
		//Pitch, Yaw,Roll
	case 'Y': config.camera.ShiftRotation(Vector<float, 3>({ -2.5f, 0, 0 }));
		break;
	case 'U': config.camera.ShiftRotation(Vector<float, 3>({ 2.5f, 0, 0 }));
		break;
	case 'H': config.camera.ShiftRotation(Vector<float, 3>({ 0, 2.5f, 0 }));
		break;
	case 'J': config.camera.ShiftRotation(Vector<float, 3>({ 0, -2.5f, 0 }));
		break;
	case 'N': config.camera.ShiftRotation(Vector<float, 3>({ 0, 0, 2.5f }));
		break;
	case 'M': config.camera.ShiftRotation(Vector<float, 3>({ 0, 0, -2.5f }));
		break;
		//Misc
	case 'R': //Reset camera
		config.camera = config.defaultCamera;
		break;
	case 'C': //change camera
		config.changeHudDisplay();
		break;
	case 'F':
		config.changeDrawMode();
	default: break;
	}
}

void Controller::OverlayHUD(HWND hwnd)
{
	if (!config.hideHUD)
	{
		//Overlaying data
		std::string str = "Camera:\no:" + config.camera.Origin.ToString() + "\nr:" + config.camera.Rotation.ToString() + "\nCamera focal length: " + std::to_string(config.camera.FocalLength);
		//if (config.LookAt) str.append("\n").append("Looking at center");
		//else str.append("\n").append("Looking in front");
		//if (config.Perspective) str.append("\n").append("Perspective");
		//else str.append("\n").append("Ortho");

		//Keybindings
		str.append("\n");

		//Focal length
		str.append("\n").append("Z: Increase Focal Length");
		str.append("\n").append("X: Decrease Focal Length");

		//Translation
		str.append("\n").append("A: Translate X decrease");
		str.append("\n").append("D: Translate X increase");
		str.append("\n").append("Q: Translate Y decrease");
		str.append("\n").append("E: Translate Y increase");
		str.append("\n").append("W: Translate Z increase");
		str.append("\n").append("S: Translate Z decrease");
		//Pitch, Yaw,Roll
		str.append("\n").append("Y: Rotate X decrease");
		str.append("\n").append("U: Rotate X increase");
		str.append("\n").append("H: Rotate Y increase");
		str.append("\n").append("J: Rotate Y decrease");
		str.append("\n").append("N: Rotate Z increase");
		str.append("\n").append("M: Rotate Z decrease");

		//Misc
		str.append("\n").append("R: Reset camera");
		str.append("\n").append("C: Hide the HUD: ").append(std::to_string(config.hideHUD));
		str.append("\n").append("F: Change drawing mode, current: ").append(std::to_string(config.getDrawMode()));

		TypeText(hwnd, str);
	}
}