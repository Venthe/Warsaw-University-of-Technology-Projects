#include "stdafx.h"
#include "Io.h"

#include <sstream>
#include <fstream>

inline void esl::io::write_to_file(std::string filename, std::vector<esl::ControlPoint> &list) {
	std::ofstream file(filename);
	file << serialize(list);
	file.close();
}

inline std::vector<esl::ControlPoint> esl::io::read_from_file(std::string filename) {
	std::ifstream file(filename);
	return esl::io::deserialize(file);
}

esl::ControlPoint esl::io::control_point_from(std::string line) {
	std::istringstream iss(line);
	long x, y;
	double w;
	iss >> x >> y >> w;

	return esl::ControlPoint(x, y, w);
}

std::string esl::io::serialize(std::vector<esl::ControlPoint> &list) {
	std::string result = "";

	for (std::vector<esl::ControlPoint>::iterator it = list.begin(); it != list.end(); it++)
	{
		result.append(it->to_string()).append("\n");
	}

	return result;
}

std::vector<esl::ControlPoint> esl::io::deserialize(std::ifstream &file)
{
	std::vector<esl::ControlPoint> newList;

	std::string line;
	while (std::getline(file, line)) {
		newList.push_back(esl::io::control_point_from(line));
	}

	return newList;
}
