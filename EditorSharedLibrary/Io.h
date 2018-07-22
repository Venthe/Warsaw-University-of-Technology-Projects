#pragma once

#include <string>
#include <vector>

#include "ControlPoint.h"

#define IO __declspec(dllexport)

namespace esl {
  namespace io {
    IO void writeToFile(std::string fileName,
                        std::vector<esl::ControlPoint>& controlPointList);
    IO std::vector<esl::ControlPoint> readFromFile(std::string fileName);
    static esl::ControlPoint controlPointFrom(std::string line);
    static std::vector<esl::ControlPoint> deserialize(std::ifstream& stream);
    static std::string serialize(
        std::vector<esl::ControlPoint>& controlPointList);
  };  // namespace io
}  // namespace esl
