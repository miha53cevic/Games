#pragma once

template<class T>
class Vector2
{
public:
	Vector2()
		: x(0)
		, y(0)
	{}
	Vector2(T x, T y)
	{
		this->x = x;
		this->y = y;
	}

	T x;
	T y;
};
