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

	Segment segment;
	segment.origin = Vec3f(0.0f, 0.0f, 0.0f);
	segment.diff = Vec3f(1.0f, 1.0f, 1.0f);
	uint32_t color = 0xffffffff;

	Plane plane;
	plane.normal = Vec3f(0.0f, 1.0f, 0.0f);
	plane.distance = 0.0f;


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

		plane.DebugDraw("Plane");

		segment.DebugDraw("Segment");

		if(IsCollision(segment, plane)) {
			color = RED;
		} else {
			color = WHITE;
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Grid::GetInstance()->Draw(*camera.get());

		plane.Draw(camera.get());
		segment.Draw(camera.get(), color);

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
