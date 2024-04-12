#pragma once

#include "Vector3.h"

///- â¡éZ
Vector3 Add(const Vector3& v1, const Vector3& v2);

///- å∏éZ
Vector3 Subtract(const Vector3& v1, const Vector3& v2);

///- ÉXÉJÉâÅ[î{
Vector3 Multiply(float scaler, const Vector3& v);

///- ì‡êœ
float Dot(const Vector3& v1, const Vector3& v2);

///- í∑Ç≥
float Length(const Vector3& v);

///- ê≥ãKâª
Vector3 Normalize(const Vector3& v);

static const int kColumnWidth = 60;
void VectorScreenPrintf(const Vector3& pos, const Vector3& vector, const char* label);
