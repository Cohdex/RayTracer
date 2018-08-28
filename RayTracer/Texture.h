#pragma once

#include <string>
#include <vector>

#include "Vec3.h"

class Texture
{
private:
	std::vector<Vec3> pixels;
	int width;
	int height;

public:
	Texture(const std::string& filename);

	int getWidth() const { return width; }
	int getHeight() const { return height; }

	Vec3 sampleNearest(double u, double v);
	Vec3 sampleLinear(double u, double v);
};
