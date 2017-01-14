#pragma once
#include <array>
#include "types.h"
#include "linalg.h"

using namespace linalg;

namespace MyMath
{
#define M_PI 3.14159

	bool transformVectorByArray(std::array<float, 16> t, Vector<float, 3>& v, bool retroProject = false);
	float NormalizationToUnity(float value, float min, float max);
	float DegreesToRadians(float d);

	template <typename T, size_t x>
	std::array<T, x> IdentityMatrix()
	{
		std::array<T, x> result;
		result.fill(0);
		if (int(sqrt(x)) % 2 != 0) return result;

		for (int i = 0; i != sqrt(x); i++)
		{
			result[static_cast<size_t>(i * sqrt(x) + i)] = 1;
		}
		return result;
	}

	template <typename T, size_t x>
	std::array<T, x> ArrayMultiplication(std::array<T, x> a, std::array<T, x> b)
	{
		std::array<T, x> result;
		result.fill(0);
		for (int r = 0; r < sqrt(x); r++)
		{
			for (int c = 0; c < sqrt(x); c++)
			{
				for (int inner = 0; inner < sqrt(int(x)); inner++)
					result[r * int(sqrt(x)) + c]
					+= a[r * int(sqrt(x)) + inner]
					* b[inner * int(sqrt(x)) + c];
			}
		}

		return result;
	}

	template <typename T>
	std::array<T, 16> ScaleMatrix(Vector<T, 3> Scale)
	{
		std::array<T, 16> temp = IdentityMatrix<T, 16>();
		temp[0] = Scale[0];
		temp[5] = Scale[1];
		temp[10] = Scale[2];
		return temp;
	}

	template <typename T>
	std::array<T, 16> fromLinalgMat4ToArray16(mat<T, 4,4> matrix)
	{
		std::array<T, 16> result;
		for(int row=0; row<4; row++)
		{
			for (int col = 0; col<4; col++)
			{
				result[row * 4 + col] = matrix[row][col];
			}
		}
		return result;
	}

	template <typename T>
	mat<T, 4, 4> fromArray16ToLinalgMat4(std::array<T, 16> matrix)
	{
		std::array<T, 16> result;
		for (int row = 0; row<4; row++)
		{
			for (int col = 0; col<4; col++)
			{
				result[row][col] = matrix[row * 4 + col];
			}
		}
		return result;
	}

	template <typename T>
	std::array<T, 16> RotateMatrix(Vector<T, 3> v)
	{
		auto quaternionX = rotation_quat(vec<float,3>(1, 0, 0), DegreesToRadians(v[0]));
		auto quaternionY = rotation_quat(vec<float, 3>(0, 1, 0), DegreesToRadians(v[1]));
		auto quaternionZ = rotation_quat(vec<float, 3>(0, 0, 1), DegreesToRadians(v[2]));
		auto quaternion = qmul(qmul(quaternionX, quaternionY), quaternionZ);

		auto rotationMatrix = linalg::rotation_matrix(quaternion);

		return fromLinalgMat4ToArray16(rotationMatrix);
	}

	template <typename T>
	std::array<T, 16> TranslateMatrix(Vector<T, 3> Origin)
	{
		std::array<T, 16> temp = IdentityMatrix<T, 16>();
		temp[3] = Origin[0];
		temp[7] = Origin[1];
		temp[11] = Origin[2];
		return temp;
	}


}

