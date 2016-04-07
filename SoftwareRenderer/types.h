#pragma once
template <class T>
class Vector3
{
private:
	T t[3];
public:
	Vector3(T a, T b, T c)
	{
		t[0] = a;
		t[1] = b;
		t[2] = c;
	}

	T& operator[](int i)
	{
		return static_cast<T>(t[i]);
	}

	void operator()(const T a, const T b, const T c)
	{
		t[0] = a;
		t[1] = b;
		t[2] = c;
	}

	T& operator+=(const Vector3<T>& rhs)
	{
		t[0] += rhs[0];
		t[1] += rhs[1];
		t[2] += rhs[2];
		return *this;
	}

	friend T operator+(Vector3<T> lhs, const Vector3<T>& rhs)
	{
		lhs += rhs;
		return lhs;
	}

	T& operator-=(const Vector3<T>& rhs)
	{
		t[0] -= rhs[0];
		t[1] -= rhs[1];
		t[2] -= rhs[2];
		return *this;
	}

	friend T operator-(Vector3<T> lhs, const Vector3<T>& rhs)
	{
		lhs -= rhs;
		return lhs;
	}

	void operator=(const T input)
	{
		for (int i = 0; i < 3; i++)
		{
			t[i] = input;
		}
	}

	Vector3()
	{
		return;
	}
};

template <class T>
class Vector2
{
private:
	T t[2];
public:
	Vector2()
	{
		return;
	}

	Vector2(T a, T b)
	{
		t[0] = a;
		t[1] = b;
	}

	T& operator[](int i)
	{
		return static_cast<T>(t[i]);
	}

	void operator()(const T a, const T b)
	{
		t[0] = a;
		t[1] = b;
	}

	T& operator+=(const Vector2<T>& rhs)
	{
		t[0] += rhs[0];
		t[1] += rhs[1];
		return *this;
	}

	friend T operator+(Vector2<T> lhs, const Vector2<T>& rhs)
	{
		lhs += rhs;
		return lhs;
	}

	T& operator-=(const Vector2<T>& rhs)
	{
		t[0] -= rhs[0];
		t[1] -= rhs[1];
		return *this;
	}

	friend T operator-(Vector2<T> lhs, const Vector2<T>& rhs)
	{
		lhs -= rhs;
		return lhs;
	}

	void operator=(const T input)
	{
		for (int i = 0; i < 2; i++)
		{
			t[i] = input;
		}
	}
};

