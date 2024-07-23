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


struct Ball {
	Vec3f position;
	float mass;
	float radius;
	uint32_t color;
	Vec3f velocity;
	Vec3f acceleraion;
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


	Plane plane{
		.normal = Normalize(Vec3f(-0.2f, 0.9f, -0.3f)),
		.distance = 0.0f
	};

	Ball ball{
		.position = Vec3f(0.8f, 1.2f, 0.3f),
		.mass = 2.0f,
		.radius = 0.05f,
		.color = WHITE,
		.velocity = {},
		.acceleraion = Vec3f(0.0f, -9.8f, 0.0f)
	};

	Sphere sphere{
		.center = ball.position,
		.radius = ball.radius,
		.subdivision = 16
	};


	bool isStart = false;
	float deltaTime = 1.0f / 60.0f;

	float e = 1.0f;

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
		if(ImGui::Button("Start Button")) {
			isStart = true;
		}

		if(ImGui::Button("Reset Button")) {
			isStart = false;

			ball.position = Vec3f(0.8f, 1.2f, 0.3f);
			ball.mass = 2.0f;
			ball.radius = 0.05f;
			ball.color = WHITE;
			ball.velocity = {};
			ball.acceleraion = Vec3f(0.0f, -9.8f, 0.0f);
		}

		ImGui::Separator();

		ImGui::DragFloat("e", &e, 0.01f);

		ImGui::End();



		///- カメラの更新
		camera->Update();



		if(isStart) {

			ball.velocity += ball.acceleraion * deltaTime;
			ball.position += ball.velocity * deltaTime;


			if(IsCollided(Sphere{ .center = ball.position, .radius = ball.radius }, plane)) {
				Vec3f reflected = Reflect(ball.velocity, plane.normal);
				Vec3f projectToNormal= Project(reflected, plane.normal);
				Vec3f movingDirection = reflected = projectToNormal;
				ball.velocity = projectToNormal * e + movingDirection;
			}

		}

		sphere.center = ball.position;

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Grid::GetInstance()->Draw(*camera.get());

		plane.Draw(camera.get());

		sphere.Draw(camera.get(), ball.color);


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
