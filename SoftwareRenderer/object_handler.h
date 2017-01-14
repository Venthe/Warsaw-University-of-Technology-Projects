#pragma once
#include <array>
#include <vector>
#include "types.h"

class ObjectData
{
public:
	Vector<float, 3> Origin = Vector<float, 3>({ 0.0, 0.0, 0.0 });
	Vector<float, 3> Rotation = Vector<float, 3>({ 0.0, 0.0, 0.0 });
	Vector<float, 3> Scale = Vector<float, 3>({ 1.0, 1.0, 1.0 });
};

class Camera : public ObjectData
{
public:
	float FocalLength;
	float clipNear;
	float clipFar;

	void ShiftFocalLength(float change);
	void ShiftLocation(Vector<float, 3> shift);
	void ShiftRotation(Vector<float, 3> rotate);
};

class Model : public ObjectData
{
	int LoadObject(std::string path);
	std::array<float, 16> ModelTransformationMatrix;
public:
	std::vector<Vector<float, 3>> Vertex;
	std::vector<Vector<int, 3>> Face;

	Model(std::string path, Vector<float, 3> Loc = Vector<float, 3>(), Vector<float, 3> Rot = Vector<float, 3>(), Vector<float, 3> Sca = Vector<float, 3>({ 1,1,1 }));
	std::array<float, 16> GetModelTransformationMatrix();
};

