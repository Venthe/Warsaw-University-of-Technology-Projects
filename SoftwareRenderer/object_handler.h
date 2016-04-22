#pragma once
#include <vector>
#include <array>
#include "types.h"
#include "mymath.h"

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
	double AngleInDegrees(double d)
	{
		return d*(M_PI/180.0);
	}
public:
	std::vector<Vector3<double>> Vertex;
	std::vector<Vector3<int>> Face;
	explicit Model(char* path);
	std::array<double, 16> ScaleMatrix = IdentityMatrix<double, 4>();
	std::array<double, 16> TranslateMatrix = IdentityMatrix<double, 4>();
	std::array<double, 16> RotateXMatrix = IdentityMatrix<double, 4>();
	std::array<double, 16> RotateYMatrix = IdentityMatrix<double, 4>();
	std::array<double, 16> RotateZMatrix = IdentityMatrix<double, 4>();

	void ModelMatrix ()
	{
		std::array<double, 16> temp;

		//ScaleMatrix
		temp = IdentityMatrix<double, 4>();
		temp[0] = Scale[0];
		temp[5] = Scale[1];
		temp[10] = Scale[2];
		ScaleMatrix = temp;

		//RotateMatrix

		//Z
		temp = IdentityMatrix<double, 4>();
		temp[5] =  std::cos(AngleInDegrees(Rotation[2]));
		temp[6] = -std::sin(AngleInDegrees(Rotation[2]));
		temp[9] =  std::sin(AngleInDegrees(Rotation[2]));
		temp[10] = std::cos(AngleInDegrees(Rotation[2]));
		RotateZMatrix = temp;

		//Y
		temp = IdentityMatrix<double, 4>();
		temp[0] =  std::cos(AngleInDegrees(Rotation[1]));
		temp[1] = -std::sin(AngleInDegrees(Rotation[1]));
		temp[4] =  std::sin(AngleInDegrees(Rotation[1]));
		temp[5] =  std::cos(AngleInDegrees(Rotation[1]));
		RotateYMatrix = temp;

		//X
		temp = IdentityMatrix<double, 4>();
		temp[0] =  std::cos(AngleInDegrees(Rotation[0]));
		temp[2] =  std::sin(AngleInDegrees(Rotation[0]));
		temp[8] = -std::sin(AngleInDegrees(Rotation[0]));
		temp[10] = std::cos(AngleInDegrees(Rotation[0]));
		RotateXMatrix = temp;


		//Translate
		temp = IdentityMatrix<double, 4>();
		temp[3]  = Origin[0];
		temp[7]  = Origin[1];
		temp[11] = Origin[2];
		TranslateMatrix = temp;
	}
};