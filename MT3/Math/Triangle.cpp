#include "Triangle.h"

#include <ImGuiManager.h>

#include "Camera.h"
#include "MyMath.h"


void Triangle::DebugDraw(const std::string& windowName) {
#ifdef _DEBUG
	ImGui::Begin(windowName.c_str());

	ImGui::DragFloat3("Origin", &origin.x, 0.025f);

	ImGui::End();
#endif // _DEBUG
}

void Triangle::Draw(const Camera* camera, uint32_t color) {
	Vec3f points[3]{};

	// screen座標系まで変換
	Matrix4x4 worldMatrix = Mat4::MakeAffine({ 1.0f,1.0f,1.0f }, { 0.0f, 0.0f,0.0f }, origin);
	Matrix4x4 wvpMatrix = worldMatrix * camera->GetMatVp();
	for(uint32_t i = 0; i < 3; i++) {
		Vec3f ndc = Mat4::Transform(vertices[i], wvpMatrix);
		points[i] = Mat4::Transform(ndc, camera->GetMatViewport());
	}

	DrawLine(points[0], points[1], color);
	DrawLine(points[1], points[2], color);
	DrawLine(points[2], points[0], color);

}
