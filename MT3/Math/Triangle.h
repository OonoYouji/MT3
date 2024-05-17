#pragma once

#include <string>
#include <cmath>
#include "Vector3.h"

class Camera;

struct Triangle {
	Vec3f origin;
	Vec3f vertices[3];
	
	void DebugDraw(const std::string& windowName);
	void Draw(const Camera* camera, uint32_t color);
};