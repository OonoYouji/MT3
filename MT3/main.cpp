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
	segment.origin = { -2.0f,-1.0f,0.0f };
	segment.diff = { 3.0f,2.0f,2.0f };
	Vec3f point = { -1.5f,0.6f, 0.6f };

	Vec3f project = Project(point - segment.origin, segment.diff);
	Vec3f closestPoint = ClosestPoint(point, segment);

	std::unique_ptr<Sphere> sphere[2];
	for(uint8_t i = 0; i < 2; i++) {
		sphere[i] = std::make_unique<Sphere>();
	}

	sphere[0]->Init(point, 0.01f);
	sphere[0]->SetColor(RED);
	sphere[1]->Init(closestPoint, 0.01f);
	sphere[1]->SetColor(BLACK);

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

		sphere[0]->DebugDraw("Piont");
		sphere[1]->DebugDraw("ClosestPoint");

		segment.DebugDraw("Segment");




		project = Project(point - segment.origin, segment.diff);
		closestPoint = ClosestPoint(point, segment);

		sphere[0]->Init(point, 0.01f);
		sphere[0]->SetColor(RED);
		sphere[1]->Init(closestPoint, 0.01f);
		sphere[1]->SetColor(BLACK);



		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Grid::GetInstance()->Draw(*camera.get());


		for(uint8_t i = 0; i < 2; i++) {
			sphere[i]->Draw(*camera.get());
		}

		segment.Draw(camera.get());

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
