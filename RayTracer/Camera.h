#pragma once

#include "Ray.h"

class Camera
{
private:
	glm::dvec3 origin;
	glm::dvec3 lowerLeft;
	glm::dvec3 horizontal;
	glm::dvec3 vertical;

public:
	Camera();

	Ray getRay(double u, double v) const;
};
