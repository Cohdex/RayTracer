#include "BackgroundColor.h"

BackgroundColor::BackgroundColor(const Vec3& color)
	: color(color)
{
}

Vec3 BackgroundColor::getColor(const Ray& ray) const
{
	return color;
}
