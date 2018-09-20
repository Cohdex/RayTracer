#include "Plane.h"

Plane::Plane(const glm::dvec3& origin, const glm::dvec3 normal)
	: origin(origin), normal(normal)
{
}

bool Plane::hit(const Ray& ray, HitRecord* hitRecord) const
{
	double denom = glm::dot(normal, ray.getDirection());
	if (denom > 1.0e-6)
	{
		glm::dvec3 p = origin - ray.getOrigin();
		double t = glm::dot(p, normal) / denom;
		if (t >= 0.0)
		{
			if (hitRecord != nullptr)
			{
				hitRecord->t = t;
				hitRecord->position = ray.getPoint(t);
				hitRecord->normal = normal;
				hitRecord->textureU = hitRecord->position.x;
				hitRecord->textureV = -hitRecord->position.z;
			}
			return true;
		}
	}
	return false;
}
