#include <windows.h>
#include "config.h"
#include "types.h"
#include "window.h"
#include "object_handler.h"
#include "draw.h"
#include "draw_window_elements.h"
#include "controller.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) // HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow
{
	config = _CONFIG(800, 600, Vector<float, 3>({ -0.0f,0.2f,-2.6f }), Vector<float, 3>(), 100.f, 0.15f, 50.f);
	_WINDOW wnd = _WINDOW(hInstance, "Main Window");

	if (wnd.isInitialized())
	{
		//load file
		Model teapot((std::string(config.CurrentDirectory) + std::string("\\teapot.obj")).c_str(), Vector<float, 3>({ -0.0f, 0.0f, 0.0f }), Vector<float, 3>({ 0, 0, 0 }), Vector<float, 3>({ .2f, -.2f, .2f }));
		Model ball((std::string(config.CurrentDirectory) + std::string("\\sphere.obj")).c_str(), Vector<float, 3>(), Vector<float, 3>(), Vector<float, 3>({ .1f,.1f,.1f }));

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

			DrawMyWindow(wnd.hwndMain);
			Controller::OverlayHUD(wnd.hwndMain);
		}
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}
