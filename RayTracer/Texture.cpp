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

glm::dvec3 Texture::sampleNearest(double u, double v)
{
	int x = (int)std::floor(glm::clamp(u, 0.0, 1.0) * (width - 1));
	int y = (int)std::floor(glm::clamp(v, 0.0, 1.0) * (height - 1));
	return pixels[x + y * width];
}

glm::dvec3 Texture::sampleLinear(double u, double v)
{
	u = u * width - 0.5;
	v = v * height - 0.5;
	int x0 = (int)std::floor(u);
	int y0 = (int)std::floor(v);
	x0 = glm::clamp(x0, 0, width - 1);
	y0 = glm::clamp(y0, 0, height - 1);
	int x1 = x0 + 1;
	int y1 = y0 + 1;
	x1 = glm::clamp(x1, 0, width - 1);
	y1 = glm::clamp(y1, 0, height - 1);
	double uRatio = u - x0;
	double vRatio = v - y0;
	glm::dvec3 ln0 = glm::mix(pixels[x0 + y0 * width], pixels[x0 + y1 * width], uRatio);
	glm::dvec3 ln1 = glm::mix(pixels[x0 + y1 * width], pixels[x1 + y1 * width], uRatio);
	return glm::mix(ln0, ln1, vRatio);
}

