#pragma once

#include <string>
#include <vector>

#include <Vector3.h>
#include <Matrix4x4.h>

class Camera;

/// <summary>
/// 回転込みのAABB
/// </summary>
struct OBB {

	Vec3f center;			//- 中心
	Vec3f orientatinos[3];	//- 座標軸
	Vec3f size;				//- 座標軸方向への長さの半分

	Vec3f rotation; //- 回転

	Matrix4x4 MakeWorldMatrix() const;

	/// <summary>
	/// 座標軸の計算
	/// </summary>
	void CulcOrientations();

	/// <summary>
	/// OBBの描画
	/// </summary>
	void Draw(const Camera* camera, uint32_t color);

	/// <summary>
	/// 座標軸の描画
	/// </summary>
	void DrawAxis(const Camera* camera);

	/// <summary>
	/// ImGuiでデバッグ表示
	/// </summary>
	void DebugDraw(const std::string& windowName);

	std::vector<Vec3f> GetVertices() const;

};