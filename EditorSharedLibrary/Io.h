#pragma once
#include <string>
#include <vector>

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
		static esl::ControlPoint control_point_from(std::string line);
		static std::vector<esl::ControlPoint> deserialize(std::ifstream &file);
		static std::string serialize(std::vector<esl::ControlPoint> &list);
	}; // namespace io
} // namespace esl
