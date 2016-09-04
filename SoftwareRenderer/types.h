#pragma once
#include <string>
#include <initializer_list>

//Base class for numerical Vectors
template <typename T, size_t S>
class Vector
{
protected:
	T t[S];
public:
	static Vector<T, S> Zero()
	{
		return Vector<T, S>();
	}

	Vector()
	{
		for (size_t i = 0; i < S; i++) t[i] = 0;
	}
	Vector(T val)
	{
		for (size_t i = 0; i < S; i++) t[i] = val;
	}

	Vector(std::initializer_list<T> l)
	{
		std::initializer_list<T>::iterator it;
		size_t i = 0;
		for (it = l.begin(); it != l.end(); ++it, i++) t[i] = *it;
	}

	void operator()(std::initializer_list<T> l)
	{
		std::initializer_list<T>::iterator it;
		size_t i = 0;
		for (it = l.begin(); it != l.end(); ++it, i++) t[i] = *it;
	}

	std::string ToString()
	{
		std::string str = "";
		if (typeid(T) == typeid(float)) for (size_t i = 0; i < S; i++) str += "(" + std::to_string(t[i]) + ")";
		return str;
	}

	T Magnitude()
	{
		T mag = 0;
		for (size_t i = 0; i < S; i++) mag += pow(t[i], 2.f);
		return sqrt(mag);
	}

	Vector<T, S> Normalize()
	{
		Vector<T, S> temp = Vector<T, S>();
		for (size_t i = 0; i < S; i++) temp[i] = this->t[i] / this->Magnitude();
		return temp;
	}

	T& operator[](int i)
	{
		return t[i];
	}

	void operator=(const T input)
	{
		for (size_t i = 0; i < S; i++) t[i] = input;
	}

	friend Vector<T, S> operator-(Vector<T, S> lhs, const Vector<T, S>& rhs)
	{
		lhs -= rhs;
		return lhs;
	}

	friend Vector<T, S> operator+(Vector<T, S> lhs, const Vector<T, S>& rhs)
	{
		lhs += rhs;
		return lhs;
	}

	friend Vector<T, S>& operator*(Vector<T, S> lhs, const T& rhs)
	{
		Vector<T, S> temp;
		for (size_t i = 0; i < S; i++) temp[i] = lhs[i] * rhs;
		return temp;
	}

	friend Vector<T, S>& operator*(const T& rhs, Vector<T, S> lhs)
	{
		Vector<T, S> temp;
		for (size_t i = 0; i < S; i++) temp[i] = lhs[i] * rhs;
		return temp;
	}

	friend Vector<T, S>& operator/(Vector<T, S> lhs, const T& rhs)
	{
		Vector<T, S> temp;
		for (size_t i = 0; i < S; i++) temp[i] = lhs[i] / rhs;
		return temp;
	}

	Vector<T, S>& operator+=(const Vector<T, S>& rhs)
	{
		for (size_t i = 0; i < S; i++) t[i] += rhs.t[i];
		return *this;
	}

	Vector<T, S>& operator-=(const Vector<T, S>& rhs)
	{
		for (size_t i = 0; i < S; i++) t[i] -= rhs.t[i];
		return *this;
	}

	Vector<T, S>& operator*=(const T& rhs)
	{
		for (size_t i = 0; i < S; i++) t[i] *= rhs.t[i];
		return *this;
	}

	Vector<T, S>& operator/=(const T& rhs)
	{
		for (size_t i = 0; i < S; i++) t[i] /= rhs.t[i];
		return *this;
	}
};

namespace Vector3
{
	template <typename T>
	static Vector<T, 3> Up()
	{
		return Vector<T, 3>({ 0, 1., 0 });
	}

	template <typename T>
	static T DotProduct(Vector<T, 3> lhs, Vector<T, 3> rhs)
	{
		return lhs[0] * rhs[0] + lhs[1] * rhs[1] + lhs[2] * rhs[2];
	}

	template <typename T>
	static Vector<T, 3> CrossProduct(Vector<T, 3> a, Vector<T, 3> b)
	{
		Vector<T, 3> temp;
		temp[0] = a[1] * b[2] - a[2] * b[1];
		temp[1] = a[2] * b[0] - a[0] * b[2];
		temp[2] = a[0] * b[1] - a[1] * b[0];
		return temp;
	}
}

//namespace Quaternion
//{
//	template <typename T>
//	Vector<T, 4> Multiplication(Vector<T, 4> a, Vector<T, 4> b)
//	{
//		Vector<T, 4> temp;
//		temp[0] = a[0] * b[0] - a[1] * b[1] - a[2] * b[2] - a[3] * b[3];
//		temp[1] = a[0] * b[1] + a[1] * b[0] + a[2] * b[3] - a[3] * b[2];
//		temp[2] = a[0] * b[2] - a[1] * b[3] + a[2] * b[0] + a[3] * b[1];
//		temp[3] = a[0] * b[3] + a[1] * b[2] - a[2] * b[1] + a[3] * b[0];
//		return temp;
//	}
//}

namespace Point2D {
	struct Structure
	{
		int x, y;
		Structure() {}
		Structure(int a, int b) { x = a; y = b; }
	};

	inline float CrossProduct(Point2D::Structure v1, Point2D::Structure v2)
	{
		return static_cast<float>(v1.x * v2.y) - static_cast<float>(v1.y * v2.x);
	}
}