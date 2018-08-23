#pragma once

#include "Vec3.h"
#include "Ray.h"

class Background
{
public:
	Background() { }
	virtual ~Background() { }

	virtual Vec3 getColor(const Ray& ray) const = 0;
};
