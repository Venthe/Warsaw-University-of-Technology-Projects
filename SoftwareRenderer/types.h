#pragma once
#include <string>

template <class T>
class Vector3
{
	T t[3];
public:

	Vector3();
	Vector3(T a, T b, T c);

	static Vector3<T> Up()
	{
		return Vector3<T>(0, 1, 0);
	}

	static Vector3<T> Down()
	{
		return Vector3<T>(0, -1, 0);
	}

	std::string ToString();

	Vector3<T> Normalize()
	{
		double length = sqrt((t[0]*t[0]) + (t[1] * t[1]) + (t[2] * t[2]));
		if (length == 0) return Vector3<T>(0, 0, 0);
		else if (length < 0.0) length *= -1.0;
		return Vector3<T>(t[0]/ length,t[1]/ length,t[2]/ length);
		//return Vector3<T>(1/ length,1/ length,1/ length);
	}
	T Length()
	{
		return std::sqrt(t[0]*t[0] + t[1] * t[1] + t[2] * t[2]);
	}

	void operator()(const T a, const T b, const T c);
	Vector3<T>& operator+=(const Vector3<T>& rhs);
	Vector3<T>& operator-=(const Vector3<T>& rhs);
	void operator=(const T input);
	T& operator[](int i);

	friend Vector3<T> operator-(Vector3<T> lhs, const Vector3<T>& rhs)
	{
		lhs -= rhs;
		return lhs;
	}

	friend Vector3<T> operator+(Vector3<T> lhs, const Vector3<T>& rhs)
	{
		lhs += rhs;
		return lhs;
	}
};

template <class T>
Vector3<T>::Vector3()
{
	for (int i = 0; i < 3; i++) t[i] = 0;
	return;
}

template <class T>
Vector3<T>::Vector3(T a, T b, T c)
{
	t[0] = a;
	t[1] = b;
	t[2] = c;
}

template <class T>
T& Vector3<T>::operator[](int i)
{
	return static_cast<T>(t[i]);
}

template <class T>
void Vector3<T>::operator()(const T a, const T b, const T c)
{
	t[0] = a;
	t[1] = b;
	t[2] = c;
}

template <class T>
Vector3<T>& Vector3<T>::operator+=(const Vector3<T>& rhs)
{

	t[0] += rhs.t[0];
	t[1] += rhs.t[1];
	t[2] += rhs.t[2];
	return *this;
}

template <class T>
Vector3<T>& Vector3<T>::operator-=(const Vector3<T>& rhs)
{

	t[0] -= rhs.t[0];
	t[1] -= rhs.t[1];
	t[2] -= rhs.t[2];
	return *this;
}

template <class T>
void Vector3<T>::operator=(const T input)
{
	for (int i = 0; i < 3; i++)
	{
		t[i] = input;
	}
}

template <class T>
std::string Vector3<T>::ToString()
{
	std::string str = std::string("(") + std::to_string(t[0]) + "," + std::to_string(t[1]) + "," + std::to_string(t[2]) + ")";
	return str;
}

template <class T>
class Vector2
{
	T t[2];
public:
	Vector2();
	Vector2(T a, T b);

	std::string ToString();

	void operator()(const T a, const T b);
	void operator=(const T input);
	Vector2<T>& operator-=(const Vector2<T>& rhs);
	Vector2<T>& operator+=(const Vector2<T>& rhs);
	T& operator[](int i);

	friend Vector2<T> operator+(Vector2<T> lhs, const Vector2<T>& rhs)
	{
		lhs += rhs;
		return lhs;
	}

	friend Vector2<T> operator-(Vector2<T> lhs, const Vector2<T>& rhs)
	{
		lhs -= rhs;
		return lhs;
	}
};


template <class T>
Vector2<T>::Vector2()
{
	return;
}

template <class T>
Vector2<T>::Vector2(T a, T b)
{
	t[0] = a;
	t[1] = b;
}

template <class T>
T& Vector2<T>::operator[](int i)
{
	return static_cast<T>(t[i]);
}

template <class T>
void Vector2<T>::operator()(const T a, const T b)
{
	t[0] = a;
	t[1] = b;
}

template <class T>
Vector2<T>& Vector2<T>::operator+=(const Vector2<T>& rhs)
{
	t[0] += rhs.t[1];
	t[1] += rhs.t[2];
	return *this;
}

template <class T>
Vector2<T>& Vector2<T>::operator-=(const Vector2<T>& rhs)
{
	t[0] -= rhs.t[1];
	t[1] -= rhs.t[2];
	return *this;
}

template <class T>
void Vector2<T>::operator=(const T input)
{
	for (int i = 0; i < 2; i++)
	{
		t[i] = input;
	}
}

template <class T>
std::string Vector2<T>::ToString()
{
	std::string str = std::string("(") + std::to_string(t[0]) + "," + std::to_string(t[1]) + ")";
	return str;
}

template <class T>
Vector3<T> CrossProduct(Vector3<T> a, Vector3<T>b)
{
	Vector3<T> temp;
	temp[0] = a[1] * b[2] - a[2] * b[1];
	temp[1] = a[2] * b[0] - a[0] * b[2];
	temp[2] = a[0] * b[1] - a[1] * b[0];
	return temp;
}

template <typename T>
T DotProduct(Vector3<T> a, Vector3<T>b)
{
	return a[0]*b[0] + a[1] * b[1] + a[2] * b[2];
}