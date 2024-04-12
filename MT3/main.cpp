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

	Vec3f translate{ 4.1f, 2.6f, 0.8f };
	Vec3f scale{ 1.5f,5.2f,7.3f };
	Mat4 translateMatrix = Mat4::MakeTranslate(translate);
	Mat4 scaleMatrix = Mat4::MakeScale(scale);
	Vec3f point{ 2.3f,3.8f, 1.4f };
	Mat4 transformMatrix = {
		1.0f, 2.0f, 3.0f, 4.0f,
		3.0f, 1.0f, 1.0f, 2.0f,
		1.0f, 4.0f, 2.0f, 3.0f,
		2.0f, 2.0f, 1.0f, 3.0f
	};
	Vec3f transformed = Mat4::Transform(point, transformMatrix);


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
		VectorScreenPrintf({ 0.0f,0.0f }, transformed, "transformed");
		MatrixScreenPrintf({ 0.0f, 20.0f }, translateMatrix, "translateMatrix");
		MatrixScreenPrintf({ 0.0f, 120.0f }, scaleMatrix, "scaleMatrix");

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
