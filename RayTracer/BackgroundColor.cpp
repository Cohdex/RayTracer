#include "BackgroundColor.h"

BackgroundColor::BackgroundColor(const glm::dvec3& color)
	: color(color)
{
}

glm::dvec3 BackgroundColor::getColor(const Ray& ray) const
{
	return color;
}
