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
		IO void writeToFile(std::string filename, std::vector<esl::ControlPoint> &list);
		IO std::vector<esl::ControlPoint> readFromFile(std::string filename);
		static esl::ControlPoint controlPointFrom(std::string line);
		static std::vector<esl::ControlPoint> deserialize(std::ifstream &file);
		static std::string serialize(std::vector<esl::ControlPoint> &list);
	}; // namespace io
} // namespace esl
