#include "Sphere.h"

#include <Novice.h>
#include <ImGuiManager.h>
#include "Matrix4x4.h"
#include "Camera.h"

Sphere::Sphere() {}
Sphere::~Sphere() {}



void Sphere::Init() {

	rotate_ = { 0.0f,0.0f,0.0f };
	center_ = { 0.0f,0.0f,0.0f };

	radius_ = 1.0f;
	color_ = 0xFFFFFFFF;

	subdivision_ = 16;

}



void Sphere::Update() {
#ifdef _DEBUG
	ImGui::Begin("Sphere");

	ImGui::DragFloat3("rotate", &rotate_.x, 0.01f);
	ImGui::DragFloat3("center", &center_.x, 0.1f);

	ImGui::End();
#endif // _DEBUG


}



void Sphere::Draw(const Camera& camera) {

	const float kLonEvery = (2.0f * 3.14f) / subdivision_; // 経度分割1つ分の角度
	const float kLatEvery = 3.14f / subdivision_; // 緯度分割1つ分の角度

	// 経度の方向に分割 -π/2 ~ π/2
	for(uint32_t latIndex = 0; latIndex < subdivision_; latIndex++) {
		float lat = -3.14f / 2.0f + kLatEvery * latIndex; // 現在の緯度

		// 経度の方向に分割 0 ~ 2π
		for(uint32_t lonIndex = 0; lonIndex < subdivision_; lonIndex++) {
			float lon = lonIndex * kLonEvery; // 現在の経度

			// world座標系でのa,b,cを求める
			Vec3f point[3];
			Vec3f screenPoint[3];

			// a
			point[0] = {
				(std::cosf(lat) * std::cosf(lon)) * radius_,
				(std::sinf(lat)) * radius_,
				(std::cosf(lat) * std::sinf(lon)) * radius_
			};

			// b
			point[1] = {
				(std::cosf(lat + kLatEvery) * std::cosf(lon)) * radius_,
				(std::sinf(lat + kLatEvery)) * radius_,
				(std::cosf(lat + kLatEvery) * std::sinf(lon)) * radius_
			};

			// c
			point[2] = {
				(std::cosf(lat) * std::cosf(lon + kLonEvery)) * radius_,
				(std::sinf(lat)) * radius_,
				(std::cosf(lat) * std::sinf(lon + kLonEvery)) * radius_
			};

			// screen座標系まで変換
			Matrix4x4 worldMatrix = Mat4::MakeAffine({ 1.0f,1.0f,1.0f }, rotate_, center_);
			Matrix4x4 wvpMatrix = worldMatrix * camera.GetMatVp();
			for(uint32_t i = 0; i < 3; i++) {
				Vec3f ndc = Mat4::Transform(point[i], wvpMatrix);
				screenPoint[i] = Mat4::Transform(ndc, camera.GetMatViewport());
			}

			// a -> b への線を描画
			Novice::DrawLine(
				static_cast<int>(screenPoint[0].x),
				static_cast<int>(screenPoint[0].y),
				static_cast<int>(screenPoint[1].x),
				static_cast<int>(screenPoint[1].y),
				color_
			);

			// a -> c への線を描画
			Novice::DrawLine(
				static_cast<int>(screenPoint[0].x),
				static_cast<int>(screenPoint[0].y),
				static_cast<int>(screenPoint[2].x),
				static_cast<int>(screenPoint[2].y),
				color_
			);

		}

	}

}
