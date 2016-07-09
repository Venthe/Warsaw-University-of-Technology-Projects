#include <array>
#include "mymath.h"
#include "config.h"
#include "draw.h"
#include "object_handler.h"
#include "draw_commons.h"

void _LookAtNothing(Vector<float, 3> up = Vector3::Up<float>(), Vector<float, 3> cameraOrigin = config.camera.Origin);
void _LookAt(Vector<float, 3> lookat = Vector<float, 3>(), Vector<float, 3> up = Vector3::Up<float>(), Vector<float, 3> cameraOrigin = config.camera.Origin);

void Projection(float fov, float aspectW, float aspectH, float clippingNear, float clippingFar)
{
	config.ProjectionMatrix = MyMath::IdentityMatrix<float, 16>();
	float aspectRatio = aspectW / aspectH;

	float yScale = 1.0f / tanf(MyMath::DegreesToRadians(fov) / 2.f);
	float xScale = yScale / aspectRatio;
	float clippingDistance = clippingNear - clippingFar;

	config.ProjectionMatrix[0] = xScale;
	config.ProjectionMatrix[5] = yScale;
	config.ProjectionMatrix[10] = (clippingFar + clippingNear) / clippingDistance;
	config.ProjectionMatrix[11] = -1;
	config.ProjectionMatrix[14] = (2 * clippingFar * clippingNear) / clippingDistance;
}

void LookAt(Vector<float, 3> up, Vector<float, 3> cameraOrigin)
{
	if (config.LookAt) _LookAt(Vector<float, 3>(), up, cameraOrigin);
	else _LookAtNothing(up, cameraOrigin);
}

void Viewport(int x, int y, int w, int h)
{
	config.ViewportMatrix = MyMath::IdentityMatrix<float, 16>();

	//float depth = 256.f;

	config.ViewportMatrix[0 * 4 + 3] = x + w / 2.f;
	config.ViewportMatrix[1 * 4 + 3] = y + h / 2.f;

	config.ViewportMatrix[0 * 4 + 0] = w / 2.f;
	config.ViewportMatrix[1 * 4 + 1] = h / 2.f;

	//if (!config.Perspective) config.ViewportMatrix[2 * 4 + 3] = depth / 2.f;
}

void DrawModel(Model model, bool fill_polygon)
{
	Vector<float, 3> current_vertex[3];
	int doNotDraw = 0;
	Vector<int, 2> triangle[3];

	for (unsigned int i = 0; i < model.Face.size(); i++ , doNotDraw = 0)
	{
		for (int j = 0; j < 3; j++) current_vertex[j]({model.Vertex.at(model.Face.at(i)[j] - 1)[0], model.Vertex.at(model.Face.at(i)[j] - 1)[1], model.Vertex.at(model.Face.at(i)[j] - 1)[2]});

		//View with perspective
		for (int j = 0; j < 3; j++)
		{
			MyMath::transformVectorByArray(model.GetModelMatrix(), current_vertex[j]);
			MyMath::transformVectorByArray(config.ViewMatrix, current_vertex[j]);
			if (config.Perspective)
				if (MyMath::transformVectorByArray(config.ProjectionMatrix, current_vertex[j], true) == 1) doNotDraw++;
			MyMath::transformVectorByArray(config.ViewportMatrix, current_vertex[j]);
		}

		if (doNotDraw == 3 && config.Perspective) continue;

		doNotDraw = 0;
		for (int j = 0; j < 3; j++)
		{
			if (current_vertex[j][2] < config.camera.Origin[2]) doNotDraw++;
			triangle[j] = Vector<int, 2>({static_cast<int>(current_vertex[j][0]), static_cast<int>(current_vertex[j][1])});
		}

		if (doNotDraw == 3 && config.Perspective) continue;
		_DrawPolygon(triangle, Vector<unsigned char, 3>(), fill_polygon);
	}
}

void _LookAt(Vector<float, 3> lookat, Vector<float, 3> up, Vector<float, 3> cameraOrigin)
{
	config.ViewMatrix = MyMath::IdentityMatrix<float, 16>();

	Vector<float, 3> z = (cameraOrigin - lookat).Normalize();
	Vector<float, 3> x = Vector3::CrossProduct(up, z).Normalize();
	Vector<float, 3> y = Vector3::CrossProduct(z, x).Normalize();
	auto M = MyMath::IdentityMatrix<float, 16>();
	auto T = MyMath::IdentityMatrix<float, 16>();
	for (int i = 0; i < 3; i++)
	{
		M[0 * 4 + i] = x[i];
		M[1 * 4 + i] = y[i];
		M[2 * 4 + i] = z[i];
		T[i * 4 + 3] = -lookat[i];
	}

	config.ViewMatrix = MyMath::ArrayMultiplication(M, T);
	config.ViewMatrix = MyMath::ArrayMultiplication(config.ViewMatrix, MyMath::TranslateMatrix<float, 16>(
		                                                (-1.) * config.camera.Origin
	                                                ));
}

void _LookAtNothing(Vector<float, 3>, Vector<float, 3>)
{
	config.ViewMatrix = MyMath::IdentityMatrix<float, 16>();
	config.ViewMatrix = MyMath::ArrayMultiplication(config.ViewMatrix, MyMath::RotateMatrix<float, 16>(config.camera.Rotation));
	config.camera.Origin[0] *= -1.;
	config.ViewMatrix = MyMath::ArrayMultiplication(config.ViewMatrix, MyMath::TranslateMatrix<float, 16>(config.camera.Origin));
	config.camera.Origin[0] *= -1.;
}

