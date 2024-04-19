#include <Novice.h>

#include "Vector3.h"
#include "Matrix4x4.h"
#include "math/Math.h"

const char kWindowTitle[] = "LE2A_05_オオノ_ヨウジ_MT3";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };


	Vec3f rotate = { 0.4f, 1.43f, -0.8f };
	Mat4 rotateXMatrix = Mat4::MakeRotateX(rotate.x);
	Mat4 rotateYMatrix = Mat4::MakeRotateY(rotate.y);
	Mat4 rotateZMatrix = Mat4::MakeRotateZ(rotate.z);
	Mat4 rotateXYZMatrix = rotateXMatrix * (rotateYMatrix * rotateZMatrix);

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

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		///- 計算結果の表示
		MatrixScreenPrintf({ 0.0f, 0.0f }, rotateXMatrix, "rotateXMatrix");
		MatrixScreenPrintf({ 0.0f, 100.0f }, rotateYMatrix, "rotateYMatrix");
		MatrixScreenPrintf({ 0.0f, 200.0f }, rotateZMatrix, "rotateZMatrix");
		MatrixScreenPrintf({ 0.0f, 300.0f }, rotateXYZMatrix, "rotateXYZMatrix");

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
