#pragma once
#include <vector>
#include <array>
#include "types.h"
#include "mymath.h"

class Scalable
{
public:
	Vector<double, 3> Scale = Vector<double, 3>({1.0, 1.0, 1.0});
};

class ObjectData
{
public:
	Vector<double, 3> Origin = Vector<double, 3>({0.0, 0.0, 0.0});
	Vector<double, 3> Rotation = Vector<double, 3>({0.0, 0.0, 0.0});
};

class Camera : public ObjectData
{
public:
	double FocalLength;

	void ShiftFocalLength(double change)
	{
		FocalLength += change;
	}

	void ShiftLocation(Vector<double, 3> shift)
	{
		Origin[0] += shift[0];
		Origin[1] += shift[1];
		Origin[2] += shift[2];
	}

	void ShiftRotation(Vector<double, 3> rotate)
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
	std::vector<Vector<double, 3>> Vertex;
	std::vector<Vector<int, 3>> Face;

	Model(std::string path, Vector<double, 3> Loc = Vector<double, 3>(), Vector<double, 3> Rot = Vector<double, 3>(), Vector<double, 3> Sca = Vector<double, 3>({1,1,1}))
	{
		Origin = Loc;
		Rotation = Rot;
		Scale = Sca;
		this->LoadObject(path);
	}

	std::array<double, 16> GetModelMatrix();
};

