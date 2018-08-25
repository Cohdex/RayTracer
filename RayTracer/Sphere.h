#pragma once

#include "IHitable.h"

class Sphere : public IHitable
{
private:
	Vec3 center;
	double radius;

public:
	Sphere(const Vec3& center, double radius);

	virtual bool hit(const Ray& ray, HitRecord* hitRecord) const override;
};
