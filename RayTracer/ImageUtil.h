#pragma once

#include <string>

#include "Image.h"

class ImageUtil
{
	ImageUtil() = delete;

public:
	static void writeImage(const std::string& filename, int width, int height, const Image& image);
};
