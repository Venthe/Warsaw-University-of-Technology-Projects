#include <windows.h>
#include "Main.h"
#include "window.h"
#include "draw_window_elements.h"
#include "controller.h"
#include "color.h"

void drawBalls(Model ball)
{
	//Drawing balls
	for (int currentBall = 0; currentBall < 4; currentBall++)
	{
		float scale = 0.5f - float(currentBall) / 10;
		ball.Scale({scale,scale, scale});
		ball.Origin({1.f - float(currentBall / 2), 0.f, -currentBall * 3.f});
		DrawCommon::DrawModel(ball);
		ball.Origin({-1.f, 0.f + float(currentBall), -currentBall * 3.f});
		DrawCommon::DrawModel(ball);
	}
}

void drawTeapot(Model teapot, float rotOfTeapot[3])
{
	teapot.Rotation = {rotOfTeapot[0] += 1.0f,rotOfTeapot[1] += 3.0f,rotOfTeapot[2] += 5.0f};
	if (rotOfTeapot[0] > 360.f) rotOfTeapot[0] = 0.f;
	if (rotOfTeapot[1] > 360.f) rotOfTeapot[1] = 0.f;
	if (rotOfTeapot[2] > 360.f) rotOfTeapot[2] = 0.f;
	DrawCommon::DrawModel(teapot); //Drawing Teapot
}

std::string getFilenameFromCurrentDirectory(std::string filename) { return std::string(config.CurrentDirectory) + "\\" + filename; }

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) // HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow
{
	config = _CONFIG(1024, 768, {0.0f,1.2f,10.f}, {}, 60.f, 0.01f, 40.f);
	_WINDOW wnd = _WINDOW(hInstance, "Main Window");

	if (wnd.isInitialized())
	{
		//load file
		Model teapot(getFilenameFromCurrentDirectory("teapot.obj"), {0,3,1}, {}, {.5f, .5f, .5f});
		Model ball(getFilenameFromCurrentDirectory("sphere.obj"), {}, {}, {.8f,.8f,.8f});

		float rotOfTeapot[3] = {0.0f, 0.0f, 0.0f};
		while (true)
		{
			while (PeekMessage(&wnd.msg, nullptr, 0, 0, PM_REMOVE) > 0)
			{
				TranslateMessage(&wnd.msg);
				DispatchMessage(&wnd.msg);
			}

			//Background
			DrawWindowElements::ClearZBuffer();
			DrawWindowElements::FillRectangle(MyColor::LIGHTBLUE);
			//DrawWindowElements::DrawGrid(32, MyColor::BLACK);

			//Setting visual and camera
			DrawCommon::SetProjection();
			DrawCommon::SetViewMatrix();

			//Drawing models
			drawTeapot(teapot, rotOfTeapot);
			drawBalls(ball);

			DrawMyWindow(wnd.hwndMain);
			Controller::OverlayHUD(wnd.hwndMain);

			Sleep(20);
			if (wnd.msg.message == WM_QUIT) return EXIT_SUCCESS;
		}
	}
	return EXIT_FAILURE;
}
