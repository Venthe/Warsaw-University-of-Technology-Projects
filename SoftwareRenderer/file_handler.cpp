#include "file_handler.h"
// basic file operations
#include <iostream>
#include <fstream>
#include <string>
#include "types.h"

using namespace std;

Vector3<double> ParseDoubleFromObj(string line)
{
	string buffer[3];
	int pos;
	for (int i = 0; i < 3; i++)
	{
		pos = line.find(' ');
		buffer[i] = line.substr(0, pos);
		line = line.substr(pos + 1, line.length());
	}

	return Vector3<double>(stod(buffer[0]), stod(buffer[1]), stod(buffer[2]));
}

Vector3<int> ParseIntFromObj(string line)
{
	string buffer[3];
	int pos;
	for (int i = 0; i < 3; i++)
	{
		pos = line.find(' ');
		buffer[i] = line.substr(0, pos);
		line = line.substr(pos + 1, line.length());
	}

	return Vector3<int>(atoi(buffer[0].c_str()), atoi(buffer[1].c_str()), atoi(buffer[2].c_str()));
}

int ObjModel::ReadObj(char* path)
{
	ifstream myfile;
	myfile.open(path);
	if (!myfile.is_open())
	{
		cout << "Problem opening file " << path << endl;
		return 1;
	}
	string line;
	while (getline(myfile, line))
	{
		if (line[0] == 'v' || line[0] == 'V')
		{
			Vertex.push_back(ParseDoubleFromObj(line.substr(2, line.length())));
		}
		else if (line[0] == 'f' || line[0] == 'F')
		{
			Face.push_back(ParseIntFromObj(line.substr(2, line.length())));
		}
	}
	myfile.close();
	return 0;
}

