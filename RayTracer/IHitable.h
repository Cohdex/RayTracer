#pragma once

#include "Ray.h"

class IHitable;

struct HitRecord
{
	const IHitable* hit;
	double t;
	glm::dvec3 position;
	glm::dvec3 normal;
	double textureU;
	double textureV;
};

class IHitable
{
private:
	int materialIndex;

public:
	virtual ~IHitable() { }
	virtual bool hit(const Ray& ray, HitRecord* hitRecord) const = 0;
	void setMaterial(int materialIndex) { this->materialIndex = materialIndex; }
	int getMaterial() const { return this->materialIndex; }
};
