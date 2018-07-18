#include "stdafx.h"
#include "ControlPoint.h"

namespace esl {
	inline ControlPoint::ControlPoint(long x, long y, double weight) {
		_x = x;
		_y = y;
		_weight = weight;
	}

	inline long ControlPoint::get_x() {
		return _x;
	}

	inline long ControlPoint::get_y() {
		return _y;
	}

	inline double ControlPoint::get_weight() {
		return _weight;
	}

	inline std::string ControlPoint::to_string() {
		return std::to_string(_x) + " " + std::to_string(_y) + " " + std::to_string(_weight);
	}
}