#pragma once
#include <vector>

template <class T>
class ThreeTuple
{
private:
	T t[3];
public:
	ThreeTuple(T a, T b, T c)
	{
		t[0] = a;
		t[1] = b;
		t[2] = c;
	}
	T &operator[](int i){
		return static_cast<T>(t[i]);
	}
	void operator()(const T a, const T b, const T c){
		t[0] = a;
		t[1] = b;
		t[2] = c;
	}
	void operator=(const T input){
		for (int i = 0; i < 3;i++)
		{
			t[i] = input;
		}
	}
	ThreeTuple()
	{
		return;
	}
};

class ObjModel
{
public:
	ThreeTuple<double> Origin = ThreeTuple<double>(0.0, 0.0, 0.0);
	ThreeTuple<double> Scale = ThreeTuple<double>(1.0, 1.0, 1.0);
	std::vector<ThreeTuple<double>> Vertex;
	std::vector<ThreeTuple<int>> Face;
	ObjModel();
	ObjModel(char * path);
	int ReadObj(char * path);
};
