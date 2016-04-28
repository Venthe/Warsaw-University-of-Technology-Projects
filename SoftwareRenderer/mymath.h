#pragma once
#include <array>
#include "types.h"
namespace MyMath{
	#define M_PI 3.14159

	double AngleInDegrees(double d);

	template <typename T, size_t x>
	std::array <T, x> IdentityMatrix()
	{
		std::array <T, x> result;
		result.fill(0);
		if (static_cast<int>(sqrt(x)) % 2 != 0) return result;

		for (int i = 0; i != sqrt(x); i++)
		{
			result[static_cast<size_t>(i*sqrt(x) + i)] = 1;
		}
		return result;
	}

	template <typename T, size_t x>
	std::array <T, x> ArrayMultiplication(std::array <T, x> a, std::array <T, x> b)
	{
		std::array <T, x> result;
		result.fill(0);
		for (int r = 0; r < sqrt(x); r++)
		{
			for (int c = 0; c < sqrt(x); c++)
			{
				for (int inner = 0; inner < sqrt(static_cast<int>(x)); inner++)
					result[r*static_cast<int>(sqrt(x)) + c]
					+= a[r * static_cast<int>(sqrt(x)) + inner]
					* b[inner * static_cast<int>(sqrt(x)) + c];
			}
		}

		return result;
	}

	template <typename T, size_t x>
	int transformVectorByArray(std::array<T, x> t, Vector3<T>& v, bool retroProject = false)
	{
		T result[4];
		for (int i = 0; i < sqrt(x); i++) result[i] = v[0] * t[i * 4] + v[1] * t[i * 4 + 1] + v[2] * t[i * 4 + 2] + 1 * t[i * 4 + 3];

		for (int i = 0; i < 4 - 1; i++) {
			if (retroProject) {
				v[i] = result[i] / result[4 - 1];
			}
			else v[i] = result[i];
		}
		return 0;
	}

	template <typename T, size_t x>
	std::array <T, x> ScaleMatrix(Vector3<T> Scale)
	{
		std::array <T, x>temp = IdentityMatrix<T, x>();
		temp[0] = Scale[0];
		temp[5] = Scale[1];
		temp[10] = Scale[2];
		return temp;
	}
	template <typename T, size_t x>
	std::array <T, x> RotateMatrix(Vector3<T> v)
	{
		auto temp = IdentityMatrix<T, x>();

		temp = ArrayMultiplication(temp, RotateMatrixx<T, x>(v[0]));
		temp = ArrayMultiplication(temp, RotateMatrixy<T, x>(v[1]));
		temp = ArrayMultiplication(temp, RotateMatrixz<T, x>(v[2]));

		return temp;
	}

	template <typename T, size_t x>
	std::array <T, x> RotateMatrixz(double d)
	{
		std::array <T, x>temp = IdentityMatrix<T, x>();
		temp[5] = std::cos(AngleInDegrees(d));
		temp[6] = -std::sin(AngleInDegrees(d));
		temp[9] = std::sin(AngleInDegrees(d));
		temp[10] = std::cos(AngleInDegrees(d));
		return temp;
	}

	template <typename T, size_t x>
	std::array <T, x> RotateMatrixy(double d)
	{
		std::array <T, x>temp = IdentityMatrix<T, x>();
		temp[0] = std::cos(AngleInDegrees(d));
		temp[1] = -std::sin(AngleInDegrees(d));
		temp[4] = std::sin(AngleInDegrees(d));
		temp[5] = std::cos(AngleInDegrees(d));
		return temp;
	}

	template <typename T, size_t x>
	std::array <T, x> RotateMatrixx(double d)
	{
		std::array <T, x>temp = IdentityMatrix<T, x>();
		temp[0] = std::cos(AngleInDegrees(d));
		temp[2] = std::sin(AngleInDegrees(d));
		temp[8] = -std::sin(AngleInDegrees(d));
		temp[10] = std::cos(AngleInDegrees(d));
		return temp;
	}

	template <typename T, size_t x>
	std::array <T, x> TranslateMatrix(Vector3<T> Origin)
	{
		std::array <T, x>temp = IdentityMatrix<T, x>();
		temp[3] = Origin[0];
		temp[7] = Origin[1];
		temp[11] = Origin[2];
		return temp;
	}
}