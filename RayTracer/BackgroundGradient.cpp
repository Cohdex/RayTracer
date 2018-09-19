#include "BackgroundGradient.h"

#include "Texture.h"

#include "glm/exponential.hpp"
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
#if 1
	double t = ray.getDirection().y * 0.5 + 0.5;
	return glm::pow(glm::mix(bottomColor, topColor, t), glm::dvec3(2.2));
#else
	double textureU = std::asin(ray.getDirection().x) / glm::pi<double>() + 0.5;
	double textureV = std::asin(ray.getDirection().y) / glm::pi<double>() + 0.5;
	return texture->sampleLinear(textureU, textureV);
#endif
}
