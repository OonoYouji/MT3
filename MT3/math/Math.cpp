#include "Math.h"

#include <cmath>
#include <Novice.h>

Vec3f Add(const Vec3f& v1, const Vec3f& v2) {
	return v1 + v2;
}

Vec3f Subtract(const Vec3f& v1, const Vec3f& v2) {
	return v1 - v2;
}

Vec3f Multiply(float scaler, const Vec3f& v) {
	return v * scaler;
}

float Dot(const Vec3f& v1, const Vec3f& v2) {
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

float Length(const Vec3f& v) {
	return sqrtf(powf(v.x, 2.0f) + powf(v.y, 2.0f) + powf(v.z, 2.0f));
}

Vec3f Normalize(const Vec3f& v) {
	float length = Length(v);
	if(length != 0.0f) {
		return v / length;
	}
	return v;
}

void VectorScreenPrintf(const Vec3f& pos, const Vec3f& vector, const char* label) {
	Novice::ScreenPrintf(static_cast<int>(pos.x), static_cast<int>(pos.y), "%0.2f", vector.x);
	Novice::ScreenPrintf(static_cast<int>(pos.x) + kColumnWidth * 1, static_cast<int>(pos.y), "%0.2f", vector.y);
	Novice::ScreenPrintf(static_cast<int>(pos.x) + kColumnWidth * 2, static_cast<int>(pos.y), "%0.2f", vector.z);
	Novice::ScreenPrintf(static_cast<int>(pos.x) + kColumnWidth * 3, static_cast<int>(pos.y), "%s", label);
}
