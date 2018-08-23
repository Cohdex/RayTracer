#pragma once

class Math
{
	Math() = delete;

public:
	template<typename T>
	static T min(T a, T b)
	{
		return a < b ? a : b;
	}

	template<typename T>
	static T max(T a, T b)
	{
		return a > b ? a : b;
	}

	template<typename T, typename Q>
	static T lerp(T a, T b, Q x)
	{
		return (Q(1.0) - x) * a + x * b;
	}
};
