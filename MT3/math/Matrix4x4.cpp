#include "Matrix4x4.h"

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
