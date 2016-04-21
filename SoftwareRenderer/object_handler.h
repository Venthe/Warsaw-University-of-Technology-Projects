#pragma once
#include <vector>
#include "types.h"

#define M_PI 3.14159

class ObjectData
{
public:
	Vector3<double> Origin = Vector3<double>(0.0, 0.0, 0.0);
	Vector3<double> Rotation = Vector3<double>(0.0, 0.0, 0.0);
	Vector3<double> Scale = Vector3<double>(1.0, 1.0, 1.0);
};

class Camera : public ObjectData
{
public:
	double FocalLength;
	void ShiftFocalLength(double change)
	{
		FocalLength += change;
	}
	void ShiftLocation(Vector3<double> shift)
	{
		Origin[0] += shift[0];
		Origin[1] += shift[1];
		Origin[2] += shift[2];
	}
	void ShiftRotation(Vector3<double> rotate)
	{
		Rotation[0] += rotate[0]*(M_PI/180.0);
		Rotation[1] += rotate[1]*(M_PI/180.0);
		Rotation[2] += rotate[2]*(M_PI/180.0);
	}
};

class Model : public ObjectData
{
	int LoadObject(char* path);
public:
	std::vector<Vector3<double>> Vertex;
	std::vector<Vector3<int>> Face;
	explicit Model(char* path);

	void MeshTranslate(Vector3<double> translate);
	void MeshRotate(Vector3<double> rotate);
	void MeshScale(Vector3<double> scale);
	void MeshTransform(Vector3<double> translate, Vector3<double> rotate, Vector3<double> scale);
};