#pragma once

#include <string>

#ifdef ESL_EXPORTS
#define CONTROL_POINT __declspec(dllexport)
#else
#define CONTROL_POINT __declspec(dllimport)
#endif

namespace esl {
	class CONTROL_POINT ControlPoint {
	private:
		long _x;
		long _y;
		double _weight;

	public:
		ControlPoint(long x, long y, double weight);
		long get_x();
		long get_y();
		double get_weight();
		std::string to_string();
	};
} // namespace esl