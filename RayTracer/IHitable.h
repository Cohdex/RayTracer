#pragma once

#include "Vec3.h"
#include "Ray.h"

struct HitRecord
{
	double t;
	Vec3 position;
	Vec3 normal;
};

class IHitable
{
public:
	virtual bool hit(const Ray& ray, HitRecord* hitRecord) const = 0;
};
