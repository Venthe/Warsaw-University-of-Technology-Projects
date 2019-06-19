#pragma once
#include <array>
#include "types.h"

namespace MyMath
{
#define M_PI 3.14159

	inline void transformVectorByArray(Matrix4f t, Vector4f& v)
	{
		Vector4f result;
		for (int i = 0; i < 4; i++) result[i] = v[0] * t[i * 4] + v[1] * t[i * 4 + 1] + v[2] * t[i * 4 + 2] + v[3] * t[i * 4 + 3];

		v = result;
	}

	inline void transformFaceByArray(Matrix4f t, Facef& v)
	{
		for (int i = 0; i < 3; i++)
		{
			transformVectorByArray(t, v[i]);
		}
	}

	inline float ArcDegreesToRadians(float degrees) { return degrees * (float(M_PI) / 180.0f); }

	template <typename T, size_t x>
	std::array<T, x> IdentityMatrix()
	{
		std::array<T, x> result;
		result.fill(0);

		int squareRootOfSize = int(sqrt(x));
		if (squareRootOfSize % 2 != 0) return result;

		for (int i = 0; i != squareRootOfSize; i++)
		{
			result[static_cast<size_t>(i * squareRootOfSize + i)] = 1;
		}
		return result;
	}

	template <typename T, size_t x>
	std::array<T, x> ArrayMultiplication(std::array<T, x> a, std::array<T, x> b)
	{
		size_t sizeSqrt = size_t(sqrt(x));
		std::array<T, x> result;
		result.fill(0);
		for (size_t row = 0; row < sizeSqrt; row++)
		{
			for (size_t column = 0; column < sizeSqrt; column++)
			{
				for (size_t inner = 0; inner < sizeSqrt; inner++)
				{
					result[row * sizeSqrt + column] += a[row * sizeSqrt + inner] * b[inner * sizeSqrt + column];
				}
			}
		}
		return result;
	}

	template <typename T>
	Vector<T, 4> toQuaternion( T pitchEuler,T rollEuler, T yawEuler)
	{
		Vector<T, 4> q;

		pitchEuler = ArcDegreesToRadians(pitchEuler);
		rollEuler = ArcDegreesToRadians(rollEuler);
		yawEuler = ArcDegreesToRadians(yawEuler);

		T t0 = std::cos(yawEuler * 0.5f);
		T t1 = std::sin(yawEuler * 0.5f);
		T t2 = std::cos(rollEuler * 0.5f);
		T t3 = std::sin(rollEuler * 0.5f);
		T t4 = std::cos(pitchEuler * 0.5f);
		T t5 = std::sin(pitchEuler * 0.5f);

		q[0] = t0 * t2 * t4 + t1 * t3 * t5;
		q[1] = t0 * t3 * t4 - t1 * t2 * t5;
		q[2] = t0 * t2 * t5 + t1 * t3 * t4;
		q[3] = t1 * t2 * t4 - t0 * t3 * t5;
		return q;
	}


	template <typename T>
	std::array<T, 16> QuaternionToMatrix(Vector<T, 4> quaternion)
	{
		auto result = IdentityMatrix<float, 16>();

		T qx = quaternion[3], qy = quaternion[2], qz = quaternion[1], qw = quaternion[0];

		result[0] = 1 - (2 * qy * qy) - (2 * qz * qz);
		result[1] = (2 * qx * qy) - (2 * qz * qw);
		result[2] = (2 * qx * qz) + (2 * qy * qw);

		result[4] = (2 * qx * qy) + (2 * qz * qw);
		result[5] = 1 - (2 * qx * qx) - (2 * qz *qz);
		result[6] = (2 * qy * qz) - (2 * qx * qw);

		result[8] = (2 * qx * qz) - (2 * qy * qw);
		result[9] = (2 * qy * qz) + (2 * qx * qw);
		result[10] = 1 - (2 * qx *qx) - (2 * qy *qy);

		return result;
	}

