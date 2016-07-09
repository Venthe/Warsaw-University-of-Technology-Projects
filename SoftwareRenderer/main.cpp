#include <iostream>
#include "config.h"
#include "platform_specific.h"
#include "draw.h"
#include "object_handler.h"

#ifdef _WIN32
#include <windows.h>
#include "window.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) // HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow
{
	SetSettings(1024, 768);
	_WINDOW wnd = _WINDOW(hInstance, "Main Window");

	if (wnd.isInitialized()) {
		Viewport();

		//load file
		//TODO: Model name from command line?
		Model object((std::string(config.CurrentDirectory) + std::string("\\teapot.obj")).c_str(), Vector<double, 3>({ -3, 2, 1.5 }), Vector<double, 3>({ 50, 0, 0 }), Vector<double, 3>({ .1, -.1, .1 }));
		Model ball((std::string(config.CurrentDirectory) + std::string("\\center.obj")).c_str(), Vector<double, 3>(), Vector<double, 3>(), Vector<double, 3>({ .1,.1,.1 }));
		Model grid((std::string(config.CurrentDirectory) + std::string("\\grid.obj")).c_str(), Vector<double, 3>(), Vector<double, 3>(), Vector<double, 3>({ .1, .1, .1 }));

		config.camera.Origin[2] = -1.5;

		while (GetMessage(&wnd.msg, nullptr, 0, 0))
		{
			// Message handling
			TranslateMessage(&wnd.msg);
			DispatchMessage(&wnd.msg);

			//Background
			FillRect(Vector<unsigned char, 3>({ 70,70,70 }));
			DrawGrid();

			//Setting visual and camera
			Projection();
			LookAt();

			DrawModel(object); //Drawing Teapot

			//Drawing balls
			for (int i = 0; i < 4; i++)
			{
				ball.Origin({ 4., 0., -i * 5. });
				DrawModel(ball);
				ball.Origin({ -4., 0., -i * 5. });
				DrawModel(ball);
			}

			//DrawingGrid
			for (int j = 0, a = 36, b = 36; j < a; j++)
			{
				for (int k = 0; k < b; k++)
				{
					grid.Origin({ -static_cast<double>(b / 2) + k, 0., -static_cast<double>(a / 2) + j });
					DrawModel(grid);
				}
			}

			Draw(wnd.hwndMain);
			OverlayHUD(wnd.hwndMain);
		}
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

#endif // _WIN32


