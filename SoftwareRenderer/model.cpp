#include <iostream>
#include <fstream>
#include "mymath.h"
#include "model.h"

Model::Model(std::string path, Vector<float, 3> Loc, Vector<float, 3> Rot, Vector<float, 3> Sca)
{
	Origin = Loc;
	Rotation = Rot;
	Scale = Sca;
	this->LoadObject(path);
}

Vector<float, 3> ParsefloatFromObj(std::string line)
{
	std::string buffer[3];
	int pos;
	for (int i = 0; i < 3; i++)
	{
		pos = int(line.find(' '));
		buffer[i] = line.substr(0, pos);
		line = line.substr(pos + 1, line.length());
	}

	return Vector<float, 3>({ stof(buffer[0]), stof(buffer[1]), stof(buffer[2]) });
}

Vector<int, 3> ParseIntFromObj(std::string line)
{
	std::string buffer[3];
	int pos;
	for (int i = 0; i < 3; i++)
	{
		pos = int(line.find(' '));
		buffer[i] = line.substr(0, pos);
		line = line.substr(pos + 1, line.length());
	}

	return Vector<int, 3>({ atoi(buffer[0].c_str()), atoi(buffer[1].c_str()), atoi(buffer[2].c_str()) });
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
	while (getline(myfile, line))
	{
		if (line.length() > 2 && line[1] == ' ')
		{
			if (line[0] == 'v' || line[0] == 'V')
			{
				Vertex.push_back(ParsefloatFromObj(line.substr(2, line.length())));
			}
			else if (line[0] == 'f' || line[0] == 'F')
			{
				Face.push_back(ParseIntFromObj(line.substr(2, line.length())));
			}
		}
	}
	myfile.close();
	return 0;
}

std::array<float, 16> Model::GetModelTransformationMatrix()
{
	std::array<float, 16> ScaleM = MyMath::ScaleMatrix<float>(Scale);
	std::array<float, 16> TranslateM = MyMath::TranslateMatrix<float>(Origin);
	std::array<float, 16> Rotate = MyMath::RotateMatrix<float>(Rotation);

	ModelTransformationMatrix = MyMath::IdentityMatrix<float, 16>();
	ModelTransformationMatrix = MyMath::ArrayMultiplication(ModelTransformationMatrix, Rotate);
	ModelTransformationMatrix = MyMath::ArrayMultiplication(ModelTransformationMatrix, ScaleM);
	ModelTransformationMatrix = MyMath::ArrayMultiplication(ModelTransformationMatrix, TranslateM);

	return ModelTransformationMatrix;
}
