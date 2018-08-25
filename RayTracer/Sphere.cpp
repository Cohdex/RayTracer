#include "Sphere.h"

#include "Math.h"

Sphere::Sphere(const Vec3& center, double radius)
	: center(center), radius(radius)
{
}

bool Sphere::hit(const Ray& ray, HitRecord* hitRecord) const
{
	Vec3 oc = ray.getOrigin() - center;
	double a = ray.getDirection().lengthSquared();
	double b = oc.dot(ray.getDirection());
	double c = oc.lengthSquared() - (radius * radius);
	double d = (b * b) - (a * c);

	if (d > 0.0)
	{
		auto recordData = [&](double t) {
			if (hitRecord != nullptr)
			{
				hitRecord->t = t;
				hitRecord->position = ray.getPoint(t);
				hitRecord->normal = (hitRecord->position - center).normalize();
			}
		};

		double t = (-b - std::sqrt(d)) / a;
		if (t > 0.0)
		{
			recordData(t);
			return true;
		}

		t = (-b + std::sqrt(d)) / a;
		if (t > 0.0)
		{
			recordData(t);
			return true;
		}
	}

	return false;
}
