#pragma once

#include "IHitable.h"

class Plane : public IHitable
{
private:
	glm::dvec3 origin;
	glm::dvec3 normal;

public:
	Plane(const glm::dvec3& origin, const glm::dvec3 normal);

	virtual bool hit(const Ray& ray, HitRecord* hitRecord) const override;
};
