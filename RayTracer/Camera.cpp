#include "Camera.h"

Camera::Camera()
{
	origin = glm::dvec3(0.0, 0.0, 0.0);
	lowerLeft = glm::dvec3(-2.0, -1.0, -1.0);
	horizontal = glm::dvec3(4.0, 0.0, 0.0);
	vertical = glm::dvec3(0.0, 2.0, 0.0);
}

Ray Camera::getRay(double u, double v) const
{
	glm::dvec3 direction(lowerLeft + (horizontal * u) + (vertical * v));
	return Ray(origin, direction);
}
