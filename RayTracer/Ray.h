#pragma once

#include "glm/glm.hpp"

class Ray
{
private:
	glm::dvec3 origin;
	glm::dvec3 direction;

public:
	Ray() { }
	Ray(const glm::dvec3& origin, const glm::dvec3& direction);

	const glm::dvec3& getOrigin() const { return origin; }
	const glm::dvec3& getDirection() const { return direction; }

	glm::dvec3 getPoint(double t) const;
};
