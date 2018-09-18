#include "Sphere.h"

#include "glm/gtc/constants.hpp"
#include "glm/gtx/norm.hpp"

Sphere::Sphere(const glm::dvec3& center, double radius)
	: center(center), radius(radius)
{
}

bool Sphere::hit(const Ray& ray, HitRecord* hitRecord) const
{
	glm::dvec3 oc = ray.getOrigin() - center;
	double a = glm::length2(ray.getDirection());
	double b = glm::dot(oc, ray.getDirection());
	double c = glm::length2(oc) - (radius * radius);
	double d = (b * b) - (a * c);

	if (d > 0.0)
	{
		auto recordData = [&](double t) {
			if (hitRecord != nullptr)
			{
				hitRecord->t = t;
				hitRecord->position = ray.getPoint(t);
				hitRecord->normal = glm::normalize(hitRecord->position - center);
				hitRecord->textureU = glm::asin(hitRecord->normal.x) / glm::pi<double>() + 0.5;
				hitRecord->textureV = glm::asin(hitRecord->normal.y) / glm::pi<double>() + 0.5;
			}
		};

		double t = (-b - glm::sqrt(d)) / a;
		if (t > 0.0)
		{
			recordData(t);
			return true;
		}

		t = (-b + glm::sqrt(d)) / a;
		if (t > 0.0)
		{
			recordData(t);
			return true;
		}
	}

	return false;
}
