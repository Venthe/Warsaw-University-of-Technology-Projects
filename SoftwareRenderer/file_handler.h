#pragma once
#include <vector>
#include "types.h"


class ObjModel
{
public:
	ObjModel(char* path)
	{
		this->ReadObj(path);
	}

	Vector3<double> Origin = Vector3<double>(0.0, 0.0, 0.0);
	Vector3<double> Scale = Vector3<double>(1.0, 1.0, 1.0);
	std::vector<Vector3<double>> Vertex;
	std::vector<Vector3<int>> Face;
	int ReadObj(char* path);
};

