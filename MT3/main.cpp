#include <Novice.h>

#include "Vector3.h"
#include "Matrix4x4.h"
#include "MyMath.h"
#include <ImGuiManager.h>

#include <cmath>
#include <memory>
#include <numbers>

#include "Camera.h"
#include "Grid.h"
#include "Sphere.h"
#include "Line.h"
#include "Plane.h"
#include "Triangle.h"
#include "AABB.h"
#include "OBB.h"
#include "Collision.h"

struct ConicalPendulum {
	Vec3f anchor;
	float length;
	float halfApexAngle;
	float angle;
	float angularVelocity;
};


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

	Sphere sphere{
		.center = {},
		.radius = 0.05f,
		.subdivision = 16
	};

	ConicalPendulum conicalPendulum{
		.anchor = {0.0f, 1.0f, 0.0f},
		.length = 0.8f,
		.halfApexAngle = 0.7f,
		.angle = 0.0f,
		.angularVelocity = 0.0f,
	};


	bool isStart = false;
	float deltaTime = 1.0f / 60.0f;

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

		ImGui::Begin("setting");
		//ImGui::DragFloat3("center", &center.x, 0.01f);
		if(ImGui::Button("Start Button")) {
			isStart = true;
		}

		ImGui::End();

		///- カメラの更新
		camera->Update();

		if(isStart) {

			conicalPendulum.angularVelocity = std::sqrt(9.8f / (conicalPendulum.length * std::cos(conicalPendulum.halfApexAngle)));
			conicalPendulum.angle += conicalPendulum.angularVelocity * deltaTime;

			float radius = std::sin(conicalPendulum.halfApexAngle) * conicalPendulum.length;
			float height = std::cos(conicalPendulum.halfApexAngle) * conicalPendulum.length;

			sphere.center = {
				conicalPendulum.anchor.x + std::sin(conicalPendulum.angle) * radius,
				conicalPendulum.anchor.y - height,
				conicalPendulum.anchor.z - std::cos(conicalPendulum.angle) * radius
			};

		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Grid::GetInstance()->Draw(*camera.get());

		sphere.Draw(camera.get(), WHITE);

		DrawLine(
			CalcScreenPosition(Mat4::MakeTranslate(sphere.center), camera.get()),
			CalcScreenPosition(Mat4::MakeTranslate(conicalPendulum.anchor), camera.get()),
			WHITE
		);

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
