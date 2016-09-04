#include "draw.h"
#include "types.h"
#include "config.h"
#include "mymath.h"
#include "draw_internal.h"

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

void DrawCommon::LookAt(Vector<float, 3> up, Vector<float, 3> cameraOrigin)
{
	if (config.LookAt) _LookAt(Vector<float, 3>(), up, cameraOrigin);
	else _LookAtNothing(up, cameraOrigin);
}

void DrawCommon::SetProjection(float fov, float aspectW, float aspectH, float clippingNear, float clippingFar)
{
	bool perspective = true;
	float aspectRatio = aspectW / aspectH;
	float right = clippingNear * tanf(MyMath::DegreesToRadians(fov) * 0.5f);
	float top = right / aspectRatio;
	float clippingDistance = (clippingFar - clippingNear);

	if (perspective) {
		// first column
		config.ProjectionMatrix[0] = clippingNear / right;
		config.ProjectionMatrix[1] = 0.0f;
		config.ProjectionMatrix[2] = 0.0f;
		config.ProjectionMatrix[3] = 0.0f;

		// second column
		config.ProjectionMatrix[4] = 0.0f;
		config.ProjectionMatrix[5] = clippingNear / top;
		config.ProjectionMatrix[6] = 0.0f;
		config.ProjectionMatrix[7] = 0.0f;

		// third column
		config.ProjectionMatrix[8] = 0.f;
		config.ProjectionMatrix[9] = 0.f;
		config.ProjectionMatrix[10] = -(clippingFar + clippingNear) / clippingDistance;
		config.ProjectionMatrix[11] = -1.0f;

		// fourth column
		config.ProjectionMatrix[12] = 0.0f;
		config.ProjectionMatrix[13] = 0.0f;
		config.ProjectionMatrix[14] = -(2 * clippingFar * clippingNear) / clippingDistance;
		config.ProjectionMatrix[15] = 0.0f;
	}
	else {
		// first column
		config.ProjectionMatrix[0] = 1.0f / right;
		config.ProjectionMatrix[1] = 0.0f;
		config.ProjectionMatrix[2] = 0.0f;
		config.ProjectionMatrix[3] = 0.0f;

		// second column
		config.ProjectionMatrix[4] = 0.0f;
		config.ProjectionMatrix[5] = 1.0f / top;
		config.ProjectionMatrix[6] = 0.0f;
		config.ProjectionMatrix[7] = 0.0f;

		// third column
		config.ProjectionMatrix[8] = 0.0f;
		config.ProjectionMatrix[9] = 0.0f;
		config.ProjectionMatrix[10] = -2.0f / clippingDistance;
		config.ProjectionMatrix[11] = 0.0f;

		// fourth column
		config.ProjectionMatrix[12] = 0.f;
		config.ProjectionMatrix[13] = 0.f;
		config.ProjectionMatrix[14] = -(clippingFar + clippingNear) / clippingDistance;
		config.ProjectionMatrix[15] = 1.0f;
	}
}

void DrawCommon::SetViewport(int x, int y, int w, int h)
{
	config.ViewportMatrix = MyMath::IdentityMatrix<float, 16>();

	float depth = config.clipFar - config.clipNear;

	config.ViewportMatrix[0 * 4 + 3] = x + (w / 2.f);
	config.ViewportMatrix[1 * 4 + 3] = y + (h / 2.f);
	config.ViewportMatrix[2 * 4 + 3] = depth / 2.f;

	config.ViewportMatrix[0 * 4 + 0] = w / 2.f;
	config.ViewportMatrix[1 * 4 + 1] = h / 2.f;
	config.ViewportMatrix[2 * 4 + 2] = depth / 2.f;
}

void DrawCommon::DrawModel(Model model)
{
	Vector<float, 3> current_vertex[3];

	for (unsigned int i = 0; i < model.Face.size(); i++)
	{
		bool isWithinDrawDistance[3] = { false,false, false };

		// Assigning processed face a vertcies, which in turn are placed in temp
		for (int j = 0; j < 3; j++) {
			current_vertex[j]({
				model.Vertex.at(model.Face.at(i)[j] - 1)[0],
				model.Vertex.at(model.Face.at(i)[j] - 1)[1],
				model.Vertex.at(model.Face.at(i)[j] - 1)[2]
			});

			MyMath::transformVectorByArray(model.GetModelTransformationMatrix(), current_vertex[j]);
			MyMath::transformVectorByArray(config.ViewMatrix, current_vertex[j]);
		}

		Vector<float, 3> U = current_vertex[1] - current_vertex[0];
		Vector<float, 3> W = current_vertex[2] - current_vertex[0];

		for (int j = 0; j < 3; j++) {
			isWithinDrawDistance[j] = MyMath::transformVectorByArray(config.ProjectionMatrix, current_vertex[j], config.Perspective);
			MyMath::transformVectorByArray(config.ViewportMatrix, current_vertex[j]);
		}

		if (!isWithinDrawDistance[0] || !isWithinDrawDistance[1] || !isWithinDrawDistance[2]) continue;

		Vector<float, 3> normal = Vector3::CrossProduct(U, W).Normalize();
		float intensity = Vector3::DotProduct(normal, Vector<float, 3>({ 0.f,0.f,-1.f }));

		if (intensity > 0) {
			Vector<unsigned char, 3> color = Vector<unsigned char, 3>(static_cast<unsigned char>(round(intensity*256.f)) - 1);
			DrawInternal::_DrawPolygon(current_vertex, color, config.getDrawMode());
		}
	}
}
