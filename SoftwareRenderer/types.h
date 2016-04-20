#pragma once
#include <string>

template <class T>
class Vector3
{
	T t[3];
public:

	Vector3();
	Vector3(T a, T b, T c);

	std::string ToString();

	void operator()(const T a, const T b, const T c);
	T& operator+=(const Vector3<T>& rhs);
	T& operator-=(const Vector3<T>& rhs);
	void operator=(const T input);
	T& operator[](int i);

	friend T operator-(Vector3<T> lhs, const Vector3<T>& rhs)
	{
		lhs -= rhs;
		return lhs;
	}

	friend T operator+(Vector3<T> lhs, const Vector3<T>& rhs)
	{
		lhs += rhs;
		return lhs;
	}
};

template <class T>
Vector3<T>::Vector3()
{
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
T& Vector3<T>::operator+=(const Vector3<T>& rhs)
{
	t[0] += rhs[0];
	t[1] += rhs[1];
	t[2] += rhs[2];
	return *this;
}

template <class T>
T& Vector3<T>::operator-=(const Vector3<T>& rhs)
{
	t[0] -= rhs[0];
	t[1] -= rhs[1];
	t[2] -= rhs[2];
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
	T& operator-=(const Vector2<T>& rhs);
	T& operator+=(const Vector2<T>& rhs);
	T& operator[](int i);

	friend T operator+(Vector2<T> lhs, const Vector2<T>& rhs)
	{
		lhs += rhs;
		return lhs;
	}

	friend T operator-(Vector2<T> lhs, const Vector2<T>& rhs)
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
T& Vector2<T>::operator+=(const Vector2<T>& rhs)
{
	t[0] += rhs[0];
	t[1] += rhs[1];
	return *this;
}

template <class T>
T& Vector2<T>::operator-=(const Vector2<T>& rhs)
{
	t[0] -= rhs[0];
	t[1] -= rhs[1];
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
