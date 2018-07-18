#include "stdafx.h"
#include "Io.h"

#include <sstream>
#include <fstream>

namespace esl {
	inline void io::write_to_file(std::string filename, std::vector<esl::ControlPoint> &list) {
		std::ofstream file(filename);
		file << serialize(list);
		file.close();
	}

	inline std::vector<esl::ControlPoint> io::read_from_file(std::string filename) {
		std::ifstream file(filename);
		return io::deserialize(file);
	}

	inline esl::ControlPoint io::control_point_from(std::string line) {
		std::istringstream iss(line);
		long x, y;
		double w;
		iss >> x >> y >> w;

		return { x, y, w };
	}

	inline std::string io::serialize(std::vector<esl::ControlPoint> &list) {
		std::string result;

		for (auto controlPoint : list)
		{
			result.append(controlPoint.to_string()).append("\n");
		}

		return result;
	}

	inline std::vector<esl::ControlPoint> io::deserialize(std::ifstream &file)
	{
		std::vector<esl::ControlPoint> newList;

		std::string line;
		while (std::getline(file, line)) {
			newList.push_back(io::control_point_from(line));
		}

		return newList;
	}
} // namespace esl