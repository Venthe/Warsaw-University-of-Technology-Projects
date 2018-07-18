#pragma once
#include <String>
#include <Vector>

#include "ControlPoint.h"

#ifdef ESL_EXPORTS
#define IO __declspec(dllexport)
#else
#define IO __declspec(dllimport)
#endif

namespace esl {
	namespace io {
		IO void write_to_file(std::string filename, std::vector<esl::ControlPoint> &list);
		IO std::vector<esl::ControlPoint> read_from_file(std::string filename);

		esl::ControlPoint control_point_from(std::string line);
		std::vector<esl::ControlPoint> deserialize(std::ifstream &file);
		std::string serialize(std::vector<esl::ControlPoint> &list);
	}
}