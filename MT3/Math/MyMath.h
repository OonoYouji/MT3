#pragma once

#include <string>

#include "Vector3.h"
#include "Vector2.h"
#include "Matrix4x4.h"
#include "Line.h"

///- 加算
Vec3f Add(const Vec3f& v1, const Vec3f& v2);

///- 減算
Vec3f Subtract(const Vec3f& v1, const Vec3f& v2);

///- スカラー倍
Vec3f Multiply(float scaler, const Vec3f& v);

///- 内積
float Dot(const Vec3f& v1, const Vec3f& v2);

///- 長さ
float Length(const Vec3f& v);

///- 正規化
Vec3f Normalize(const Vec3f& v);

///- クロス積
Vec3f Cross(const Vec3f& v1, const Vec3f& v2);

void VectorScreenPrintf(const Vec2f& pos, const Vec3f& vector, const char* label);



///- 加算
Mat4 Add(const Mat4& m1, const Mat4& m2);

///- 減算
Mat4 Subtract(const Mat4& m1, const Mat4& m2);

///- 積
Mat4 Multiply(const Mat4& m1, const Mat4& m2);

///- 逆行列
Mat4 Inverse(const Mat4& m);

///- 転置行列
Mat4 Transpose(const Mat4& m);

///- 単位行列の生成
Mat4 MakeIdentity4x4();

///- 行列のデバッグ表示
void MatrixScreenPrintf(const Vec2f& pos, const Mat4& matrix, const std::string& label);


void DrawLine(const Vec3f& v1, const Vec3f& v2, uint32_t color);


///- 正射影ベクトル
Vec3f Project(const Vec3f& v1, const Vec3f& v2);

///- 最近接点を求める
Vec3f ClosestPoint(const Vec3f& point, const Segment& segment);


Vec3f Perpendiculer(const Vec3f& vector);

