#pragma once

#include <string>
#include <cmath>

#include "Vector3.h"
#include "Camera.h"


enum class LineTag {
	Line,
	Segment,
	Ray,
};

template<LineTag tag>
struct LineBase {

	Vec3f origin;
	Vec3f diff;

	void DebugDraw(const std::string& windowName);
	void Draw(const Camera* camera, uint32_t color);
};

using Line = LineBase<LineTag::Line>;
using Segment = LineBase<LineTag::Segment>;
using Ray = LineBase<LineTag::Ray>;
