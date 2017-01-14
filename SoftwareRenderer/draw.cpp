#include "draw.h"
#include "types.h"
#include "config.h"
#include "mymath.h"
#include "draw_internal.h"

void DrawCommon::LookAt(Vector<float, 3> up, Vector<float, 3> cameraOrigin)
{
	config.ViewMatrix = MyMath::IdentityMatrix<float, 16>();
	config.ViewMatrix = MyMath::ArrayMultiplication(config.ViewMatrix, MyMath::RotateMatrix<float, 16>(config.camera.Rotation));
	config.ViewMatrix = MyMath::ArrayMultiplication(config.ViewMatrix, MyMath::TranslateMatrix<float, 16>(config.camera.Origin));
}

void DrawCommon::SetProjection(float fov, float aspectW, float aspectH, float clippingNear, float clippingFar)
{
	float aspectRatio = aspectW / aspectH;
	float right = clippingNear * tanf(MyMath::DegreesToRadians(fov) * 0.5f);
	float top = right / aspectRatio;
	float clippingDistance = (clippingFar - clippingNear);
		// first column
		config.ProjectionMatrix[0] = clippingNear / right;
		config.ProjectionMatrix[4] = 0.0f;
		config.ProjectionMatrix[8] = 0.0f;
		config.ProjectionMatrix[12] = 0.0f;

		// second column
		config.ProjectionMatrix[1] = 0.0f;
		config.ProjectionMatrix[5] = clippingNear / top;
		config.ProjectionMatrix[9] = 0.0f;
		config.ProjectionMatrix[13] = 0.0f;

		// third column
		config.ProjectionMatrix[2] = 0.f;
		config.ProjectionMatrix[6] = 0.f;
		config.ProjectionMatrix[10] = -(clippingFar + clippingNear) / clippingDistance;
		config.ProjectionMatrix[14] = -1.0f;

		// fourth column
		config.ProjectionMatrix[3] = 0.0f;
		config.ProjectionMatrix[7] = 0.0f;
		config.ProjectionMatrix[11] = -(2 * clippingFar * clippingNear) / clippingDistance;
		config.ProjectionMatrix[15] = 0.0f;
	
}

void DrawCommon::SetViewport(int x, int y, int w, int h)
{
	config.ViewportMatrix = MyMath::IdentityMatrix<float, 16>();

	float depth = config.camera.clipFar - config.camera.clipNear;

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