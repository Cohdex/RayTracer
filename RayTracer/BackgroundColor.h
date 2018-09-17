#pragma once

#include "Background.h"

class BackgroundColor : public Background
{
private:
	glm::dvec3 color;

public:
	BackgroundColor(const glm::dvec3& color);

	virtual glm::dvec3 getColor(const Ray& ray) const override;
};
