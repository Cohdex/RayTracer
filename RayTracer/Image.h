#pragma once

#include "Vec3.h"

#include <vector>

class Image
{
private:
	int width;
	int height;
	std::vector<Vec3> data;

public:
	Image(int width, int height);

	int getWidth() const { return width; }
	int getHeight() const { return height; }

	Vec3 getPixel(int x, int y) const;
	void setPixel(int x, int y, const Vec3& color);
};
