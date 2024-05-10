#pragma once

#include <string>

#include "Vector3.h"
#include "Camera.h"

struct Line {
	Vec3f origin;
	Vec3f diff;

	void DebugDraw(const std::string& windowName);
	void Draw(const Camera* camera);
};



using Ray = Line;
using Segment = Line;