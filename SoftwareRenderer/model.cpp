#include <iostream>
#include <fstream>
#include "my_math.h"
#include "model.h"

Model::Model(std::string path, Vector3f Loc, Vector3f Rot, Vector3f Sca)
{
	Origin = Loc;
	Rotation = Rot;
	Scale = Sca;
	this->LoadObject(path);
}

int Model::LoadObject(std::string path)
{
	std::ifstream myfile;
	myfile.open(path.c_str());

	if (!myfile.is_open())
	{
		std::cerr << "Problem opening file " << path << std::endl;
		return 1;
	}

	std::string line;
	parseObjData(myfile, line);
	myfile.close();
	return 0;
}

void Model::parseObjData(std::ifstream& myfile, std::string& line)
{
	while (getline(myfile, line))
	{
		if (isValidObjDataPrefix(line))
		{
			parseVertex(line);
			parseFace(line);
		}
	}
}

bool Model::isValidObjDataPrefix(std::string& line)
{
	return line.length() > 2 && line[1] == ' ';
}

void Model::parseFace(std::string& line)
{
	if (line[0] == 'f' || line[0] == 'F') Face.push_back(ParseIntFromObj(line.substr(2, line.length())));
}

void Model::parseVertex(std::string& line)
{
	if (line[0] == 'v' || line[0] == 'V') Vertex.push_back(ParsefloatFromObj(line.substr(2, line.length())));
}

Matrix4f Model::GetModelTransformationMatrix()
{
	auto RotationMatrix = constructRotationMatrix<float>(Rotation);
	auto ScaleMatrix = constructScaleMatrix<float>(Scale);
	auto TranslateMatrix = constructTranslationMatrix<float>(Origin);

	ModelTransformationMatrix = IdentityMatrix<float, 16>();
	ModelTransformationMatrix = ArrayMultiplication(RotationMatrix, ModelTransformationMatrix);
	ModelTransformationMatrix = ArrayMultiplication(ScaleMatrix, ModelTransformationMatrix);
	ModelTransformationMatrix = ArrayMultiplication(TranslateMatrix, ModelTransformationMatrix);

	return ModelTransformationMatrix;
}

Vector3f Model::ParsefloatFromObj(std::string line) const
{
	std::string buffer[3];
	extractValuesToBuffer(line, buffer);

	return Vector3f({stof(buffer[0]), stof(buffer[1]), stof(buffer[2])});
}

Vector<int, 3> Model::ParseIntFromObj(std::string line)
{
	std::string buffer[3];
	extractValuesToBuffer(line, buffer);

	return Vector<int, 3>({atoi(buffer[0].c_str()), atoi(buffer[1].c_str()), atoi(buffer[2].c_str())});
}

void Model::extractValuesToBuffer(std::string& line, std::string buffer[3])
{
	int pos;
	for (int i = 0; i < 3; i++)
	{
		pos = int(line.find(' '));
		buffer[i] = line.substr(0, pos);
		line = line.substr(pos + 1, line.length());
	}
}
