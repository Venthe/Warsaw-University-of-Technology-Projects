#include "stdafx.h"
#include "ControlPointList.h"

std::string serialize(std::list<ControlPoint> list) {
	std::string result = "";

	for (std::list<ControlPoint>::iterator it = list.begin(); it != list.end(); it++)
	{
		result.append(it->to_string()).append("\n");
	}

	return result;
}