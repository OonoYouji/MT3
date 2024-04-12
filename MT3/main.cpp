#include <Novice.h>

#include "Vector3.h"
#include "math/Math.h"

const char kWindowTitle[] = "LE2A_05_オオノ_ヨウジ_MT3";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Vec3f v1{ 1.0f,3.0f,-5.0f };
	Vec3f v2{ 4.0f,-1.0f,2.0f };
	float k = 4.0f;

	///- 計算結果
	Vec3f resultAdd = Add(v1, v2);
	Vec3f resultSubtract = Subtract(v1, v2);
	Vec3f resultMultiply = Multiply(k, v1);
	float resultDot = Dot(v1, v2);
	float resultLength = Length(v1);
	Vec3f resultNormalize = Normalize(v2);

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
		VectorScreenPrintf({ 0.0f,0.0f }, resultAdd, " : Add");
		VectorScreenPrintf({ 0.0f,20.0f * 1 }, resultSubtract, " : Subtract");
		VectorScreenPrintf({ 0.0f,20.0f * 2 }, resultMultiply, " : Multiply");
		Novice::ScreenPrintf(0, 20 * 3, "%0.2f : Dot", resultDot);
		Novice::ScreenPrintf(0, 20 * 4, "%0.2f : Length", resultLength);
		VectorScreenPrintf({ 0.0f,20.0f * 5 }, resultNormalize, " : Normalize");


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
