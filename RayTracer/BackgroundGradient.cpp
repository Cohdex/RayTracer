#include "BackgroundGradient.h"

#include "Texture.h"

#include "glm/gtc/constants.hpp"

#include <memory>

static std::unique_ptr<Texture> texture;

BackgroundGradient::BackgroundGradient(const glm::dvec3& topColor, const glm::dvec3& bottomColor)
	: topColor(topColor), bottomColor(bottomColor)
{
	texture = std::make_unique<Texture>("hexagon_pattern.jpg");
}

glm::dvec3 BackgroundGradient::getColor(const Ray& ray) const
{
	//double t = ray.getDirection().y * 0.5 + 0.5;
	//return Math::pow(Math::lerp(bottomColor, topColor, t), 2.2);
	double textureU = std::asin(ray.getDirection().x) / glm::pi<double>() + 0.5;
	double textureV = std::asin(ray.getDirection().y) / glm::pi<double>() + 0.5;
	return texture->sampleLinear(textureU, textureV);
}
