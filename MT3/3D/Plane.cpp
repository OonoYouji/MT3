#include "Plane.h"

#include <Novice.h>
#include <ImGuiManager.h>
#include "Camera.h"
#include "MyMath.h"

void Plane::DebugDraw(const std::string& windowName) {
#ifdef _DEBUG
	ImGui::Begin(windowName.c_str());

	ImGui::DragFloat3("Normal", &normal.x, 0.01f);
	ImGui::DragFloat("Distance", &distance, 0.05f);

	ImGui::End();
#endif // _DEBUG
}

void Plane::Draw(const Camera* camera) {

	Vec3f center = normal * distance;
	Vec3f perpendiculers[4];

	perpendiculers[0] = Normalize(Perpendiculer(normal));
	perpendiculers[1] = -perpendiculers[0];
	perpendiculers[2] = Cross(normal, perpendiculers[1]);
	perpendiculers[3] = -perpendiculers[2];

	Vec3f points[4];
	for(uint32_t index = 0; index < 4; index++) {
		Vec3f extend = perpendiculers[index] * 2.0f;
		Vec3f point = center + extend;
		points[index] = Mat4::Transform(Mat4::Transform(point, camera->GetMatVp()), camera->GetMatViewport());
	}

	DrawLine(points[0], points[2], WHITE);
	DrawLine(points[0], points[3], WHITE);
	DrawLine(points[1], points[2], WHITE);
	DrawLine(points[1], points[3], WHITE);

}
