#include "stdafx.h"

#include "Io.h"

#include <fstream>
#include <sstream>

namespace esl {
  inline void io::writeToFile(
      std::string fileName,
      std::vector<esl::ControlPoint>& controlPointList) {
    std::ofstream file(fileName);
    file << serialize(controlPointList);
    file.close();
  }

  inline std::vector<esl::ControlPoint> io::readFromFile(std::string fileName) {
    std::ifstream file(fileName);
    return io::deserialize(file);
  }

  inline esl::ControlPoint io::controlPointFrom(std::string line) {
    std::istringstream iss(line);
    long x, y;
    double w;
    iss >> x >> y >> w;

    return {x, y, w};
  }

  inline std::string io::serialize(
      std::vector<esl::ControlPoint>& controlPointList) {
    std::string result;

    for (auto controlPoint : controlPointList) {
      result.append(controlPoint.toString()).append("\n");
    }

    return result;
  }

  inline std::vector<esl::ControlPoint> io::deserialize(std::ifstream& stream) {
    std::vector<esl::ControlPoint> newList;

    std::string line;
    while (std::getline(stream, line)) {
      newList.push_back(io::controlPointFrom(line));
    }

    return newList;
  }
}  // namespace esl
