#include <iostream>
#include "main.h"
#include "config.h"
#include "platform_specific.h"
#include "draw.h"
#include "object_handler.h"
#include "draw_window_elements.h"
#include "draw_internal.h"

#ifdef _WIN32
#include <windows.h>
#include "window.h"

_CONFIG config;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) // HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow
{
	config = _CONFIG(800, 600);

	_WINDOW wnd = _WINDOW(hInstance, "Main Window");

	if (wnd.isInitialized())
	{
		//load file
		Model teapot((std::string(config.CurrentDirectory) + std::string("\\teapot.obj")).c_str(), Vector<float, 3>({ -0.0f, 0.0f, 0.0f }), Vector<float, 3>({ 0, 0, 0 }), Vector<float, 3>({ .2f, -.2f, .2f }));
		Model ball((std::string(config.CurrentDirectory) + std::string("\\center.obj")).c_str(), Vector<float, 3>(), Vector<float, 3>(), Vector<float, 3>({ .1f,.1f,.1f }));

		DrawCommon::SetViewport();
		while (GetMessage(&wnd.msg, nullptr, 0, 0))
		{
			// Message handling
			TranslateMessage(&wnd.msg);
			DispatchMessage(&wnd.msg);

			//Background
			DrawWindowElements::ClearZBuffer();
			DrawWindowElements::FillRectangle(Vector<unsigned char, 3>({ 70,70,70 }));
			DrawWindowElements::DrawGrid();

			//Setting visual and camera
			DrawCommon::SetProjection();
			DrawCommon::LookAt();

			//Drawing models
			DrawCommon::DrawModel(teapot); //Drawing Teapot

			//Drawing balls
			for (int i = 0; i < 4; i++)
			{
				ball.Origin({ 4., 0., -i * 5.f });
				DrawCommon::DrawModel(ball);
				ball.Origin({ -4., 0., -i * 5.f });
				DrawCommon::DrawModel(ball);
			}

			Draw(wnd.hwndMain);
			OverlayHUD(wnd.hwndMain);
		}
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

#endif // _WIN32