#include <Novice.h>

#include "Vector3.h"
#include "Matrix4x4.h"
#include "MyMath.h"
#include <ImGuiManager.h>

#include <cmath>
#include <memory>

#include "Camera.h"
#include "Grid.h"
#include "Sphere.h"
#include "Line.h"
#include "Plane.h"
#include "Triangle.h"
#include "AABB.h"
#include "OBB.h"
#include "Collision.h"

const char kWindowTitle[] = "LE2A_05_オオノ_ヨウジ_MT3";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	std::unique_ptr<Camera> camera = std::make_unique<Camera>();
	camera->Init();

	Vec3f translates[3] = {
		{0.2f, 1.0f, 0.0f},
		{0.4f, 0.0f, 0.0f},
		{0.3f, 0.0f, 0.0f}
	};

	Vec3f rotates[3] = {
		{0.0f, 0.0f, -6.8f},
		{0.0f, 0.0f, -1.4f},
		{0.0f, 0.0f, 0.0f}
	};

	Vec3f scales[3] = {
		{1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f}
	};

	Matrix4x4 worldMatrices[3]{};

	Sphere spheres[3]{
		{.radius = 0.05f, .subdivision = 16 },
		{.radius = 0.05f, .subdivision = 16 },
		{.radius = 0.05f, .subdivision = 16 }
	};

	uint32_t colors[3]{
		RED, GREEN, BLUE
	};

	Vec3f screenPositions[3]{};

	// ウィンドウの×ボタンが押されるまでループ
	while(Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);



		///
		/// ↓更新処理ここから
		///

		///- カメラの更新
		camera->Update();

		ImGui::Begin("setting");
		for(uint32_t index = 0; index < 3; ++index) {
			if(!ImGui::TreeNodeEx(("Parts" + std::to_string(index)).c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
				continue;
			}

			ImGui::DragFloat3("scale", &scales[index].x, 0.01f);
			ImGui::DragFloat3("rotate", &rotates[index].x, 0.01f);
			ImGui::DragFloat3("translate", &translates[index].x, 0.01f);

			ImGui::TreePop();
		}
		ImGui::End();

		for(uint32_t index = 0; index < 3; ++index) {
			worldMatrices[index] = Mat4::MakeAffine(scales[index], rotates[index], translates[index]);
			if(index != 0) {

				worldMatrices[index] *= worldMatrices[index - 1];
			}
			spheres[index].center = Mat4::Transform({ 0.0f,0.0f,0.0f }, worldMatrices[index]);
			screenPositions[index] = CalcScreenPosition(worldMatrices[index], camera.get());
		}



		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Grid::GetInstance()->Draw(*camera.get());

		for(uint32_t index = 0; index < 3; ++index) {
			spheres[index].Draw(camera.get(), colors[index]);
		}

		DrawLine(screenPositions[0], screenPositions[1], WHITE);
		DrawLine(screenPositions[1], screenPositions[2], WHITE);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if(preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
