#include "Image.h"

Image::Image(int width, int height)
	: width(width), height(height), data(width * height)
{
}

Vec3 Image::getPixel(int x, int y) const
{
	return data[x + y * width];
}

void Image::setPixel(int x, int y, const Vec3& color)
{
	data[x + y * width] = color;
}
