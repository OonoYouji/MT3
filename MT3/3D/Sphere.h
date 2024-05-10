#pragma once

#include "Vector3.h"
#include <cmath>
#include <string>

class Camera;

class Sphere final {
public:

	Sphere();
	~Sphere();

	void Init();
	void Init(const Vec3f& position, float radius);
	void Update();
	void Draw(const Camera& camera);

	void DebugDraw(const std::string& windowName);

private:


	Vec3f rotate_;
	Vec3f center_;

	float radius_;
	uint32_t color_;

	uint32_t subdivision_;

public: ///- Getter

	const Vec3f& GetPosition() const { return center_; }
	float GetRadius() const { return radius_; }

	void SetColor(uint32_t color) {
		color_ = color;
	}

};