#include "draw.h"
#include "types.h"
#include "config.h"
#include "my_math.h"
#include "draw_internal.h"

namespace DrawCommon
{
	void retroProjectVector(Vector<float, 4>& vec);
	void retroProjectVertex(Facef& current_vertex);
	void assignVertex(Facef& current_vertex, Model& model, unsigned int i);
	void RestoreZValue(Facef& current_vertex, float zValue[3]);
	void StashZValue(float zValue[3], Facef& current_vertex);
	void ndcToViewport(Facef& current_vertex);
	void SetPerspectiveProjectionSymmetrical(float l, float b, float n, float f);
	void SetPerspectiveProjection(float l, float r, float b, float t, float n, float f);
	void SetOrthoProjectionSymmetrical(float l, float b, float n, float f);
	void SetOrthoProjection(float l, float r, float b, float t, float n, float f);

	std::array<float, 16> GetFpsCameraView();

	bool isBetween(float value, float min = -1.f, float max = 1.f);
	bool isInRangeIndex(Facef vec, int index);
	bool isInRange(Facef vec);
	float calculateIntensity(Vector3f UW[2]);
	void setUWforCullingCalculation(Vector3f* UW, Facef current_vertex);
};

void DrawCommon::SetViewMatrix()
{
	config.ViewMatrix = IdentityMatrix<float, 16>();
	config.ViewMatrix = ArrayMultiplication(constructRotationMatrix<float>(config.camera.Rotation), config.ViewMatrix);
	config.ViewMatrix = ArrayMultiplication(constructTranslationMatrix<float>(config.camera.Origin), config.ViewMatrix);
	config.ViewMatrix = invertMatrix(config.ViewMatrix);
}

std::array<float, 16> DrawCommon::GetFpsCameraView()
{
	float pitch = config.camera.Rotation[0], yaw = config.camera.Rotation[1];
	Vector3f eye = {0,0,1};

	float cosPitch = cos(pitch);
	float sinPitch = sin(pitch);
	float cosYaw = cos(yaw);
	float sinYaw = sin(yaw);

	Vector3f xaxis = {cosYaw, 0, -sinYaw};
	Vector3f yaxis = {sinYaw * sinPitch, cosPitch, cosYaw * sinPitch};
	Vector3f zaxis = {sinYaw * cosPitch, -sinPitch, cosPitch * cosYaw};

	return {
		xaxis[0],xaxis[1],xaxis[2],-Vector3::DotProduct(xaxis, eye),
		yaxis[0],yaxis[1],yaxis[2],-Vector3::DotProduct(yaxis, eye),
		zaxis[0],zaxis[1],zaxis[2],-Vector3::DotProduct(zaxis, eye),
		0,0,0,1
	};
}

void DrawCommon::SetProjection()
{
	config.ProjectionMatrix = IdentityMatrix<float, 16>();
	if (config.Perspective)
	{
		float aspectRatio = float(config.bufferSize[0]) / float(config.bufferSize[1]);
		float f = config.camera.clipFar;
		float n = config.camera.clipNear;
		float b = -n * config.camera.getFov();
		float l = b * aspectRatio;
		DrawCommon::SetPerspectiveProjectionSymmetrical(l, b, n, f);
	}
	else
	{
		float l = -4.f, b = -4.f, f = config.camera.clipFar, n = config.camera.clipNear;
		DrawCommon::SetOrthoProjectionSymmetrical(l, b, n, f);
	}
}

void DrawCommon::SetPerspectiveProjectionSymmetrical(float l, float b, float n, float f)
{
	float r = -l;
	float t = -b;
	SetPerspectiveProjection(l, r, b, t, n, f);
}

void DrawCommon::SetPerspectiveProjection(float l, float r, float b, float t, float n, float f)
{
	config.ProjectionMatrix = {
		(2 * n) / (r - l),0,(r + l) / (r - l) ,0,
		0,(2 * n) / (t - b) ,(t + b) / (t - b) , 0,
		0,0,-(f + n) / (f - n),(-2 * f * n) / (f - n),
		0,0,-1,0
	};
}

void DrawCommon::SetOrthoProjectionSymmetrical(float l, float b, float n, float f)
{
	float r = -l;
	float t = -b;
	SetOrthoProjection(l, r, b, t, n, f);
}

