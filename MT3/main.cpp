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

	Vec3f a{ 0.2f, 1.0f, 0.0f };
	Vec3f b{ 2.4f, 3.1f, 1.2f };
	Vec3f c = a + b;
	Vec3f d = a - b;
	Vec3f e = a * 2.4f;
	Vec3f rotate{0.4f, 1.43f, -0.8f};
	Matrix4x4 rotateXMatrix = Mat4::MakeRotateX(rotate.x);
	Matrix4x4 rotateYMatrix = Mat4::MakeRotateY(rotate.y);
	Matrix4x4 rotateZMatrix = Mat4::MakeRotateZ(rotate.z);
	Matrix4x4 rotateMatrix = rotateXMatrix * rotateYMatrix * rotateZMatrix;

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
		ImGui::Begin("window");

		VectorImGuiText("c", c);
		VectorImGuiText("d", d);
		VectorImGuiText("e", e);

		ImGui::Separator();

		MatrixImGuiText("matrix", rotateMatrix);

		ImGui::End();
#endif // _DEBUG



		///- カメラの更新
		camera->Update();




		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Grid::GetInstance()->Draw(*camera.get());


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
