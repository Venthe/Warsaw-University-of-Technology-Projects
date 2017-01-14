#pragma once
#include <array>
#include "types.h"
#include <vector>
#include "object_handler.h"

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

