#include "Image.h"
#include "Ray.h"
#include "Background.h"
#include "BackgroundColor.h"
#include "BackgroundGradient.h"

#include <memory>
#include <vector>

struct Sphere
{
	Vec3 center;
	double radius;
	Vec3 color;
};

struct RayHit
{
	Vec3 position;
	Vec3 normal;
};

Vec3 get_color(std::vector<Sphere> spheres, const Ray& ray, const Background* background);

bool sphere_hit(const Ray& ray, const Sphere& sphere, RayHit* rayHit)
{
	Vec3 oc = ray.getOrigin() - sphere.center;
	double a = ray.getDirection().lengthSquared();
	double b = 2.0 * oc.dot(ray.getDirection());
	double c = oc.lengthSquared() - sphere.radius*sphere.radius;
	double d = b*b - 4*a*c;
	if (d < 0.0)
	{
		return false;
	}
	else
	{
		if (rayHit != nullptr)
		{
			double t = (-b - std::sqrt(d)) / (2.0*a);
			Vec3 p = ray.getPoint(t);
			Vec3 n = (p - sphere.center).normalize();
			rayHit->position = p;
			rayHit->normal = n;
		}
		return true;
	}
}

int main(void)
{
	constexpr int w = 1000;
	constexpr int h = 500;
	Image image(w, h);

	std::unique_ptr<Background> background = std::make_unique<BackgroundGradient>(Vec3(0.5, 0.7, 1.0), Vec3(1.0, 1.0, 1.0));

	Vec3 lowerLeft(-2.0, -1.0, -1.0);
	Vec3 horizontal(4.0, 0.0, 0.0);
	Vec3 vertical(0.0, 2.0, 0.0);
	Vec3 origin(0.0, 0.0, 0.0);

	std::vector<Sphere> spheres;
	spheres.push_back({ Vec3(0.0, 0.0, -1.0), 0.5, Vec3(1.0, 0.0, 0.0) });
	spheres.push_back({ Vec3(0.3, 0.0, -1.3), 0.5, Vec3(0.0, 0.0, 1.0) });

	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			double u = (x + 0.5) / w;
			double v = (y + 0.5) / h;

			Vec3 direction(lowerLeft + horizontal*u + vertical*v);
			Ray ray(origin, direction);

			image.setPixel(x, y, get_color(spheres, ray, background.get()));
		}
	}

	image.write("output.png");

	return 0;
}

Vec3 get_color(std::vector<Sphere> spheres, const Ray& ray, const Background* background)
{
	for (Sphere& s : spheres)
	{
		RayHit rayHit;
		if (sphere_hit(ray, s, &rayHit))
		{
			Ray bounceRay(rayHit.position, rayHit.normal);
			//return background->getColor(bounceRay);
			return rayHit.normal * 0.5 + 0.5;
			//return s.color;
		}
	}
	return background->getColor(ray);
}
