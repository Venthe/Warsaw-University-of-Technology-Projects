#pragma once
#include <String>
#include <Vector>

#include "ControlPoint.h"

void writeToFile(std::string filename, std::vector<ControlPoint> list);
std::vector<ControlPoint> readFromFile(std::string filename);
