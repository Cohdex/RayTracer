#include "Image.h"
#include "Ray.h"
#include "Background.h"
#include "BackgroundColor.h"
#include "BackgroundGradient.h"
#include "IHitable.h"
#include "Sphere.h"
#include "Math.h"
#include "Texture.h"

#include <memory>
#include <vector>

Vec3 get_color(const std::vector<std::unique_ptr<IHitable>>& hitables, const Ray& ray, const Background* background);

int main(void)
{
	constexpr int w = 600;
	constexpr int h = 300;
	Image image(w, h);

	std::unique_ptr<Background> background = std::make_unique<BackgroundGradient>(Vec3(0.5, 0.7, 1.0), Vec3(1.0, 1.0, 1.0));

	Vec3 lowerLeft(-2.0, -1.0, -1.0);
	Vec3 horizontal(4.0, 0.0, 0.0);
	Vec3 vertical(0.0, 2.0, 0.0);
	Vec3 origin(0.0, 0.0, 0.0);

	std::vector<std::unique_ptr<IHitable>> hitables;
	hitables.push_back(std::make_unique<Sphere>(Vec3(0.4, 0.0, -1.3), 0.5));
	hitables.push_back(std::make_unique<Sphere>(Vec3(0.0, 0.0, -1.0), 0.5));

	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			double u = (x + 0.5) / w;
			double v = (y + 0.5) / h;

			Vec3 direction(lowerLeft + horizontal*u + vertical*v);
			Ray ray(origin, direction);

			image.setPixel(x, y, get_color(hitables, ray, background.get()));
		}
	}

	image.write("output.png");

	return 0;
}

Vec3 get_color(const std::vector<std::unique_ptr<IHitable>>& hitables, const Ray& ray, const Background* background)
{
	HitRecord closestHit;
	closestHit.t = -1.0;
	for (const std::unique_ptr<IHitable>& h : hitables)
	{
		HitRecord hitRecord;
		if (h->hit(ray, &hitRecord) && (closestHit.t <= 0.0 || hitRecord.t < closestHit.t))
		{
			closestHit = hitRecord;
		}
	}

	if (closestHit.t > 0.0)
	{
		Ray bounceRay(closestHit.position, -closestHit.normal);
		return background->getColor(bounceRay);
		//return hitRecord.normal * 0.5 + 0.5;
	}

	return background->getColor(ray);
}
