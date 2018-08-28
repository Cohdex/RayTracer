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
#include <iostream>

static Vec3 get_color(const Ray& ray);

static std::unique_ptr<Background> background;
static std::vector<std::unique_ptr<IHitable>> hitables;
static std::unique_ptr<Texture> texture;

int main(void)
{
	constexpr int w = 1200;
	constexpr int h = 600;
	Image image(w, h);

	background = std::make_unique<BackgroundGradient>(Vec3(0.5, 0.7, 1.0), Vec3(1.0, 1.0, 1.0));

	Vec3 lowerLeft(-2.0, -1.0, -1.0);
	Vec3 horizontal(4.0, 0.0, 0.0);
	Vec3 vertical(0.0, 2.0, 0.0);
	Vec3 origin(0.0, 0.0, 0.0);

	hitables.push_back(std::make_unique<Sphere>(Vec3(0.4, 0.0, -1.3), 0.5));
	hitables.push_back(std::make_unique<Sphere>(Vec3(0.0, 0.0, -1.0), 0.5));

	texture = std::make_unique<Texture>("hexagon_pattern.jpg");

	int totalWork = w * h;
	int completedWork = 0;
	int percentCounter = 0;

	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			double u = (x + 0.5) / w;
			double v = (y + 0.5) / h;

			Vec3 direction(lowerLeft + horizontal*u + vertical*v);
			Ray ray(origin, direction);

			Vec3 color = get_color(ray);
			image.setPixel(x, y, color);

			completedWork++;
			int percent = 100 * completedWork / totalWork;
			if (percent - percentCounter >= 10)
			{
				percentCounter = percent;
				std::cout << "Progress: " << percent << "%" << std::endl;
			}
		}
	}
	std::cout << "Done! Writing result...";

	image.write("output.png");

	return 0;
}

static Vec3 get_color(const Ray& ray)
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
		//return background->getColor(bounceRay);
		//return closestHit.normal * 0.5 + 0.5;
		return Math::lerp(texture->sampleLinear(closestHit.textureU, closestHit.textureV) * 0.96 + 0.04, background->getColor(bounceRay), 0.5) * (closestHit.normal * 0.5 + 0.5);
	}

	return background->getColor(ray);
}
