#include "Sphere.h"

#include <Novice.h>
#include <ImGuiManager.h>
#include "Matrix4x4.h"
#include "Camera.h"


void Sphere::Init() {

	rotate = { 0.0f,0.0f,0.0f };
	center = { 0.0f,0.0f,0.0f };

	radius = 1.0f;

	subdivision = 16;

}

void Sphere::Init(const Vec3f& position, float rad) {
	Init();

	center = position;
	radius = rad;

}



void Sphere::Draw(const Camera* camera, uint32_t color) {

	const float kLonEvery = (2.0f * 3.14f) / subdivision; // 経度分割1つ分の角度
	const float kLatEvery = 3.14f / subdivision; // 緯度分割1つ分の角度

	// 経度の方向に分割 -π/2 ~ π/2
	for(uint32_t latIndex = 0; latIndex < subdivision; latIndex++) {
		float lat = -3.14f / 2.0f + kLatEvery * latIndex; // 現在の緯度

		// 経度の方向に分割 0 ~ 2π
		for(uint32_t lonIndex = 0; lonIndex < subdivision; lonIndex++) {
			float lon = lonIndex * kLonEvery; // 現在の経度

			// world座標系でのa,b,cを求める
			Vec3f point[3];
			Vec3f screenPoint[3];

			// a
			point[0] = {
				(std::cos(lat) * std::cos(lon)) * radius,
				(std::sin(lat)) * radius,
				(std::cos(lat) * std::sin(lon)) * radius
			};

			// b
			point[1] = {
				(std::cos(lat + kLatEvery) * std::cos(lon)) * radius,
				(std::sin(lat + kLatEvery)) * radius,
				(std::cos(lat + kLatEvery) * std::sin(lon)) * radius
			};

			// c
			point[2] = {
				(std::cos(lat) * std::cos(lon + kLonEvery)) * radius,
				(std::sin(lat)) * radius,
				(std::cos(lat) * std::sin(lon + kLonEvery)) * radius
			};

			// screen座標系まで変換
			Matrix4x4 worldMatrix = Mat4::MakeAffine({ 1.0f,1.0f,1.0f }, rotate, center);
			Matrix4x4 wvpMatrix = worldMatrix * camera->GetMatVp();
			for(uint32_t i = 0; i < 3; i++) {
				Vec3f ndc = Mat4::Transform(point[i], wvpMatrix);
				screenPoint[i] = Mat4::Transform(ndc, camera->GetMatViewport());
			}

			// a -> b への線を描画
			Novice::DrawLine(
				static_cast<int>(screenPoint[0].x),
				static_cast<int>(screenPoint[0].y),
				static_cast<int>(screenPoint[1].x),
				static_cast<int>(screenPoint[1].y),
				color
			);

			// a -> c への線を描画
			Novice::DrawLine(
				static_cast<int>(screenPoint[0].x),
				static_cast<int>(screenPoint[0].y),
				static_cast<int>(screenPoint[2].x),
				static_cast<int>(screenPoint[2].y),
				color
			);

		}

	}

}



void Sphere::DebugDraw(const std::string& windowName) {
	ImGui::Begin(windowName.c_str());


	///- 拡縮; 回転; 平行移動量
	if(ImGui::TreeNodeEx("Transform", true)) {

		//ImGui::DragFloat3("Scale", &scale_.x, 0.05f);
		ImGui::DragFloat3("Rotate", &rotate.x, 0.05f);
		ImGui::DragFloat3("Translate", &center.x, 0.05f);

		ImGui::TreePop();
	}

	ImGui::Spacing();

	///- 各種パラメータ
	if(ImGui::TreeNodeEx("Parameters", true)) {

		ImGui::DragFloat("Radius", &radius, 0.05f);

		ImGui::TreePop();
	}


	ImGui::End();
}
