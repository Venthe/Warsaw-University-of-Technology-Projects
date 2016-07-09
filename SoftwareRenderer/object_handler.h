#pragma once
#include <vector>
#include <array>
#include "types.h"
#include "mymath.h"

class Scalable
{
public:
	Vector<float, 3> Scale = Vector<float, 3>({1.0, 1.0, 1.0});
};

class ObjectData
{
public:
	Vector<float, 3> Origin = Vector<float, 3>({0.0, 0.0, 0.0});
	Vector<float, 3> Rotation = Vector<float, 3>({0.0, 0.0, 0.0});
};

class Camera : public ObjectData
{
public:
	float FocalLength;

	void ShiftFocalLength(float change)
	{
		FocalLength += change;
	}

	void ShiftLocation(Vector<float, 3> shift)
	{
		Origin[0] += shift[0];
		Origin[1] += shift[1];
		Origin[2] += shift[2];
	}

	void ShiftRotation(Vector<float, 3> rotate)
	{
		Rotation[0] += rotate[0];
		Rotation[1] += rotate[1];
		Rotation[2] += rotate[2];
	}
};

class Model : public ObjectData, public Scalable
{
	int LoadObject(std::string path);
	std::array<float, 16> ModelMatrix;
public:
	std::vector<Vector<float, 3>> Vertex;
	std::vector<Vector<int, 3>> Face;

	Model(std::string path, Vector<float, 3> Loc = Vector<float, 3>(), Vector<float, 3> Rot = Vector<float, 3>(), Vector<float, 3> Sca = Vector<float, 3>({1,1,1}))
	{
		Origin = Loc;
		Rotation = Rot;
		Scale = Sca;
		this->LoadObject(path);
	}

	std::array<float, 16> GetModelMatrix();
};

