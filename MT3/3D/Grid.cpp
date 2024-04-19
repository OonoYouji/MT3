#include "Grid.h"

#include <Novice.h>
#include "Vector3.h"
#include "Matrix4x4.h"

#include "Camera.h"

Grid* Grid::GetInstance() {
	static Grid instance;
	return &instance;
}

void Grid::Init() {



}



void Grid::Draw(const Camera& camera) {

	const float kGridEvery = (gridHalfWidth_ * 2.0f) / float(subdivision_);
	
	///- 奥から手前
	// 始点と終点の計算に用いる変数
	Vec3f pos[2];
	Matrix4x4 worldMatrix[2];
	Matrix4x4 wvpMatrix[2];
	Vec3f ndc[2];
	Vec3f screenPos[2];

	// 奥から手前へと順番に描画;
	for(uint32_t xIndex = 0; xIndex <= subdivision_; ++xIndex) {

		pos[0] = { -gridHalfWidth_, 0.0f, (xIndex - subdivision_ / 2.0f) * kGridEvery };
		pos[1] = { gridHalfWidth_, 0.0f, (xIndex - subdivision_ / 2.0f) * kGridEvery };

		for(uint32_t i = 0; i < 2; i++) {
			worldMatrix[i] = Mat4::MakeAffine({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, pos[i]);
			wvpMatrix[i] = worldMatrix[i] * camera.GetMatVp();
			ndc[i] = Mat4::Transform({ 0.0f,0.0f,0.0f }, wvpMatrix[i]);
			screenPos[i] = Mat4::Transform(ndc[i], camera.GetMatViewport());
		}

		if(xIndex == subdivision_ / 2) {
			Novice::DrawLine(
				static_cast<int>(screenPos[0].x),
				static_cast<int>(screenPos[0].y),
				static_cast<int>(screenPos[1].x),
				static_cast<int>(screenPos[1].y),
				0x000000ff
			);
		} else {
			Novice::DrawLine(
				static_cast<int>(screenPos[0].x),
				static_cast<int>(screenPos[0].y),
				static_cast<int>(screenPos[1].x),
				static_cast<int>(screenPos[1].y),
				0xaaaaaaff
			);
		}

	}

	// 左から右へと順番に描画;
	for(uint32_t zIndex = 0; zIndex <= subdivision_; ++zIndex) {

		pos[0] = { (zIndex - subdivision_ / 2.0f) * kGridEvery, 0.0f, -gridHalfWidth_ };
		pos[1] = { (zIndex - subdivision_ / 2.0f) * kGridEvery, 0.0f, gridHalfWidth_ };

		for(uint32_t i = 0; i < 2; i++) {
			worldMatrix[i] = Mat4::MakeAffine({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, pos[i]);
			wvpMatrix[i] = worldMatrix[i] * camera.GetMatVp();
			ndc[i] = Mat4::Transform({ 0.0f,0.0f,0.0f }, wvpMatrix[i]);
			screenPos[i] = Mat4::Transform(ndc[i], camera.GetMatViewport());
		}


		if(zIndex == subdivision_ / 2) {
			Novice::DrawLine(
				static_cast<int>(screenPos[0].x),
				static_cast<int>(screenPos[0].y),
				static_cast<int>(screenPos[1].x),
				static_cast<int>(screenPos[1].y),
				0x000000ff
			);
		} else {
			Novice::DrawLine(
				static_cast<int>(screenPos[0].x),
				static_cast<int>(screenPos[0].y),
				static_cast<int>(screenPos[1].x),
				static_cast<int>(screenPos[1].y),
				0xaaaaaaff
			);
		}

	}


}
