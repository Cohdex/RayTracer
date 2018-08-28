#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ASSERT(x)
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

Vec3 Texture::sampleNearest(double u, double v)
{
	int x = (int)std::floor(Math::clamp(u, 0.0, 1.0) * (width - 1));
	int y = (int)std::floor(Math::clamp(v, 0.0, 1.0) * (height - 1));
	return pixels[x + y * width];
}

Vec3 Texture::sampleLinear(double u, double v)
{
	u = u * width - 0.5;
	v = v * height - 0.5;
	int x0 = (int)std::floor(u);
	int y0 = (int)std::floor(v);
	x0 = Math::clamp(x0, 0, width);
	y0 = Math::clamp(y0, 0, height);
	int x1 = x0 + 1;
	int y1 = y0 + 1;
	x1 = Math::clamp(x1, 0, width);
	y1 = Math::clamp(y1, 0, height);
	double uRatio = u - x0;
	double vRatio = v - y0;
	Vec3 ln0 = Math::lerp(pixels[x0 + y0 * width], pixels[x0 + y1 * width], uRatio);
	Vec3 ln1 = Math::lerp(pixels[x0 + y1 * width], pixels[x1 + y1 * width], uRatio);
	return Math::lerp(ln0, ln1, vRatio);
}

