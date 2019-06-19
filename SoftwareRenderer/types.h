#pragma once
#include <string>
#include <array>
#include <initializer_list>

namespace MyMath
{
	template <typename T, size_t S>
	class Vector
	{
	protected:
		T t[S];
	public:
		static Vector<T, S> Zero() { return Vector<T, S>(); }
		Vector() { for (size_t i = 0; i < S; i++) t[i] = 0; }
		Vector(T val) { for (size_t i = 0; i < S; i++) t[i] = val; }

		Vector(std::initializer_list<T> l)
		{
			typename std::initializer_list<T>::iterator it;
			size_t i = 0;
			for (it = l.begin(); it != l.end(); ++it , i++) t[i] = *it;
		}

		void operator()(std::initializer_list<T> l)
		{
			typename std::initializer_list<T>::iterator it;
			size_t i = 0;
			for (it = l.begin(); it != l.end(); ++it , i++) t[i] = *it;
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

		T& operator[](int i) { return t[i]; }
		void operator=(const T input) { for (size_t i = 0; i < S; i++) t[i] = input; }

		friend bool operator==(Vector<T, S> lhs, Vector<T, S> rhs)
		{
			for (size_t i = 0; i < S; i++)
			{
				if (rhs[i] != lhs[i])
					return false;
			}
			return true;
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

		friend Vector<T, S> operator*(Vector<T, S> lhs, const T& rhs)
		{
			for (size_t i = 0; i < S; i++) lhs[i] = lhs[i] * rhs;
			return lhs;
		}

		friend Vector<T, S> operator*(const T& rhs, Vector<T, S> lhs)
		{
			for (size_t i = 0; i < S; i++) lhs[i] = lhs[i] * rhs;
			return lhs;
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

		static std::wstring ToString(const Vector<T, S>& q)
		{
			std::string result = "[ ";
			for (size_t i = 0; i < S; i++)
			{
				result += q[i] + " ";
			}
			result += " ]";

			std::wstring str2(result.length(), L' ');
			std::copy(result.begin(), result.end(), str2.begin());
			return str2;
		}
	};

	template <typename T>
	class Face
	{
	public:
		Vector<T, 4> v[3];

		Face(Vector<T, 4> a, Vector<T, 4> b, Vector<T, 4> c)
		{
			v[0] = a;
			v[1] = b;
			v[3] = c;
		}

		Face(Vector<T, 4> a[3]) { v = a; }

		Face()
		{
		}

		Vector<T, 4>& operator[](const int index) { return v[index]; }
	};

	namespace Vector3
	{
		template <typename T>
		static Vector<T, 3> Up() { return Vector<T, 3>({0, 1, 0}); }

		template <typename T>
		static Vector<T, 3> Down() { return (-1) * Vector3::Up<T>(); }

		template <typename T>
		static Vector<T, 3> Right() { return Vector<T, 3>({1, 0, 0}); }

		template <typename T>
		T DotProduct(Vector<T, 3> lhs, Vector<T, 3> rhs) { return lhs[0] * rhs[0] + lhs[1] * rhs[1] + lhs[2] * rhs[2]; }

		template <typename T>
		static Vector<T, 3> CrossProduct(Vector<T, 3> a, Vector<T, 3> b)
		{
			Vector<T, 3> temp;
			temp[0] = a[1] * b[2] - a[2] * b[1];
			temp[1] = a[2] * b[0] - a[0] * b[2];
			temp[2] = a[0] * b[1] - a[1] * b[0];
			return temp;
		}

		template <typename T>
		Vector<T, 4> toVector4(Vector<T, 3> vec, T augment)
		{
			Vector<T, 4> out;
			for (int i = 0; i < 3; i++) out[i] = vec[i];
			out[3] = augment;
			return out;
		}

		template <typename T>
		Vector<T, 4> toAugmentedVector4(Vector<T, 3> vec) { return toVector4(vec, 1); }

		template <typename T>
		Vector<T, 4> toAugmentedPointVector4(Vector<T, 3> vec) { return toVector4(vec, 0); }
	}

	namespace Vector4
	{
		template <typename T>
		Vector<T, 3> toVector3(Vector<T, 4> vec)
		{
			Vector<T, 3> out;
			for (int i = 0; i < 3; i++) out[i] = vec[i];
			return out;
		}
	}

	namespace Point2i
	{
		struct Structure
		{
			int x, y;

			Structure()
			{
				x = 0;
				y = 0;
			}

			Structure(int a, int b)
			{
				x = a;
				y = b;
			}
		};

		inline float CrossProduct(Point2i::Structure v1, Point2i::Structure v2) { return float(v1.x * v2.y) - float(v1.y * v2.x); }
	}

	typedef std::array<float, 16> Matrix4f;
	typedef Vector<float, 3> Vector3f;
	typedef Vector<float, 4> Vector4f;
	typedef Vector<unsigned char, 3> Vector3uc;
	typedef Vector<int, 2> Vector2i;
	typedef Face<float> Facef;
	typedef Vector3uc Color;
}
