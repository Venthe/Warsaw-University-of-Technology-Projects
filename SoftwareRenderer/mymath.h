#pragma once
#include <array>
#include "types.h"

template <typename T, size_t X>
std::array <T, X> ArrayMultiplication(std::array <T, X> a, std::array <T, X> b)
{
	std::array <T, X> result;
	result.fill(0);
	for(int r = 0; r<sqrt(X);r++)
	{
		for(int c=0;c<sqrt(X);c++)
		{
			for(int inner = 0; inner < sqrt(X); inner++) result[r*sqrt(X) + c] += a[r * sqrt(X) + inner] * b[inner * sqrt(X) + c];
		}
	}

	return result;
}

template <typename T, size_t X>
std::array <T, X*X> IdentityMatrix()
{
	std::array <T, X*X> result;
	result.fill(0);
	for (int i = 0; i != X; i++)
	{
		result[static_cast<size_t>(i*X + i)] = 1;
	}
	return result;
}

template <typename T, size_t X>
void transformVectorByArray(std::array<T, X> t, Vector3<T>& v, bool retroProject = false)
{
	T result[4];
	for (int i = 0; i < sqrt(X); i++) result[i] = v[0] * t[i * 4] + v[1] * t[i * 4 + 1] + v[2] * t[i * 4 + 2] + 1 * t[i * 4 + 3];

	for (int i = 0; i < 4 - 1; i++) {
		if (retroProject) v[i] = result[i] / result[4 - 1];
		else v[i] = result[i];
	}
}
//std::array<double,9> calculateRotationMatrix(Camera camera)
//{
//	std::array<double, 9> rotationMatrix;
//
//	double rTemp[9];
//	double rx[9] = {
//		1,0,0,
//		0,std::cos(camera.Rotation[0]),-std::sin(camera.Rotation[0]),
//		0,std::sin(camera.Rotation[0]),std::cos(camera.Rotation[0])
//	};
//	double ry[9] = {
//		std::cos(camera.Rotation[1]),0,std::sin(camera.Rotation[1]),
//		0,1,0,
//		-std::sin(camera.Rotation[1]),0,std::cos(camera.Rotation[1])
//	};
//	double rz[9] = {
//		std::cos(camera.Rotation[2]),-std::sin(camera.Rotation[2]),0,
//		std::sin(camera.Rotation[2]),std::cos(camera.Rotation[2]),0,
//		0,0,1
//	};
//	for(int r = 0; r<3;r++)
//	{
//		for(int c=0;c<3;c++)
//		{
//			for(int inner = 0; inner<3;inner++)
//			{
//				rTemp[(r * 3) + c] += rx[(r*3) + inner] * ry[c+(inner*3)];
//				rotationMatrix[(r * 3) + c] += rTemp[(r * 3) + inner] * rz[c + (inner * 3)];
//			}
//		}
//	}
//
//	return rotationMatrix;
//}