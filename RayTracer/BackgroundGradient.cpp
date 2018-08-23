#include "BackgroundGradient.h"

#include "Math.h"

BackgroundGradient::BackgroundGradient(const Vec3& topColor, const Vec3& bottomColor)
	: topColor(topColor), bottomColor(bottomColor)
{
}

Vec3 BackgroundGradient::getColor(const Ray& ray) const
{
	double t = ray.getDirection().y * 0.5 + 1.0;
	return Math::lerp(bottomColor, topColor, t);
}