	template <typename T>
	T Minor(std::array<T, 16> m, int r0, int r1, int r2, int c0, int c1, int c2)
	{
		return m[4 * r0 + c0] * (m[4 * r1 + c1] * m[4 * r2 + c2] - m[4 * r2 + c1] * m[4 * r1 + c2]) -
			m[4 * r0 + c1] * (m[4 * r1 + c0] * m[4 * r2 + c2] - m[4 * r2 + c0] * m[4 * r1 + c2]) +
			m[4 * r0 + c2] * (m[4 * r1 + c0] * m[4 * r2 + c1] - m[4 * r2 + c0] * m[4 * r1 + c1]);
	}

	template <typename T>
	void adjoint(std::array<T, 16> m, std::array<T, 16>& adjOut)
	{
		adjOut[0] = Minor(m, 1, 2, 3, 1, 2, 3);
		adjOut[1] = -Minor(m, 0, 2, 3, 1, 2, 3);
		adjOut[2] = Minor(m, 0, 1, 3, 1, 2, 3);
		adjOut[3] = -Minor(m, 0, 1, 2, 1, 2, 3);
		adjOut[4] = -Minor(m, 1, 2, 3, 0, 2, 3);
		adjOut[5] = Minor(m, 0, 2, 3, 0, 2, 3);
		adjOut[6] = -Minor(m, 0, 1, 3, 0, 2, 3);
		adjOut[7] = Minor(m, 0, 1, 2, 0, 2, 3);
		adjOut[8] = Minor(m, 1, 2, 3, 0, 1, 3);
		adjOut[9] = -Minor(m, 0, 2, 3, 0, 1, 3);
		adjOut[10] = Minor(m, 0, 1, 3, 0, 1, 3);
		adjOut[11] = -Minor(m, 0, 1, 2, 0, 1, 3);
		adjOut[12] = -Minor(m, 1, 2, 3, 0, 1, 2);
		adjOut[13] = Minor(m, 0, 2, 3, 0, 1, 2);
		adjOut[14] = -Minor(m, 0, 1, 3, 0, 1, 2);
		adjOut[15] = Minor(m, 0, 1, 2, 0, 1, 2);
	}

	template <typename T>
	float det(std::array<T, 16> m)
	{
		return m[0] * Minor(m, 1, 2, 3, 1, 2, 3) -
			m[1] * Minor(m, 1, 2, 3, 0, 2, 3) +
			m[2] * Minor(m, 1, 2, 3, 0, 1, 3) -
			m[3] * Minor(m, 1, 2, 3, 0, 1, 2);
	}

	template <typename T>
	void invertRowMajor(std::array<T, 16> m, std::array<T, 16>& invOut)
	{
		adjoint(m, invOut);

		float inv_det = 1.0f / det(m);
		for (int i = 0; i < 16; ++i)
			invOut[i] = invOut[i] * inv_det;
	}

	template <typename T>
	std::array<T, 16> invertMatrix(std::array<T, 16> arr)
	{
		std::array<T, 16> result = std::array<T, 16>();
		invertRowMajor(arr, result);
		return result;
	}

	template <typename T>
	std::array<T, 16> constructScaleMatrix(Vector<T, 3> Scale)
	{
		std::array<T, 16> temp = IdentityMatrix<T, 16>();
		temp[0] = Scale[0];
		temp[5] = Scale[1];
		temp[10] = Scale[2];
		return temp;
	}

	template <typename T>
	std::array<T, 16> constructRotationMatrix(Vector<T, 3> v)
	{
		auto q = toQuaternion(v[2], v[1], v[0]);
		auto result = QuaternionToMatrix(q);

		return result;
	}

	template <typename T>
	std::array<T, 16> constructTranslationMatrix(Vector<T, 3> Origin)
	{
		std::array<T, 16> temp = IdentityMatrix<T, 16>();
		temp[3] = Origin[0];
		temp[7] = Origin[1];
		temp[11] = Origin[2];
		return temp;
	}
}
