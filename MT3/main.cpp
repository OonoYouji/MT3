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

	Vec3f controlPoints[3] = {
		{-0.8f, 0.58f, 1.0f},
		{1.76f, 1.0f, -0.3f},
		{0.94f, -0.7f, 2.3f}
	};

	Sphere spheres[3] = {
		{
			.center = controlPoints[0],
			.radius = 0.01f,
			.subdivision = 16
		},
		{
			.center = controlPoints[1],
			.radius = 0.01f,
			.subdivision = 16
		},
		{
			.center = controlPoints[2],
			.radius = 0.01f,
			.subdivision = 16
		},
	};

	uint32_t color = WHITE;

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

#ifdef _DEBUG
		ImGui::Begin("ControlPoints");
		ImGui::DragFloat3("v1", &controlPoints[0].x, 0.05f);
		ImGui::DragFloat3("v2", &controlPoints[1].x, 0.05f);
		ImGui::DragFloat3("v3", &controlPoints[2].x, 0.05f);
		ImGui::End();
#endif // _DEBUG


		///- カメラの更新
		camera->Update();

		for(uint32_t index = 0; index < 3; ++index) {
			spheres[index].center = controlPoints[index];
		}


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Grid::GetInstance()->Draw(*camera.get());

		DrawBezier(controlPoints[0], controlPoints[1], controlPoints[2], camera.get(), color);

		for(uint32_t index = 0; index < 3; ++index) {
			spheres[index].Draw(camera.get(), BLACK);
		}

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
