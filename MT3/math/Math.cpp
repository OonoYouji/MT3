#include "Math.h"

#include <cmath>
#include <Novice.h>

Vector3 Add(const Vector3& v1, const Vector3& v2) {
	return v1 + v2;
}

Vector3 Subtract(const Vector3& v1, const Vector3& v2) {
	return v1 - v2;
}

Vector3 Multiply(float scaler, const Vector3& v) {
	return v * scaler;
}

float Dot(const Vector3& v1, const Vector3& v2) {
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

float Length(const Vector3& v) {
	return sqrtf(powf(v.x, 2.0f) + powf(v.y, 2.0f) + powf(v.z, 2.0f));
}

Vector3 Normalize(const Vector3& v) {
	return v / Vec3f{ Length(v), Length(v), Length(v), };
}

void VectorScreenPrintf(const Vector3& pos, const Vector3& vector, const char* label) {
	static const int kColumnWidth = 60;
	Novice::ScreenPrintf(static_cast<int>(pos.x), static_cast<int>(pos.y), "%0.2f", vector.x);
	Novice::ScreenPrintf(static_cast<int>(pos.x), static_cast<int>(pos.y) + kColumnWidth * 1, "%0.2f", vector.y);
	Novice::ScreenPrintf(static_cast<int>(pos.x), static_cast<int>(pos.y) + kColumnWidth * 2, "%0.2f", vector.z);
	Novice::ScreenPrintf(static_cast<int>(pos.x), static_cast<int>(pos.y) + kColumnWidth * 3, "%s", label);
}
