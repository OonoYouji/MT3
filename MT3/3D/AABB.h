#pragma once 

#include <cmath>
#include <string>

#include "Vector3.h"


class Camera;

/// <summary>
/// Axis Aligned Bounding Box
/// </summary>
struct AABB {
	Vec3f min;
	Vec3f max;
	
	void Draw(const Camera* camera, uint32_t color);
	void DebugDraw(const std::string& windowName);

};