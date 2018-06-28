#include "stdafx.h"
#include "ControlPointList.h"

std::string serialize(std::vector<ControlPoint> list) {
	std::string result = "";

	for (std::vector<ControlPoint>::iterator it = list.begin(); it != list.end(); it++)
	{
		result.append(it->to_string()).append("\n");
	}

	return result;
}

std::vector<QPoint> toQPoints(std::vector<ControlPoint> list) {
	std::vector<QPoint> result;

	for (std::vector<ControlPoint>::iterator it = list.begin(); it != list.end(); it++) {
		result.push_back(toQPoint(*it));
	}

	return result;
}

QPoint toQPoint(ControlPoint point) {
	return QPoint(point.getX(), point.getY());
}

ControlPoint toControlPoint(QPoint point, double weight) {
	return ControlPoint(point.x(), point.y(), weight);
}
