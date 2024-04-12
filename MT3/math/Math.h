#pragma once

#include "Vector3.h"

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

static const int kColumnWidth = 60;
void VectorScreenPrintf(const Vec3f& pos, const Vec3f& vector, const char* label);
