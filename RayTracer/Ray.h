#pragma once

#include "Vec3.h"

class Ray
{
private:
	Vec3 origin;
	Vec3 direction;

public:
	Ray() { }
	Ray(const Vec3& origin, const Vec3& direction);

	const Vec3& getOrigin() const { return origin; }
	const Vec3& getDirection() const { return direction; }

	Vec3 getPoint(double t) const;
};
