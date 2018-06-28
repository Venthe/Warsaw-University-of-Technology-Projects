#pragma once
#include <String>
#include <List>

#include "ControlPoint.h"

void writeToFile(std::string filename, std::list<ControlPoint> list);
std::list<ControlPoint> readFromFile(std::string filename);