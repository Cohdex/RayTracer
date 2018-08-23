#include "ImageUtil.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_MSC_SECURE_CRT
#include "stb_image_write.h"

#include "Math.h"

void ImageUtil::writeImage(const std::string& filename, int width, int height, const Image& image)
{
	int comp = 3;
	int stride = comp * width;

	unsigned char* data = new unsigned char[width * height * comp];
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			Vec3 pixel = image.getPixel(x, y);
			int index = (x + y * width) * comp;
			for (int i = 0; i < comp; i++)
			{
				double p = pixel[i];
				//p = std::pow(p, 1.0 / 2.2);
				unsigned char c = (unsigned char)Math::min((int)(p * 256), 255);
				data[index + i] = c;
			}
		}
	}

	stbi_flip_vertically_on_write(true);
	stbi_write_png(filename.c_str(), width, height, comp, data, stride);

	delete[] data;
}
