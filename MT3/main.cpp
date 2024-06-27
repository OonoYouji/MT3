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

	OBB obb[2] = {
		{
			.center = {0.0f, 0.0f, 0.0f},
			.orientatinos = {},
			.size = {0.83f, 0.26f, 0.24f},
			.rotation = {0.0f, 0.0f, 0.0f}
		},
		{
			.center = {0.9f, 0.66f, 0.78f},
			.orientatinos = {},
			.size = {0.5f, 0.37f, 0.5f},
			.rotation = {-0.05f, -2.49f, 0.15f}
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


		///- カメラの更新
		camera->Update();

		obb[0].DebugDraw("OBB1");
		obb[1].DebugDraw("OBB2");
		for(uint32_t index = 0; index < 2; ++index) {
			obb[index].CulcOrientations();
		}

		color = WHITE;
		if(IsCollided(obb[0], obb[1])) {
			color = RED;
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Grid::GetInstance()->Draw(*camera.get());

		for(uint32_t index = 0; index < 2; ++index) {
			obb[index].Draw(camera.get(), color);
			obb[index].DrawAxis(camera.get());
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