void DrawCommon::SetOrthoProjection(float l, float r, float b, float t, float n, float f)
{
	config.ProjectionMatrix = {
		2 / (r - l), 0, 0, -(r + l) / (r - l),
		0, 2 / (t - b), 0, -(t + b) / (t - b),
		0, 0, -2 / (f - n), -(f + n) / (f - n),
		0, 0, 0, 1
	};
}

void DrawCommon::DrawModel(Model model)
{
	Facef currentVertex;
	Vector3f UW[2];
	float intensity;

	auto ModelMatrix = model.GetModelTransformationMatrix();
	auto ViewMatrix = config.ViewMatrix;
	auto ProjectionMatrix = config.ProjectionMatrix;

	auto MVP = IdentityMatrix<float, 16>();

	MVP = ArrayMultiplication(ModelMatrix, MVP);
	MVP = ArrayMultiplication(ViewMatrix, MVP);
	MVP = ArrayMultiplication(ProjectionMatrix, MVP);

	for (unsigned int currentFace = 0; currentFace < model.Face.size(); currentFace++)
	{
		DrawCommon::assignVertex(currentVertex, model, currentFace); // Assigning processed face a vertex

		transformFaceByArray(MVP, currentVertex);
		DrawCommon::setUWforCullingCalculation(UW, currentVertex);
		DrawCommon::retroProjectVertex(currentVertex); // Clip to NDC
		if (!isInRange(currentVertex)) continue;
		DrawCommon::ndcToViewport(currentVertex); // NDC to Window

		intensity = DrawCommon::calculateIntensity(UW);
		if (intensity < 0) intensity = 0;
		Color color = Color(static_cast<unsigned char>(floor(intensity * 255.f)));
		DrawInternal::DrawPolygon(currentVertex, color, config.getDrawMode());
	}
}

void DrawCommon::RestoreZValue(Facef& current_vertex, float zValue[3])
{
	for (int z = 0; z < 3; z++) current_vertex[z][2] = zValue[z];
}

void DrawCommon::StashZValue(float zValue[3], Facef& currentVertex) { for (int z = 0; z < 3; z++) zValue[z] = currentVertex[z][2]; }

void DrawCommon::ndcToViewport(Facef& current_vertex)
{
	for (int k = 0; k < 3; k++)
	{
		float w = float(config.bufferSize[0]), h = float(config.bufferSize[1]), x = 0, y = 0;
		current_vertex[k][0] = w / 2 * current_vertex[k][0] + (x + w / 2);
		current_vertex[k][1] = h - (h / 2 * current_vertex[k][1] + (y + h / 2));
	}
}

void DrawCommon::retroProjectVector(Vector<float, 4>& vec)
{
	vec[0] /= vec[3];
	vec[1] /= vec[3];
	vec[2] /= vec[3];
}

void DrawCommon::retroProjectVertex(Facef& current_vertex)
{
	for (int j = 0; j < 3; j++) DrawCommon::retroProjectVector(current_vertex[j]);
}

void DrawCommon::assignVertex(Facef& current_vertex, Model& model, unsigned int i)
{
	for (int j = 0; j < 3; j++)
	{
		current_vertex[j]({
			model.Vertex.at(model.Face.at(i)[j] - 1)[0],
			model.Vertex.at(model.Face.at(i)[j] - 1)[1],
			model.Vertex.at(model.Face.at(i)[j] - 1)[2],
			1.f
		});
	}
}

bool DrawCommon::isBetween(float value, float min, float max)
{
	return min <= value && value <= max;
}

bool DrawCommon::isInRangeIndex(Facef vec, int index)
{
	bool a, b, c;
	a = isBetween(vec[index][0]);
	b = isBetween(vec[index][1]);
	c = isBetween(vec[index][2]);
	return (a || b) && c;
}

bool DrawCommon::isInRange(Facef vec)
{
	bool a, b, c;
	a = isInRangeIndex(vec, 0);
	b = isInRangeIndex(vec, 1);
	c = isInRangeIndex(vec, 2);

	return a && b && c;
}

void DrawCommon::setUWforCullingCalculation(Vector3f* UW, Facef current_vertex)
{
	UW[0] = Vector4::toVector3(current_vertex[1]) - Vector4::toVector3(current_vertex[0]);
	UW[1] = Vector4::toVector3(current_vertex[2]) - Vector4::toVector3(current_vertex[0]);
}

float DrawCommon::calculateIntensity(Vector3f UW[2])
{
	return Vector3::DotProduct(
		Vector3::CrossProduct(UW[0], UW[1]).Normalize(),
		Vector3f({0.f,0.f,1.f})
	);
}
