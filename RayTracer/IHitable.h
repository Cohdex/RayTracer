#pragma once

#include "Ray.h"

struct HitRecord
{
	double t;
	glm::dvec3 position;
	glm::dvec3 normal;
	double textureU;
	double textureV;
};

class IHitable
{
public:
	virtual ~IHitable() { }
	virtual bool hit(const Ray& ray, HitRecord* hitRecord) const = 0;
};
