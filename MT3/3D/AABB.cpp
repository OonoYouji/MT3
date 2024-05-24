#include "AABB.h"

#include "MyMath.h"
#include <array>

#include <ImGuiManager.h>

void AABB::Draw(const Camera* camera, uint32_t color) {

	///- 頂点の配列
	std::array<Vec3f, 8> points{
		/// 0 ~ 3 -> 奥
		Vec3f(min.x, max.y, max.z),	//- LT
		Vec3f(max.x, max.y, max.z),	//- RT
		Vec3f(max.x, min.y, max.z),	//- RB
		Vec3f(min.x, min.y, max.z),	//- LB
		/// 4 ~ 7 -> 手前
		Vec3f(min.x, max.y, min.z),	//- LT
		Vec3f(max.x, max.y, min.z),	//- RT
		Vec3f(max.x, min.y, min.z),	//- RB
		Vec3f(min.x, min.y, min.z)	//- LB
	};


	Matrix4x4 worldMatrix = Mat4::MakeIdentity();
	Matrix4x4 wvpMatrix = Mat4::MakeIdentity();
	for(uint32_t i = 0; i < 8; i++) {
		worldMatrix = Mat4::MakeTranslate(points[i]);
		wvpMatrix = worldMatrix * camera->GetMatVp();
		Vec3f ndc = Mat4::Transform({ 0.0f,0.0f,0.0f }, wvpMatrix);
		points[i] = Mat4::Transform(ndc, camera->GetMatViewport());
	}


	for(uint32_t i = 0; i < 4; ++i) {
		DrawLine(points[i], points[(i + 1) % 4], color);
		uint32_t j = i + 4;
		DrawLine(points[j], points[(j + 1) % 4 + 4], color);
		DrawLine(points[i], points[j], color);
	}


}

void AABB::DebugDraw(const std::string& windowName) {
#ifdef _DEBUG
	ImGui::Begin(windowName.c_str());

	ImGui::DragFloat3("min", &min.x, 0.025f);
	ImGui::DragFloat3("max", &max.x, 0.025f);

	ImGui::End();
#endif // _DEBUG
}
