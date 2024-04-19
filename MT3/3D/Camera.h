#pragma once

#include "Vector3.h"
#include "Matrix4x4.h"


class Camera final {
public:

	Camera();
	~Camera();

	void Init();
	void Update();

private:

	Vec3f scale_;
	Vec3f rotate_;
	Vec3f translate_;

	Mat4 matWorld_;
	Mat4 matView_;
	Mat4 matProjection_;
	Mat4 matViewport_;

	Mat4 matVp_;


	void UpdateMatrix();


public: ///- getter

	const Mat4& GetMatVp() const { return matVp_; }
	const Mat4& GetMatViewport() const { return matViewport_; }

	const Vec3f& GetPosition() const { return translate_; }

};