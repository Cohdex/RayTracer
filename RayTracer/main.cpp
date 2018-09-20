#include "Image.h"
#include "Ray.h"
#include "Camera.h"
#include "Background.h"
#include "BackgroundColor.h"
#include "BackgroundGradient.h"
#include "IHitable.h"
#include "Sphere.h"
#include "Plane.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/common.hpp"

#include <memory>
#include <vector>
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <random>

static constexpr int width = 1800;
static constexpr int height = 900;
static constexpr int sampleCount = 16;

static void rowCompleted();
static void render_worker(Image* image, int startRow, int endRow);
static glm::dvec3 get_color(const Ray& ray, int bounceLimit);

static Camera camera;
static std::vector<std::unique_ptr<IHitable>> hitables;
static std::unique_ptr<Background> background;
static std::unique_ptr<Texture> texture;

int main(void)
{
	Image image(width, height);

	hitables.push_back(std::make_unique<Sphere>(glm::dvec3(0.4, 0.0, -1.3), 0.5));
	hitables.push_back(std::make_unique<Sphere>(glm::dvec3(0.0, 0.0, -1.0), 0.5));
	hitables.push_back(std::make_unique<Sphere>(glm::dvec3(1.0, 0.0, -0.5), 0.3));
	hitables.push_back(std::make_unique<Plane>(glm::dvec3(0.0, -0.5, 0.0), glm::normalize(-glm::dvec3(0.0, 1.0, 0.2))));

	background = std::make_unique<BackgroundGradient>(glm::dvec3(0.5, 0.7, 1.0), glm::dvec3(1.0, 1.0, 1.0));

	texture = std::make_unique<Texture>("hexagon_pattern.jpg");

	int numWorkers = std::thread::hardware_concurrency();
	std::vector<std::thread> workerThreads(numWorkers);

	auto startTime = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < numWorkers; i++)
	{
		int startRow = i * height / numWorkers;
		int endRow = (i + 1) * height / numWorkers;

		workerThreads[i] = std::thread(render_worker, &image, startRow, endRow);
	}

	for (auto& worker : workerThreads)
	{
		worker.join();
	}

	auto endTime = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> elapsedTime = endTime - startTime;

	std::cout << "Done! Took " << elapsedTime.count() << "s. Writing result..." << std::endl;
	image.write("output.png");

	std::cout << "Press Enter to exit...";
	std::cin.get();

	return 0;
}

static void rowCompleted()
{
	static std::mutex mutex;
	static unsigned int totalWork = (unsigned)width * (unsigned)height;
	static unsigned int completedWork = 0;
	static unsigned int percentCounter = 0;

	std::lock_guard<std::mutex> lock(mutex);

	completedWork += width;

	unsigned int percent = 100u * completedWork / totalWork;
	if (percent - percentCounter >= 10u)
	{
		percentCounter = percent;
		std::cout << "Progress: " << percent << "%" << std::endl;
	}
}

static void render_worker(Image* image, int startRow, int endRow)
{
	std::default_random_engine rndGen;
	std::uniform_real_distribution<double> rndDist(0.0, 1.0);
	auto rnd = std::bind(rndDist, rndGen);

	for (int y = startRow; y < endRow; y++)
	{
		for (int x = 0; x < width; x++)
		{
			glm::dvec3 color;
			for (int i = 0; i < sampleCount; i++)
			{
				double u = (x + rnd()) / width;
				double v = (y + rnd()) / height;

				Ray ray = camera.getRay(u, v);

				color += get_color(ray, 100);
			}
			color /= sampleCount;

			image->setPixel(x, y, color);
		}

		rowCompleted();
	}
}

static glm::dvec3 get_color(const Ray& ray, int bounceLimit)
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
		glm::dvec3 bounceDirection = glm::reflect(ray.getDirection(), closestHit.normal);
		Ray bounceRay(closestHit.position + bounceDirection * 1.0e-6, bounceDirection);
		glm::dvec3 bounceColor = (bounceLimit <= 0 ? background->getColor(bounceRay) : get_color(bounceRay, bounceLimit - 1));
		return glm::mix(texture->sampleNearest(closestHit.textureU, closestHit.textureV) * 0.96 + 0.04, bounceColor, 0.5) * (closestHit.normal * 0.5 + 0.5);
		//return glm::mix(bounceRay.getDirection() * 0.5 + 0.5, bounceColor, 0.5)  * (closestHit.normal * 0.5 + 0.5);
		//return bounceColor * 0.8;
	}

	return background->getColor(ray);
}
