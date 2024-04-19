#include <Novice.h>

#include "Vector3.h"
#include "Matrix4x4.h"
#include "math/Math.h"
#include <cmath>
#include <ImGuiManager.h>

const char kWindowTitle[] = "LE2A_05_オオノ_ヨウジ_MT3";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };


	Vec3f v1 = { 1.2f, -3.9f, 2.5f };
	Vec3f v2 = { 2.8f, 0.4f, -1.3f };
	Vec3f cross = Cross(v1, v2);

	Vec3f rotate = { 0.0f,0.0f,0.0f };
	Vec3f translate = { 0.0f,0.0f,0.0f };
	Mat4 worldMatrix = Mat4::MakeAffine({ 1.0f,1.0f,1.0f }, rotate, translate);

	Vec3f cameraPosition = { 0.0f,0.0f,-5.0f };
	Mat4 cameraMatrix = Mat4::MakeAffine({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, cameraPosition);
	Mat4 viewMatrix = Mat4::MakeInverse(cameraMatrix);
	Mat4 projectionMatrix = Mat4::MakePerspectiveFov(0.45f, 1280.0f / 720.0f, 0.1f, 100.0f);
	Mat4 viewportMatrix = Mat4::MakeViewport(0.0f, 0.0f, 1280.0f, 720.0f, 0.0f, 1.0f);
	Mat4 vpMatrix = viewMatrix * projectionMatrix;

	const Vec3f kLocalVertices[3] = {
		{ 0.0f, 0.5f, 0.0f},
		{ -0.5f, -0.5f, 0.0f},
		{ 0.5f, -0.5f, 0.0f}
	};

	Mat4 wvpMatrix = worldMatrix * vpMatrix;
	Vec3f screenVertices[3];
	for(uint32_t i = 0; i < 3; i++) {
		Vec3f ndcVertex = Mat4::Transform(kLocalVertices[i], wvpMatrix);
		screenVertices[i] = Mat4::Transform(ndcVertex, viewportMatrix);
	}

	Vec3f worldVertices[3];
	for(uint32_t i = 0; i < 3; i++) {
		worldVertices[i] = Mat4::Transform(kLocalVertices[i], worldMatrix);
	}

	float dot = Dot(Normalize(cameraPosition - translate), cross);

	int frameCount = 0;


	// ウィンドウの×ボタンが押されるまでループ
	while(Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

#ifdef _DEBUG

		ImGui::Begin("triangle");

		ImGui::DragFloat3("rotate", &rotate.x, 0.25f);

		ImGui::End();

#endif // _DEBUG



		///
		/// ↓更新処理ここから
		///
		frameCount++;

		rotate.y += 1.0f / 64.0f;

		//translate.z = std::sin(float(frameCount) / 10.0f);
		worldMatrix = Mat4::MakeAffine({ 1.0f,1.0f,1.0f }, rotate, translate);

		///- world座標系
		for(uint32_t i = 0; i < 3; i++) {
			worldVertices[i] = Mat4::Transform(kLocalVertices[i], worldMatrix);
		}

		///- screen座標系
		wvpMatrix = worldMatrix * vpMatrix;
		for(uint32_t i = 0; i < 3; i++) {
			Vec3f ndcVertex = Mat4::Transform(kLocalVertices[i], wvpMatrix);
			screenVertices[i] = Mat4::Transform(ndcVertex, viewportMatrix);
		}

		///- 外積の計算
		cross = Cross(worldVertices[0], worldVertices[1]);
		dot = Dot(Normalize(cameraPosition - translate), cross);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		VectorScreenPrintf({ 0.0f,0.0f }, cross, "cross");

		if(dot < 0) {

			Novice::DrawTriangle(
				static_cast<int>(screenVertices[0].x),
				static_cast<int>(screenVertices[0].y),
				static_cast<int>(screenVertices[1].x),
				static_cast<int>(screenVertices[1].y),
				static_cast<int>(screenVertices[2].x),
				static_cast<int>(screenVertices[2].y),
				RED,
				kFillModeSolid
			);
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
