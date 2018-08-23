#pragma once

#include "Background.h"

class BackgroundGradient : public Background
{
private:
	Vec3 topColor;
	Vec3 bottomColor;

public:
	BackgroundGradient(const Vec3& topColor, const Vec3& bottomColor);

	virtual Vec3 getColor(const Ray& ray) const override;
};
