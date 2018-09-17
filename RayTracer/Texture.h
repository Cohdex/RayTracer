#pragma once

#include "glm/glm.hpp"

#include <string>
#include <vector>

class Texture
{
private:
	std::vector<glm::dvec3> pixels;
	int width;
	int height;

public:
	Texture(const std::string& filename);

	int getWidth() const { return width; }
	int getHeight() const { return height; }

	glm::dvec3 sampleNearest(double u, double v);
	glm::dvec3 sampleLinear(double u, double v);
};
