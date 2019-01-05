#pragma once
#include "Math.h"
#include "Vector2.h"

class VectorMath
{
public:
	VectorMath() = default;

	static float getMagnitude(float x, float y)
	{
		return sqrtf(powf(x, 2) + powf(y, 2));
	}

	static double getMagnitude(double x, double y)
	{
		return sqrt(pow(x, 2) + pow(y, 2));
	}

	template<class T>
	static Vector2<T> NormalizeVector(T x, T y, T magnitude)
	{
		return Vector2<T>(x / magnitude, y / magnitude);
	}

	template<class T>
	static Vector2<T> NormalizeVector(Vector2<T> vectorA)
	{
		T magnitude = sqrt(pow(vectorA.x, 2) + pow(vectorA.y, 2));

		return Vector2<T>(vectorA.x / magnitude, vectorA.y / magnitude);
	}

	template<class T>
	static Vector2<T> getVector(T x1, T y1, T x2, T y2)
	{
		return Vector2<T>(x2 - x1, y2 - y1);
	}

private:
};
