#include "object_handler.h"
// basic file operations
#include <iostream>
#include <fstream>
#include <string>
#include "types.h"

Vector3<double> ParseDoubleFromObj(std::string line)
{
	std::string buffer[3];
	int pos;
	for (int i = 0; i < 3; i++)
	{
		pos = line.find(' ');
		buffer[i] = line.substr(0, pos);
		line = line.substr(pos + 1, line.length());
	}

	return Vector3<double>(stod(buffer[0]), stod(buffer[1]), stod(buffer[2]));
}

Vector3<int> ParseIntFromObj(std::string line)
{
	std::string buffer[3];
	int pos;
	for (int i = 0; i < 3; i++)
	{
		pos = line.find(' ');
		buffer[i] = line.substr(0, pos);
		line = line.substr(pos + 1, line.length());
	}

	return Vector3<int>(atoi(buffer[0].c_str()), atoi(buffer[1].c_str()), atoi(buffer[2].c_str()));
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
		if (line.length() > 2 && line[1] == ' ') {
			if (line[0] == 'v' || line[0] == 'V')
			{
				Vertex.push_back(ParseDoubleFromObj(line.substr(2, line.length())));
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

std::array<double, 16> Model::GetModelMatrix()
{
	std::array<double, 16> ScaleM = MyMath::ScaleMatrix<double, 16>(Scale);
	std::array<double, 16> TranslateM = MyMath::TranslateMatrix<double, 16>(Origin);
	std::array<double, 16> Rotate = MyMath::RotateMatrix<double, 16>(Rotation);

	ModelMatrix = MyMath::IdentityMatrix<double, 16>();
	ModelMatrix = MyMath::ArrayMultiplication(ModelMatrix, Rotate);
	ModelMatrix = MyMath::ArrayMultiplication(ModelMatrix, ScaleM);
	ModelMatrix = MyMath::ArrayMultiplication(ModelMatrix, TranslateM);

	return ModelMatrix;
}