#pragma once
#include <vector>
#include <array>
#include "types.h"
#include "mymath.h"

class Scalable
{
public:
	Vector3<double> Scale = Vector3<double>(1.0, 1.0, 1.0);
};

class ObjectData
{
public:
	Vector3<double> Origin = Vector3<double>(0.0, 0.0, 0.0);
	Vector3<double> Rotation = Vector3<double>(0.0, 0.0, 0.0);
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
		Rotation[0] += rotate[0];
		Rotation[1] += rotate[1];
		Rotation[2] += rotate[2];
	}
};

class Model : public ObjectData, public Scalable
{
	int LoadObject(std::string path);
	std::array<double, 16> ModelMatrix;
public:
	std::vector<Vector3<double>> Vertex;
	std::vector<Vector3<int>> Face;

	Model(std::string path, Vector3<double> Loc = Vector3<double>(), Vector3<double> Rot = Vector3<double>(), Vector3<double> Sca = Vector3<double>(1,1,1))
	{
		Origin = Loc;
		Rotation = Rot;
		Scale = Sca;
		this->LoadObject(path);
	}

	std::array<double, 16> GetModelMatrix();
};