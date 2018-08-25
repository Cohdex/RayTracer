#pragma once

class Math
{
	Math() = delete;

public:
	template<typename T>
	static T min(const T& a, const T& b)
	{
		return a < b ? a : b;
	}

	template<typename T>
	static T max(const T& a, const T& b)
	{
		return a > b ? a : b;
	}

	template<typename T, typename Q>
	static T lerp(const T& a, const T& b, Q x)
	{
		return (Q(1.0) - x) * a + x * b;
	}

	static Vec3 pow(const Vec3& vec, double a)
	{
		Vec3 result;
		result.x = std::pow(vec.x, a);
		result.y = std::pow(vec.y, a);
		result.z = std::pow(vec.z, a);
		return result;
	}

	static Vec3 sqrt(const Vec3& vec)
	{
		Vec3 result;
		result.x = std::sqrt(vec.x);
		result.y = std::sqrt(vec.y);
		result.z = std::sqrt(vec.z);
		return result;
	}
};
