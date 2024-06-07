#pragma once

#include "Vector3.h"
#include <cmath>
#include <string>

class Camera;

struct Sphere {

	Vec3f rotate;
	Vec3f center;

	float radius;

	uint32_t subdivision;

	void Init();
	void Init(const Vec3f& position, float rad);
	void Draw(const Camera* camera, uint32_t color);

	void DebugDraw(const std::string& windowName);

};