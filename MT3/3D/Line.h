#pragma once

#include <string>
#include <cmath>

#include "Vector3.h"
#include "Camera.h"

struct Line {
	Vec3f origin;
	Vec3f diff;

	void DebugDraw(const std::string& windowName);
	void Draw(const Camera* camera, uint32_t color);
};

struct Segment : public Line {};
struct Ray : public Line {};

