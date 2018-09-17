#include "Ray.h"

Ray::Ray(const glm::dvec3& origin, const glm::dvec3& direction)
	: origin(origin), direction(glm::normalize(direction))
{
}

glm::dvec3 Ray::getPoint(double t) const
{
	return origin + direction * t;
}
