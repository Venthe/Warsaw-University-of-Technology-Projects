#pragma once

#include <List>

#include "ControlPoint.h"

class ControlPointList {
public:
	std::list<ControlPoint> List;

	std::string toString() {
		std::string result = "";

		for (std::list<ControlPoint>::iterator it = List.begin(); it != List.end() ; it++)
		{
			result.append(it->toString()).append("\n");
		}

		return result;
	}
};

ControlPointList controlPointList;