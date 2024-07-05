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



struct Spring {
	Vec3f anchor;				///- アンカー、固定された端の位置
	float naturalLength;		///- 自然潮
	float stiffness;			///- 剛性、バネ定数k
	float dampingCoefficient;	///- 減衰係数
};

struct Ball {
	Vec3f position;		///- 位置
	Vec3f velocity;		///- 速度
	Vec3f acceleration;	///- 加速度
	float mass;			///- 質量
	float radius;		///- 半径
	uint32_t color;		///- 色
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

	Spring spring{
		.anchor = {0.0f,1.0f,0.0f},
		.naturalLength = 1.0f,
		.stiffness = 100.0f,
		.dampingCoefficient = 2.0f
	};

	Ball ball{
		.position = {1.2f, 0.0f, 0.0f},
		.mass = 2.0f,
		.radius = 0.05f,
		.color = BLUE
	};

	///- 1frame当たりの時間
	float deltaTime = 1.0f / 60.0f;
	const Vec3f kGravity = { 0.0f, -9.8f, 0.0f };

	Sphere sphere{
		.radius = 0.05f,
		.subdivision = 16
	};

	Vec3f startPos = {};

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
		ImGui::DragFloat3("startPos", &startPos.x, 0.01f);
		if(ImGui::Button("start")) {
			ball.position = startPos;
		}
		ImGui::End();

		///- カメラの更新
		camera->Update();

		/// =========================================
		/// バネの更新
		/// =========================================

		///- 差分
		Vec3f diff = ball.position - spring.anchor;
		float length = Length(diff);
		if(length != 0.0f) {
			///- 向き
			Vec3f direction = Normalize(diff);

			///- 伸びきったときの座標
			Vec3f restPosition = spring.anchor + (direction * spring.naturalLength);

			///- 変位ベクトル
			Vec3f displacement = (ball.position - restPosition) * length;

			///- 復元力
			Vec3f restoringForce = displacement * -spring.stiffness;
			///- 減衰力
			Vec3f dampingForce = ball.velocity * -spring.dampingCoefficient;
			///- 最終的な力
			Vec3f force = restoringForce + dampingForce;

			ball.acceleration = force / ball.mass;

		}

		ball.velocity += ball.acceleration * deltaTime;
		ball.velocity += kGravity * deltaTime;
		ball.position += ball.velocity * deltaTime;

		sphere.center = ball.position;

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Grid::GetInstance()->Draw(*camera.get());

		sphere.Draw(camera.get(), ball.color);
		DrawLine(
			CalcScreenPosition(Mat4::MakeTranslate(sphere.center), camera.get()),
			CalcScreenPosition(Mat4::MakeTranslate(spring.anchor), camera.get()),
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
