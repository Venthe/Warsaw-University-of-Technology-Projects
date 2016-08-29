#include <array>
#include "mymath.h"
#include "config.h"
#include "draw.h"
#include "object_handler.h"
#include "draw_internal.h"
#include "main.h"

void _LookAtNothing(Vector<float, 3> up = Vector3::Up<float>(), Vector<float, 3> cameraOrigin = config.camera.Origin);
void _LookAt(Vector<float, 3> lookat = Vector<float, 3>(), Vector<float, 3> up = Vector3::Up<float>(), Vector<float, 3> cameraOrigin = config.camera.Origin);

void DrawCommon::SetProjection(float fov, float aspectW, float aspectH, float clippingNear, float clippingFar)
{
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

void DrawCommon::LookAt(Vector<float, 3> up, Vector<float, 3> cameraOrigin)
{
	if (config.LookAt) _LookAt(Vector<float, 3>(), up, cameraOrigin);
	else _LookAtNothing(up, cameraOrigin);
}

void DrawCommon::SetViewport(int x, int y, int w, int h)
{
	config.ViewportMatrix = MyMath::IdentityMatrix<float, 16>();

	float depth = 256.f;

	config.ViewportMatrix[0 * 4 + 3] = x + (w / 2.f);
	config.ViewportMatrix[1 * 4 + 3] = y + (h / 2.f);
	config.ViewportMatrix[2 * 4 + 3] = depth / 2.f;

	config.ViewportMatrix[0 * 4 + 0] = w / 2.f;
	config.ViewportMatrix[1 * 4 + 1] = h / 2.f;
	config.ViewportMatrix[2 * 4 + 2] = depth / 2.f;
}

bool isVertexWithinBoundaries(Vector<float, 3> v)
{
	if (v[2] < config.clipNear || v[2] > config.clipFar)
	{
		return false;
	}
	else if ((v[0] > config.bufferSize[0] || v[0] < 0) && ((v[1] > config.bufferSize[1] || v[1] < 0)))
	{
		return false;
	}
	return true;
}

void DrawCommon::DrawModel(Model model, bool fill_polygon)
{
	Vector<float, 3> current_vertex[3];

	for (unsigned int i = 0; i < model.Face.size(); i++)
	{
		bool qualified = false;
		// Assigning processed face a vertcies, which in turn are placed in temp
		for (int j = 0; j < 3; j++) {
			current_vertex[j]({
				model.Vertex.at(model.Face.at(i)[j] - 1)[0],
				model.Vertex.at(model.Face.at(i)[j] - 1)[1],
				model.Vertex.at(model.Face.at(i)[j] - 1)[2]
			});

			MyMath::transformVectorByArray(model.GetModelTransformationMatrix(), current_vertex[j]);
			MyMath::transformVectorByArray(config.ViewMatrix, current_vertex[j]);
			MyMath::transformVectorByArray(config.ProjectionMatrix, current_vertex[j], config.Perspective);
			MyMath::transformVectorByArray(config.ViewportMatrix, current_vertex[j]);

			if (!qualified) qualified = isVertexWithinBoundaries(current_vertex[j]);
		}
		if (!qualified) continue;

		if (!fill_polygon) { DrawInternal::_DrawPolygon(current_vertex); }
		else {
			//Calculating normal for the color fill
			Vector<float, 3> U = current_vertex[1] - current_vertex[0];
			Vector<float, 3> W = current_vertex[2] - current_vertex[0];
			Vector<float, 3> normal = Vector3::CrossProduct(U, W).Normalize();
			float intensity = Vector3::DotProduct(normal, Vector<float, 3>({ 0.f,0.f,1.f }));

			if (intensity > 0) {
				Vector<unsigned char, 3> color = Vector<unsigned char, 3>(static_cast<unsigned char>(round(intensity*256.f) - 1));
				DrawInternal::_DrawPolygon(current_vertex, color, fill_polygon); // Fill Polygon
			}
		}


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
