#include "Ray.h"

Ray::Ray(const Vec3& origin, const Vec3& direction)
	: origin(origin), direction(direction)
{
	this->direction.normalize();
}

Vec3 Ray::getPoint(double t) const
{
	return origin + direction * t;
}
