﻿#include "Matrix4x4.h"
#include <cassert>
#include <cmath>

Matrix4x4 Matrix4x4::MakeIdentity() {
	return {
		1.0f,0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f
	};
}

Matrix4x4 Matrix4x4::MakeTranslate(const Vec3f& translate) {
	return {
		1.0f,0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		translate.x, translate.y, translate.z, 1.0f
	};
}

Matrix4x4 Matrix4x4::MakeScale(const Vec3f& scale) {
	return {
		scale.x, 0.0f, 0.0f, 0.0f,
		0.0f, scale.y, 0.0f, 0.0f,
		0.0f, 0.0f, scale.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
}

Matrix4x4 Matrix4x4::MakeRotateX(float theta) {
	return {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, std::cosf(theta), std::sinf(theta), 0.0f,
		0.0f, -std::sinf(theta) , std::cosf(theta) , 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
}

Matrix4x4 Matrix4x4::MakeRotateY(float theta) {
	return {
		std::cosf(theta), 0.0f, -std::sinf(theta), 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		std::sinf(theta), 0.0f, std::cosf(theta), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
}

Matrix4x4 Matrix4x4::MakeRotateZ(float theta) {
	return {
		std::cosf(theta), std::sinf(theta), 0.0f, 0.0f,
		-std::sinf(theta), std::cosf(theta), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
}

Matrix4x4 Matrix4x4::MakeRotate(const Vec3f& rotate) {
	Mat4 x = MakeRotateX(rotate.x);
	Mat4 y = MakeRotateY(rotate.y);
	Mat4 z = MakeRotateZ(rotate.z);
	return x * y * z;
}

Matrix4x4 Matrix4x4::MakeAffine(const Vec3f& scale, const Vec3f& rotate, const Vec3f& translate) {
	Mat4 matScale = MakeScale(scale);
	Mat4 matRotate = MakeRotate(rotate);
	Mat4 matTranslate = MakeTranslate(translate);
	return matScale * matRotate * matTranslate;
}

Vec3f Matrix4x4::Transform(const Vec3f& v, const Matrix4x4& m) {
	//w=1がデカルト座標系であるので(x,y,1)のベクトルとしてmatrixとの積をとる
	Vec3f result{ 0.0f,0.0f,0.0f };

	result.x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + 1.0f * m.m[3][0];
	result.y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + 1.0f * m.m[3][1];
	result.z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + 1.0f * m.m[3][2];
	float w = v.x * m.m[0][3] + v.y * m.m[1][3] + v.z * m.m[2][3] + 1.0f * m.m[3][3];

	//ベクトルに対して基本的な操作を行う行列でwが0になることはありえない
	//wが0.0fになった場合プログラムを停止する
	assert(w != 0.0f);

	//w=1がデカルト座標系であるので、w除算することで同次座標をデカルト座標に戻す
	result.x /= w;
	result.y /= w;
	result.z /= w;

	return result;
}

Matrix4x4 Matrix4x4::MakeInverse(const Matrix4x4& m) {
	Matrix4x4 matrix = m;
	Matrix4x4 result = MakeIdentity();

	for(int i = 0; i < 4; ++i) {
		// ピボットが0の場合、行の入れ替えを行う
		if(matrix.m[i][i] == 0.0f) {
			return MakeIdentity(); // 単位行列を返す (逆行列が存在しない)
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

Matrix4x4 Matrix4x4::MakeTranspose(const Matrix4x4& m) {
	Matrix4x4 result;
	for(int r = 0; r < 4; r++) {
		for(int c = 0; c < 4; c++) {
			result.m[r][c] = m.m[c][r];
		}
	}
	return result;
}
