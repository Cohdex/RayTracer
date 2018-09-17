#pragma once

#include "Background.h"

class BackgroundGradient : public Background
{
private:
	glm::dvec3 topColor;
	glm::dvec3 bottomColor;

public:
	BackgroundGradient(const glm::dvec3& topColor, const glm::dvec3& bottomColor);

	virtual glm::dvec3 getColor(const Ray& ray) const override;
};
