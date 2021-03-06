#include "Image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_ASSERT(x)
#define STBI_MSC_SECURE_CRT
#include "stb_image_write.h"

#include "glm/exponential.hpp"

Image::Image(int width, int height)
	: width(width), height(height), data(width * height)
{
}

glm::dvec3 Image::getPixel(int x, int y) const
{
	return data[x + y * width];
}

void Image::setPixel(int x, int y, const glm::dvec3& color)
{
	data[x + y * width] = color;
}

void Image::write(const std::string& filename) const
{
	int comp = 3;
	int stride = comp * width;

	std::vector<unsigned char> data(width * height * comp);

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			glm::dvec3 pixel = getPixel(x, y);
			pixel = glm::pow(pixel, glm::dvec3(1.0 / 2.2));
			int index = (x + y * width) * comp;
			for (int i = 0; i < comp; i++)
			{
				data[index + i] = (unsigned char)glm::min((int)(pixel[i] * 256), 255);
			}
		}
	}

	stbi_flip_vertically_on_write(true);
	stbi_write_png(filename.c_str(), width, height, comp, data.data(), stride);
}
