#include "draw.h"
#include "types.h"
#include "config.h"
#include "mymath.h"

namespace DrawInternal {
	Vector<unsigned char, 3> _RandomPixelColor();
	void _PutPixel(Vector<int, 2> a, Vector<unsigned char, 3> color);
	void _PutPixelWithZBuffer(Vector<int, 2> a, Vector<unsigned char, 3> color, float zValue);
	void _DrawLine(Vector<int, 2> a, Vector<int, 2> b, Vector<unsigned char, 3> color);
	void _DrawPolygon(Vector<float, 3> p[3], Vector<unsigned char, 3> color = Vector<unsigned char, 3>({ 0,0,0 }), int drawMode = 0);
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

void DrawInternal::_PutPixel(Vector<int, 2> a, Vector<unsigned char, 3> color)
{
	// Out of bounds checking
	if (a[0] < 0 || a[1] < 0) return;
	if (a[0] >= config.bufferSize[0] || a[1] >= config.bufferSize[1]) return;

	int* buffer = static_cast<int*>(config.backbuffer);

	buffer += (a[1] * config.bufferSize[0]) + (a[0]);
	*buffer = (color[0] << 16) + (color[1] << 8) + (color[2]);
}

void DrawInternal::_PutPixelWithZBuffer(Vector<int, 2> a, Vector<unsigned char, 3> color, float zValue)
{
	// Out of bounds checking
	if (a[0] < 0 || a[1] < 0) return;
	if (a[0] >= config.bufferSize[0] || a[1] >= config.bufferSize[1]) return;

	float* zbuffer = static_cast<float*>(config.zbackbuffer);
	zbuffer += (a[1] * config.bufferSize[0]) + (a[0]);
	if (*zbuffer != 0 && *zbuffer < zValue) return;
	*zbuffer = zValue;

	int* buffer = static_cast<int*>(config.backbuffer);
	buffer += (a[1] * config.bufferSize[0]) + (a[0]);
	*buffer = (color[0] << 16) + (color[1] << 8) + (color[2]);
}

Vector<unsigned char, 3> DrawInternal::_RandomPixelColor()
{
	return Vector<unsigned char, 3>({ static_cast<unsigned char>(rand() % 0xff), static_cast<unsigned char>(rand() % 0xff), static_cast<unsigned char>(rand() % 0xff) });
}

void DrawInternal::_DrawLine(Vector<int, 2> a, Vector<int, 2> b, Vector<unsigned char, 3> color)
{
	if (b[1] < a[1]) std::swap(a, b); // Sort by y value

	int delta_x = b[0] - a[0]; //deltax==0 -> vertical
	int delta_y = b[1] - a[1]; //deltay==0 -> horizontal
	if (delta_x == 0 && delta_y == 0)
	{
		_PutPixel(a, color);
	}
	else if (delta_x == 0 || delta_y == 0)
	{
		int current_value;
		int target_value;
		int constant;
		if (delta_x == 0)
		{
			current_value = a[1];
			target_value = b[1];
			constant = a[0];
		}
		else
		{
			current_value = a[0];
			target_value = b[0];
			constant = a[1];
		}
		if (current_value > target_value) std::swap(current_value, target_value);
		Vector<int, 2> pixel;

		for (; current_value < target_value; current_value++)
		{
			if (delta_x == 0) pixel({ constant, current_value });
			else pixel({ current_value, constant });
			pixel({ pixel[0] - 1, pixel[1] - 1 });
			_PutPixel(pixel, color);
		}
		return;
	}

	float delta_error = static_cast<float>(delta_y) / static_cast<float>(delta_x); // real deltaerr : = abs(deltay / deltax)
	if (delta_error < 0.0) delta_error *= -1.0;
	float error = 0.0f;

	int current_y = a[1];

	for (int current_x = a[0]; current_x != b[0];)
	{
		_PutPixel(Vector<int, 2>({ current_x, current_y }), color);
		error += delta_error;
		while (error >= 0.5 && current_y != b[1])
		{
			_PutPixel(Vector<int, 2>({ current_x, current_y }), color);
			current_y++;
			error -= 1.0;
		}
		if (delta_x > 0) current_x++;
		else current_x--;
	}
}

void DrawInternal::_DrawPolygon(Vector<float, 3> input[3], Vector<unsigned char, 3> color, int drawMode)
{
	if (drawMode == 0)
	{
		Point2D::Structure point[3];
		for (int i = 0; i < 3; i++)
		{
			point[i].x = static_cast<int>(input[i][0]);
			point[i].y = static_cast<int>(input[i][1]);
		}

		// Bounding box
		int minX = static_cast<int>(fmin(point[0].x, fmin(point[1].x, point[2].x)));
		int maxX = static_cast<int>(fmax(point[0].x, fmax(point[1].x, point[2].x)));
		int minY = static_cast<int>(fmin(point[0].y, fmin(point[1].y, point[2].y)));
		int maxY = static_cast<int>(fmax(point[0].y, fmax(point[1].y, point[2].y)));

		Point2D::Structure p;

		Point2D::Structure vs1 = Point2D::Structure(point[1].x - point[0].x, point[1].y - point[0].y);
		Point2D::Structure vs2 = Point2D::Structure(point[2].x - point[0].x, point[2].y - point[0].y);

		for (p.x = minX; p.x <= maxX; p.x++)
		{
			for (p.y = minY; p.y <= maxY; p.y++)
			{
				Point2D::Structure q = Point2D::Structure(p.x - point[0].x, p.y - point[0].y);

				float s = Point2D::CrossProduct(q, vs2) / Point2D::CrossProduct(vs1, vs2);
				float t = Point2D::CrossProduct(vs1, q) / Point2D::CrossProduct(vs1, vs2);

				if ((s >= 0) && (t >= 0) && (s + t <= 1))
				{
					float zValue = (1 - s - t)*input[0][2] + s*input[1][2] + t*input[2][2];
					_PutPixelWithZBuffer(Vector<int, 2>({ p.x,p.y }), color, zValue);
				}
			}
		}
	}
	else {
		Vector<int, 2> VerticiesIn2D[3];
		VerticiesIn2D[0] = Vector<int, 2>({ (int)input[0][0], (int)input[0][1] });
		VerticiesIn2D[1] = Vector<int, 2>({ (int)input[1][0], (int)input[1][1] });
		VerticiesIn2D[2] = Vector<int, 2>({ (int)input[2][0], (int)input[2][1] });

		_DrawLine(VerticiesIn2D[0], VerticiesIn2D[1], Vector<unsigned char, 3>({ 0, 0xff, 0 }));
		_DrawLine(VerticiesIn2D[1], VerticiesIn2D[2], Vector<unsigned char, 3>({ 0, 0xff, 0 }));
		_DrawLine(VerticiesIn2D[2], VerticiesIn2D[0], Vector<unsigned char, 3>({ 0xff, 0, 0 }));
	}
}