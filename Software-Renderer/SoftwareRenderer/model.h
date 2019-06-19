#pragma once
#include <array>
#include "types.h"
#include <vector>
#include "object_handler.h"

class Model : public ObjectData
{
	Vector3f ParsefloatFromObj(std::string line) const;
	static Vector<int, 3> ParseIntFromObj(std::string line);
	static void extractValuesToBuffer(std::string& line, std::string buffer[3]);
	int LoadObject(std::string path);
	void parseObjData(std::ifstream& myfile, std::string& line);
	static bool isValidObjDataPrefix(std::string& line);
	void parseFace(std::string& line);
	void parseVertex(std::string& line);
	Matrix4f ModelTransformationMatrix;
public:
	std::vector<Vector3f> Vertex;
	std::vector<Vector<int, 3>> Face;

	Model(std::string path, Vector3f Loc = Vector3f(), Vector3f Rot = Vector3f(), Vector3f Sca = {1,1,1});
	Matrix4f GetModelTransformationMatrix();
};
