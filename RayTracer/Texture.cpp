#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Math.h"

Texture::Texture(const std::string& filename)
{
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, nullptr, 3);
	pixels = std::vector<Vec3>(width * height);
	for (int i = 0; i < width * height; i++)
	{
		Vec3 p;
		p.x = data[i * 3 + 0];
		p.y = data[i * 3 + 1];
		p.z = data[i * 3 + 2];
		p /= 255.0;
		p = Math::pow(p, 2.2);
		pixels[i] = p;
	}
	stbi_image_free(data);
}

const Vec3& Texture::sample(double u, double v)
{
	int x = (int)std::floor(Math::clamp(u, 0.0, 1.0) * (width - 1));
	int y = (int)std::floor(Math::clamp(v, 0.0, 1.0) * (height - 1));
	return pixels[x + y * width];
}
