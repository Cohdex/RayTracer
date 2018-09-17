#pragma once

#include "glm/glm.hpp"

#include <vector>
#include <string>

class Image
{
private:
	int width;
	int height;
	std::vector<glm::dvec3> data;

public:
	Image(int width, int height);

	int getWidth() const { return width; }
	int getHeight() const { return height; }

	glm::dvec3 getPixel(int x, int y) const;
	void setPixel(int x, int y, const glm::dvec3& color);

	void write(const std::string& filename) const;
};
