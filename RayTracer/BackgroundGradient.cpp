#include "BackgroundGradient.h"

#include "Math.h"

#include "Texture.h"
#include <memory>

std::unique_ptr<Texture> texture;

BackgroundGradient::BackgroundGradient(const Vec3& topColor, const Vec3& bottomColor)
	: topColor(topColor), bottomColor(bottomColor)
{
	texture = std::make_unique<Texture>("hexagon_pattern.jpg");
}

Vec3 BackgroundGradient::getColor(const Ray& ray) const
{
	//double t = ray.getDirection().y * 0.5 + 0.5;
	//return Math::pow(Math::lerp(bottomColor, topColor, t), 2.2);

	double u = std::asin(ray.getDirection().x) / Math::pi<double>() + 0.5;
	double v = std::asin(ray.getDirection().y) / Math::pi<double>() + 0.5;
	return texture->sample(u, v);
}
