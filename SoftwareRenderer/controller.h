#pragma once
#include "config.h"

inline void Controller(WPARAM wParam)
{
	switch (wParam)
	{
		//Focal length
	case 'Z': config.camera.ShiftFocalLength(2.5);
		break;
	case 'X': config.camera.ShiftFocalLength(-2.5);
		break;
		//Translation
	case 'A': config.camera.ShiftLocation(Vector<float, 3>({-0.2f,0,0}));
		break;
	case 'D': config.camera.ShiftLocation(Vector<float, 3>({0.2f,0,0}));
		break;
	case 'W': config.camera.ShiftLocation(Vector<float, 3>({0,0.2f,0}));
		break;
	case 'S': config.camera.ShiftLocation(Vector<float, 3>({0,-0.2f,0}));
		break;
	case 'Q': config.camera.ShiftLocation(Vector<float, 3>({0,0,0.2f}));
		break;
	case 'E': config.camera.ShiftLocation(Vector<float, 3>({0,0,-0.2f}));
		break;
		//Pitch, Yaw,Roll
	case 'Y': config.camera.ShiftRotation(Vector<float, 3>({-2.5f, 0, 0}));
		break;
	case 'U': config.camera.ShiftRotation(Vector<float, 3>({2.5f, 0, 0}));
		break;
	case 'H': config.camera.ShiftRotation(Vector<float, 3>({0, 2.5f, 0}));
		break;
	case 'J': config.camera.ShiftRotation(Vector<float, 3>({0, -2.5f, 0}));
		break;
	case 'N': config.camera.ShiftRotation(Vector<float, 3>({0, 0, 2.5f}));
		break;
	case 'M': config.camera.ShiftRotation(Vector<float, 3>({0, 0, -2.5f}));
		break;
		//Misc
	case 'F': //Perspective camera
		if (config.Perspective == false)
		{
			config.Perspective = true;
		}
		else
		{
			config.Perspective = false;
		}
		break;
	case 'R': //Reset camera
		config.camera = config.defaultCamera;
		break;
	case 'T': //change camera pointing method
		if (config.LookAt == false)
		{
			config.LookAt = true;
		}
		else
		{
			config.LookAt = false;
		}
		break;
	case 'C': //change camera pointing method
		if (config.hideHUD == false)
		{
			config.hideHUD = true;
		}
		else
		{
			config.hideHUD = false;
		}
		break;
	default: break;
	}
}

