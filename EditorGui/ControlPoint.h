#pragma once

#include <string>

class ControlPoint {
private:
	long _x;
	long _y;
	double _weight;
public:
	ControlPoint(long x, long y, double weight) {
		_x = x;
		_y = y;
		_weight = weight;
	}

	long getX() {
		return _x;
	}

	long getY() {
		return _y;
	}

	double getWeight() {
		return _weight;
	}

	std::string to_string() {
		return std::to_string(_x) + " " + std::to_string(_y) + " " + std::to_string(_weight);
	}
};
