#include "mymath.h"

float MyMath::DegreesToRadians(float d)
{
	return d * (static_cast<float>(M_PI) / 180.0f);
}
float MyMath::NormalizationToUnity(float value, float min, float max)
{
	return ((value - min) / (max - min));
}

bool MyMath::transformVectorByArray(std::array<float, 16> t, Vector<float, 3>& v, bool retroProject)
{
	bool rtrn = true;
	Vector<float, 4> result = Vector<float, 4>(0);


	//1
	for (int i = 0; i < 4; i++)
	{
		result[i] = v[0] * t[i * 4] + v[1] * t[i * 4 + 1] + v[2] * t[i * 4 + 2] + 1 * t[i * 4 + 3];
	}

	for (int i = 0; i < 3; i++)
	{
		if (retroProject) v[i] = result[i] / result[3];
		else v[i] = result[i];
	}
	if (retroProject)
	{
		if (result[2] < config.clipNear || result[2] > config.clipFar) rtrn = false;
		if ((v[0]<-1.f || v[0]>1.f) && (v[1]<-1.f || v[1]>1.f)) rtrn = false;
	}
	return rtrn;
}