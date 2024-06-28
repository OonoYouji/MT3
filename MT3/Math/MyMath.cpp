#include "MyMath.h"

#include <cmath>
#include <Novice.h>

#include <Camera.h>


#pragma region Vector3用関数
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

Vec3f Cross(const Vec3f& v1, const Vec3f& v2) {
	return Vec3f{
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x
	};
}

void VectorScreenPrintf(const Vec2f& pos, const Vec3f& vector, const char* label) {
	static const int kColumnWidth = 60;
	Novice::ScreenPrintf(static_cast<int>(pos.x), static_cast<int>(pos.y), "%0.2f", vector.x);
	Novice::ScreenPrintf(static_cast<int>(pos.x) + kColumnWidth * 1, static_cast<int>(pos.y), "%0.2f", vector.y);
	Novice::ScreenPrintf(static_cast<int>(pos.x) + kColumnWidth * 2, static_cast<int>(pos.y), "%0.2f", vector.z);
	Novice::ScreenPrintf(static_cast<int>(pos.x) + kColumnWidth * 3, static_cast<int>(pos.y), "%s", label);
}

Vec3f Support(const std::vector<Vec3f>& vertices, const Vec3f& direction) {
	float maxDot = 0.0f;
	Vec3f result = vertices[0];
	for(const auto& vertex : vertices) {
		float d = Dot(vertex, direction);
		if(d > maxDot) {
			maxDot = d;
			result = vertex;
		}
	}
	return result;
}

float MaxDot(const std::vector<Vec3f>& vertices, const Vec3f& direction) {
	float maxDot = 0.0f;
	for(const auto& vertex : vertices) {
		float d = Dot(vertex, direction);
		if(d > maxDot) {
			maxDot = d;
		}
	}
	return maxDot;
}

float MinDot(const std::vector<Vec3f>& vertices, const Vec3f& direction) {
	float minDot = 100.0f;
	for(const auto& vertex : vertices) {
		float d = Dot(vertex, direction);
		if(d < minDot) {
			minDot = d;
		}
	}
	return minDot;
}

Vec3f Project(const Vec3f& v1, const Vec3f& v2) {
	Vec3f normalizeV2 = Normalize(v2);
	float dot = Dot(v1, normalizeV2);
	return normalizeV2 * dot;
}

Vec3f ClosestPoint(const Vec3f& point, const Segment& segment) {
	return segment.origin + Project(point - segment.origin, segment.diff);
}

Vec3f Perpendiculer(const Vec3f& vector) {
	if(vector.x != 0.0f || vector.y != 0.0f) {
		return Vec3f(-vector.y, vector.x, 0.0f);
	}
	return Vec3f(0.0f, -vector.z, vector.y);
}

Vec3f Lerp(const Vec3f& v1, const Vec3f& v2, float t) {
	return Vec3f(
		std::lerp(v1.x, v2.x, t),
		std::lerp(v1.y, v2.y, t),
		std::lerp(v1.z, v2.z, t)
	);
}

Vec3f Bezier(const Vec3f& c1, const Vec3f& c2, const Vec3f& c3, float t) {
	Vec3f c1c2 = Lerp(c1, c2, t);
	Vec3f c2c3 = Lerp(c2, c3, t);
	return Lerp(c1c2, c2c3, t);
}

#pragma endregion

#pragma region Matrix4x4用関数

Mat4 Add(const Mat4& m1, const Mat4& m2) {
	return m1 + m2;
}

Mat4 Subtract(const Mat4& m1, const Mat4& m2) {
	return m1 - m2;
}

Mat4 Multiply(const Mat4& m1, const Mat4& m2) {
	return m1 * m2;
}

Mat4 Inverse(const Mat4& m) {
	Matrix4x4 matrix = m;
	Matrix4x4 result = MakeIdentity4x4();

	for(int i = 0; i < 4; ++i) {
		// ピボットが0の場合、行の入れ替えを行う
		if(matrix.m[i][i] == 0.0f) {
			return MakeIdentity4x4(); // 単位行列を返す (逆行列が存在しない)
		}

		// ピボットの値を1にする
		float pivot_inverse = 1.0f / matrix.m[i][i];
		for(int j = 0; j < 4; ++j) {
			matrix.m[i][j] *= pivot_inverse;
			result.m[i][j] *= pivot_inverse;
		}

		// 掃き出し法を用いて、他の行を変換
		for(int k = 0; k < 4; ++k) {
			if(k != i) {
				float factor = -matrix.m[k][i];
				for(int j = 0; j < 4; ++j) {
					matrix.m[k][j] += factor * matrix.m[i][j];
					result.m[k][j] += factor * result.m[i][j];
				}
			}
		}
	}

	return result;
}

Mat4 Transpose(const Mat4& m) {
	Matrix4x4 result;
	for(int r = 0; r < 4; r++) {
		for(int c = 0; c < 4; c++) {
			result.m[r][c] = m.m[c][r];
		}
	}
	return result;
}

Mat4 MakeIdentity4x4() {
	return Mat4{
		1.0f,0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f
	};
}

void MatrixScreenPrintf(const Vec2f& pos, const Mat4& matrix, const std::string& label) {
	static const int kRowHeigth = 20;
	static const int kColumnWidth = 60;
	Novice::ScreenPrintf(static_cast<int>(pos.x), static_cast<int>(pos.y), "%s", label.c_str());
	for(int row = 0; row < 4; ++row) {
		for(int col = 0; col < 4; ++col) {
			Novice::ScreenPrintf(
				static_cast<int>(pos.x) + col * kColumnWidth,
				static_cast<int>(pos.y + 20.0f) + row * kRowHeigth,
				"%6.02f", matrix.m[row][col]
			);
		}
	}
}
#pragma endregion


void DrawLine(const Vec3f& v1, const Vec3f& v2, uint32_t color) {
	Novice::DrawLine(
		static_cast<int>(v1.x),
		static_cast<int>(v1.y),
		static_cast<int>(v2.x),
		static_cast<int>(v2.y),
		color
	);
}


void DrawBezier(const Vec3f& c1, const Vec3f& c2, const Vec3f& c3, const Camera* camera, uint32_t color) {

	Vec3f v[2];
	Matrix4x4 matWorld[2];

	for(uint32_t index = 0; index < 30; ++index) {
		float t[2] = {
			static_cast<float>(index + 0) / 30.0f,
			static_cast<float>(index + 1) / 30.0f
		};

		for(uint8_t i = 0; i < 2; ++i) {
			///- 頂点の計算
			v[i] = Bezier(c1, c2, c3, t[i]);
			///- 行列の計算
			matWorld[i] = Mat4::MakeTranslate(v[i]);
		}

		///- wvpを計算してscreen座標系にする
		for(uint8_t i = 0; i < 2; ++i) {
			Matrix4x4 wvpMatrix = matWorld[i] * camera->GetMatVp();
			Vec3f ndc = Mat4::Transform({ 0.0f,0.0f,0.0f }, wvpMatrix);
			v[i] = Mat4::Transform(ndc, camera->GetMatViewport());
		}

		///- 線の描画
		DrawLine(v[0], v[1], color);

	}
}
