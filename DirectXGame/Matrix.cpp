#include "Matrix.h"
#include <math.h>

using namespace KamataEngine;

Matrix4x4 ScaleMatrix(Vector3 scale) {
	return {
	    {{scale.x, 0.0f, 0.0f, 0.0f}, {0.0f, scale.y, 0.0f, 0.0f}, {0.0f, 0.0f, scale.z, 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f}}
    };
}

Matrix4x4 RotatedMatrix(Vector3 theta) {
	Matrix4x4 matrixRotatedX{
	    {{1.0f, 0.0f, 0.0f, 0.0f}, {0.0f, cosf(theta.x), sinf(theta.x), 0.0f}, {0.0f, -sinf(theta.x), cosf(theta.x), 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f}}
    };

	Matrix4x4 matrixRotatedY{
	    {{cosf(theta.y), 0.0f, -sinf(theta.y), 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, {sinf(theta.y), 0.0f, cosf(theta.y), 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f}}
    };

	Matrix4x4 matrixRotatedZ{
	    {{cosf(theta.z), sinf(theta.z), 0.0f, 0.0f}, {-sinf(theta.z), cosf(theta.z), 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f}}
    };

	Matrix4x4 result = Multiply(matrixRotatedX, matrixRotatedY);
	return Multiply(result, matrixRotatedZ);
}

Matrix4x4 TranslateMatrix(Vector3 translate) {
	return {
	    {{1.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}, {translate.x, translate.y, translate.z, 1.0f}}
    };
}

Matrix4x4 Multiply(const Matrix4x4& matrixA, const Matrix4x4& matrixB) {
	Matrix4x4 result{};

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = matrixA.m[i][0] * matrixB.m[0][j] + matrixA.m[i][1] * matrixB.m[1][j] + matrixA.m[i][2] * matrixB.m[2][j] + matrixA.m[i][3] * matrixB.m[3][j];
		}
	}

	return result;
}

Matrix4x4 MakeAffineMatrix(Vector3 scale, Vector3 theta, Vector3 translate) { 
	Matrix4x4 scaleMatrix = ScaleMatrix(scale);
	Matrix4x4 rotatedMatrix = RotatedMatrix(theta);
	Matrix4x4 translateMatrix = TranslateMatrix(translate);
	Matrix4x4 result = Multiply(scaleMatrix, rotatedMatrix);
	return Multiply(result, translateMatrix);
}