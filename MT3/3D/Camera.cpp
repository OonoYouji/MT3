#include "Camera.h"

#include "ImGuiManager.h"


Camera::Camera() {}
Camera::~Camera() {}



void Camera::Init() {

	scale_ = { 1.0f,1.0f,1.0f };
	rotate_ = { 0.26f, 0.0f,0.0f };
	translate_ = { 0.0f,1.9f, -6.49f };

	
	UpdateMatrix();
}



void Camera::Update() {
#ifdef _DEBUG
	ImGui::Begin("Camera");

	ImGui::DragFloat3("rotate", &rotate_.x, 0.01f);
	ImGui::DragFloat3("translate", &translate_.x, 0.1f);

	ImGui::End();
#endif // _DEBUG


	UpdateMatrix();

}


void Camera::UpdateMatrix() {

	matWorld_ = Mat4::MakeAffine(scale_, rotate_, translate_);

	matView_ = Mat4::MakeInverse(matWorld_);

	matProjection_ = Mat4::MakePerspectiveFov(0.45f, 1280.0f / 720.0f, 0.1f, 100.0f);
	matViewport_ = Mat4::MakeViewport(0.0f, 0.0f, 1280.0f, 720.0f, 0.0f, 1.0f);
	matVp_ = matView_ * matProjection_;

}

