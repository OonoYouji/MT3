#include <OBB.h>

#include <array>

#include <ImGuiManager.h>
#include <Novice.h>

#include <Camera.h>
#include <MyMath.h>

Matrix4x4 OBB::MakeWorldMatrix() const {
	///- scaleMatrixはなし
	return Mat4::MakeRotate(rotation) * Mat4::MakeTranslate(center);
}

void OBB::CulcOrientations() {
	Matrix4x4 rotateMatrix = Mat4::MakeRotate(rotation);
	orientatinos[0] = Mat4::Transform({ 1.0f, 0.0f, 0.0f }, rotateMatrix);
	orientatinos[1] = Mat4::Transform({ 0.0f, 1.0f, 0.0f }, rotateMatrix);
	orientatinos[2] = Mat4::Transform({ 0.0f, 0.0f, 1.0f }, rotateMatrix);
}


void OBB::Draw(const Camera* camera, uint32_t color) {

	///- 頂点の配列
	std::array<Vec3f, 8> points{
		/// 0 ~ 3 -> 奥
		Vec3f(-size.x, size.y, size.z),		//- LT
		Vec3f(size.x, size.y, size.z),		//- RT
		Vec3f(size.x, -size.y, size.z),		//- RB
		Vec3f(-size.x, -size.y, size.z),	//- LB
		/// 4 ~ 7 -> 手前
		Vec3f(-size.x, size.y, -size.z),	//- LT
		Vec3f(size.x, size.y, -size.z),		//- RT
		Vec3f(size.x, -size.y, -size.z),	//- RB
		Vec3f(-size.x, -size.y, -size.z)	//- LB
	};


	Matrix4x4 worldMatrix = Mat4::MakeIdentity();
	Matrix4x4 wvpMatrix = Mat4::MakeIdentity();
	Matrix4x4 obbWorldMatrix = MakeWorldMatrix();
	for(uint32_t i = 0; i < 8; i++) {
		worldMatrix = Mat4::MakeTranslate(points[i]) * obbWorldMatrix;
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


void OBB::DrawAxis(const Camera* camera) {

	///- 頂点の配列
	std::array<Vec3f, 4> points{
		/// 0 -> 中心
		Vec3f(0.0f, 0.0f, 0.0f),	//- center
		/// 1 ~ 3 -> 各軸方向
		orientatinos[0],	//- XAxis
		orientatinos[1],	//- YAxis
		orientatinos[2]		//- ZAxis
	};

	///- 色の配列
	std::array<uint32_t, 3> colors{
		BLUE, RED, GREEN
	};


	Matrix4x4 worldMatrix = Mat4::MakeIdentity();
	Matrix4x4 wvpMatrix = Mat4::MakeIdentity();
	for(uint32_t i = 0; i < 4; i++) {
		worldMatrix = Mat4::MakeTranslate(points[i]);
		wvpMatrix = worldMatrix * camera->GetMatVp();
		Vec3f ndc = Mat4::Transform({ 0.0f,0.0f,0.0f }, wvpMatrix);
		points[i] = Mat4::Transform(ndc, camera->GetMatViewport());
	}


	for(uint32_t i = 0; i < 3; ++i) {
		DrawLine(points[0], points[i + 1], colors[i]);
	}
}


void OBB::DebugDraw(const std::string& windowName) {
#ifdef _DEBUG
	ImGui::Begin(windowName.c_str());

	ImGui::DragFloat3("Center", &center.x, 0.025f);
	ImGui::DragFloat3("Size", &size.x, 0.025f);
	ImGui::DragFloat3("Rotation", &rotation.x, 0.025f);

	ImGui::Separator();

	ImGui::DragFloat3("XAxis", &orientatinos[0].x, 0.0f);
	ImGui::DragFloat3("YAxis", &orientatinos[1].x, 0.0f);
	ImGui::DragFloat3("ZAxis", &orientatinos[2].x, 0.0f);

	ImGui::End();
#endif // _DEBUG
}
