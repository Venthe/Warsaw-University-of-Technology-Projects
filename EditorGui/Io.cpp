#include "stdafx.h"
#include "Io.h"

#include <sstream>
#include <fstream>

#include "ControlPointList.h"

void writeToFile(std::string filename, std::vector<ControlPoint> list) {
	std::ofstream file;
	file.open(filename.c_str());
	file << serialize(list);
	file.close();
}

std::vector<ControlPoint> readFromFile(std::string filename) {
	std::ifstream file;
	file.open(filename);

	std::vector<ControlPoint> newList;

	std::string line;
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		long x, y;
		double w;
		iss >> x >> y >> w;

		newList.push_back(ControlPoint(x, y, w));
	}

	return newList;
}