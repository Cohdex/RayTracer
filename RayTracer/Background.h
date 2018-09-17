#pragma once

#include "Ray.h"

class Background
{
public:
	Background() { }
	virtual ~Background() { }

	virtual glm::dvec3 getColor(const Ray& ray) const = 0;
};
