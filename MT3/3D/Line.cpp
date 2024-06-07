#include "Line.h"

#include <Novice.h>
#include <ImGuiManager.h>

#include "MyMath.h"
#include "Matrix4x4.h"


template struct LineBase<LineTag::Line>;
template struct LineBase<LineTag::Segment>;
template struct LineBase<LineTag::Ray>;


template<LineTag tag>
void LineBase<tag>::DebugDraw(const std::string& windowName) {
#ifdef _DEBUG
	ImGui::Begin(windowName.c_str());

	ImGui::DragFloat3("Origin", &origin.x, 0.05f);
	ImGui::DragFloat3("Diff", &diff.x, 0.05f);

	ImGui::End();
#endif // _DEBUG
}


template<LineTag tag>
void LineBase<tag>::Draw(const Camera* camera, uint32_t color) {
	Vec3f start = Mat4::Transform(Mat4::Transform(origin, camera->GetMatVp()), camera->GetMatViewport());
	Vec3f end = Mat4::Transform(Mat4::Transform(origin + diff, camera->GetMatVp()), camera->GetMatViewport());

	Novice::DrawLine(
		static_cast<int>(start.x),
		static_cast<int>(start.y),
		static_cast<int>(end.x),
		static_cast<int>(end.y),
		color
	);
}
