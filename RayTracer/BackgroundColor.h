#pragma once

#include "Background.h"

class BackgroundColor : public Background
{
private:
	Vec3 color;

public:
	BackgroundColor(const Vec3& color);

	virtual Vec3 getColor(const Ray& ray) const override;
};
