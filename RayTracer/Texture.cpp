#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ASSERT(x)
#include "stb_image.h"

#include "glm/exponential.hpp"

Texture::Texture(const std::string& filename)
{
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, nullptr, 3);
	pixels = std::vector<glm::dvec3>(width * height);
	for (int i = 0; i < width * height; i++)
	{
		glm::dvec3 p;
		p.x = data[i * 3 + 0];
		p.y = data[i * 3 + 1];
		p.z = data[i * 3 + 2];
		p /= 255.0;
		p = glm::pow(p, glm::dvec3(2.2));
		pixels[i] = p;
	}
	stbi_image_free(data);
}

static int clampIndex(int i, int max)
{
	return glm::clamp(i, 0, max - 1);
}

static int repeatIndex(int i, int max)
{
	return (i % max + max) % max;
}

glm::dvec3 Texture::sampleNearest(double u, double v)
{
	int x = (int)glm::floor(u * width - 0.5);
	int y = (int)glm::floor(v * height - 0.5);
	x = repeatIndex(x, width);
	y = repeatIndex(y, height);
	return pixels[x + y * width];
}

glm::dvec3 Texture::sampleLinear(double u, double v)
{
	u = u * width - 0.5;
	v = v * height - 0.5;
	int x0 = (int)glm::floor(u);
	int y0 = (int)glm::floor(v);
	x0 = repeatIndex(x0, width);
	y0 = repeatIndex(y0, height);
	int x1 = x0 + 1;
	int y1 = y0 + 1;
	x1 = repeatIndex(x1, width);
	y1 = repeatIndex(y1, height);
	double uRatio = u - x0;
	double vRatio = v - y0;
	glm::dvec3 ln0 = glm::mix(pixels[x0 + y0 * width], pixels[x0 + y1 * width], uRatio);
	glm::dvec3 ln1 = glm::mix(pixels[x0 + y1 * width], pixels[x1 + y1 * width], uRatio);
	return glm::mix(ln0, ln1, vRatio);
}
