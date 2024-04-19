#pragma once

#include "Vector3.h"
#include <cmath>

class Camera;

class Sphere final {
public:

	Sphere();
	~Sphere();

	void Init();
	void Update();
	void Draw(const Camera& camera);

private:

	Vec3f rotate_;
	Vec3f center_;
	
	float radius_;
	uint32_t color_;

	uint32_t subdivision_;



};