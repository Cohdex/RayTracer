#pragma once

#include <cmath>
#include <ostream>

class Vec3
{
public:
	union
	{
		double data[3];
		struct
		{
			double x, y, z;
		};
		struct
		{
			double r, g, b;
		};
	};

	Vec3() : x(0.0), y(0.0), z(0.0) { }
	Vec3(double v) : x(v), y(v), z(v) { }
	Vec3(double x, double y, double z) : x(x), y(y), z(z) { }

	double& operator[](int i)
	{
		return data[i];
	}

	const double& operator[](int i) const
	{
		return data[i];
	}

	double lengthSquared() const
	{
		double x2 = x * x;
		double y2 = y * y;
		double z2 = z * z;
		return x2 + y2 + z2;
	}

	double length() const
	{
		double len2 = lengthSquared();
		return std::sqrt(len2);
	}

	double dot(const Vec3& right) const
	{
		return x * right.x + y * right.y + z * right.z;
	}

	Vec3 cross(const Vec3& right) const
	{
		double cx = (y * right.z) - (z * right.y);
		double cy = (-x * right.z) - (z * right.x);
		double cz = (x * right.y) - (y * right.x);
		return Vec3(cx, cy, cz);
	}

	Vec3& normalize()
	{
		double invLen = 1.0 / length();
		x *= invLen;
		y *= invLen;
		z *= invLen;
		return *this;
	}

	Vec3& operator+=(const Vec3& right)
	{
		x += right.x;
		y += right.y;
		z += right.z;
		return *this;
	}

	Vec3& operator-=(const Vec3& right)
	{
		x -= right.x;
		y -= right.y;
		z -= right.z;
		return *this;
	}

	Vec3& operator*=(const Vec3& right)
	{
		x *= right.x;
		y *= right.y;
		z *= right.z;
		return *this;
	}

	Vec3& operator/=(const Vec3& right)
	{
		x /= right.x;
		y /= right.y;
		z /= right.z;
		return *this;
	}
};

inline Vec3 operator+(const Vec3& left, const Vec3& right)
{
	return Vec3(left.x + right.x, left.y + right.y, left.z + right.z);
}
inline Vec3 operator+(const Vec3& right)
{
	return right;
}

inline Vec3 operator-(const Vec3& left, const Vec3& right)
{
	return Vec3(left.x - right.x, left.y - right.y, left.z - right.z);
}
inline Vec3 operator-(const Vec3& right)
{
	return Vec3(-right.x, -right.y, -right.z);
}

inline Vec3 operator*(const Vec3& left, const Vec3& right)
{
	return Vec3(left.x * right.x, left.y * right.y, left.z * right.z);
}

inline Vec3 operator/(const Vec3& left, const Vec3& right)
{
	return Vec3(left.x / right.x, left.y / right.y, left.z / right.z);
}

inline std::ostream& operator<<(std::ostream& os, const Vec3& vec)
{
	os << "Vec3(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
	return os;
}
