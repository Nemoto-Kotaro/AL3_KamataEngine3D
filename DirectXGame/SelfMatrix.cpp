#include "SelfMatrix.h"
#include "SelfVector.h"
#include <cmath>

namespace NemotoLibrary {

void SelfMatrix4x4::operator+=(const SelfMatrix4x4& rhs) { *this = MatrixMath::Add(*this, rhs); }

SelfMatrix4x4 SelfMatrix4x4::operator+(const SelfMatrix4x4& rhs) const { return MatrixMath::Add(*this, rhs); }

void SelfMatrix4x4::operator-=(const SelfMatrix4x4& rhs) { *this = MatrixMath::Subtract(*this, rhs); }

SelfMatrix4x4 SelfMatrix4x4::operator-(const SelfMatrix4x4& rhs) const { return MatrixMath::Subtract(*this, rhs); }

SelfMatrix4x4 MatrixMath::Add(const SelfMatrix4x4& m1, const SelfMatrix4x4& m2) {
	SelfMatrix4x4 result;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = m1.m[i][j] + m2.m[i][j];
		}
	}

	return result;
}

SelfMatrix4x4 MatrixMath::Subtract(const SelfMatrix4x4& m1, const SelfMatrix4x4& m2) {
	SelfMatrix4x4 result;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = m1.m[i][j] - m2.m[i][j];
		}
	}

	return result;
}

SelfMatrix4x4 MatrixMath::Multiply(const SelfMatrix4x4& m1, const SelfMatrix4x4& m2) {
	SelfMatrix4x4 result;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = 0.0f;
			for (int k = 0; k < 4; k++) {
				result.m[i][j] += m1.m[i][k] * m2.m[k][j];
			}
		}
	}

	return result;
}

SelfMatrix4x4 MatrixMath::Inverse(const SelfMatrix4x4& m) {
	float det = m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1] + m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2] +

	            m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2] + m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3] + m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0] +

	            m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0] + m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1] +

	            m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1] + m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2] + m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0] -

	            m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2] - m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1] -

	            m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3] - m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0] - m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2] -

	            m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1] - m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0] -

	            m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2] - m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0] - m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1];

	SelfMatrix4x4 result = {};
	if (std::fabsf(det) < 1e-6f) {
		return result;
	};
	float invDet = 1.0f / det;

	result.m[0][0] = (m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[1][2] * m.m[2][3] * m.m[3][1] + m.m[1][3] * m.m[2][1] * m.m[3][2] - m.m[1][1] * m.m[2][3] * m.m[3][2] -
	                  m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[1][3] * m.m[2][2] * m.m[3][1]) *
	                 invDet;

	result.m[1][0] = (m.m[1][0] * m.m[2][3] * m.m[3][2] + m.m[1][2] * m.m[2][0] * m.m[3][3] + m.m[1][3] * m.m[2][2] * m.m[3][0] - m.m[1][0] * m.m[2][2] * m.m[3][3] -
	                  m.m[1][2] * m.m[2][3] * m.m[3][0] - m.m[1][3] * m.m[2][0] * m.m[3][2]) *
	                 invDet;

	result.m[2][0] = (m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[1][1] * m.m[2][3] * m.m[3][0] + m.m[1][3] * m.m[2][0] * m.m[3][1] - m.m[1][0] * m.m[2][3] * m.m[3][1] -
	                  m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[1][3] * m.m[2][1] * m.m[3][0]) *
	                 invDet;

	result.m[3][0] = (m.m[1][0] * m.m[2][2] * m.m[3][1] + m.m[1][1] * m.m[2][0] * m.m[3][2] + m.m[1][2] * m.m[2][1] * m.m[3][0] - m.m[1][0] * m.m[2][1] * m.m[3][2] -
	                  m.m[1][1] * m.m[2][2] * m.m[3][0] - m.m[1][2] * m.m[2][0] * m.m[3][1]) *
	                 invDet;

	result.m[0][1] = (m.m[0][1] * m.m[2][3] * m.m[3][2] + m.m[0][2] * m.m[2][1] * m.m[3][3] + m.m[0][3] * m.m[2][2] * m.m[3][1] - m.m[0][1] * m.m[2][2] * m.m[3][3] -
	                  m.m[0][2] * m.m[2][3] * m.m[3][1] - m.m[0][3] * m.m[2][1] * m.m[3][2]) *
	                 invDet;

	result.m[1][1] = (m.m[0][0] * m.m[2][2] * m.m[3][3] + m.m[0][2] * m.m[2][3] * m.m[3][0] + m.m[0][3] * m.m[2][0] * m.m[3][2] - m.m[0][0] * m.m[2][3] * m.m[3][2] -
	                  m.m[0][2] * m.m[2][0] * m.m[3][3] - m.m[0][3] * m.m[2][2] * m.m[3][0]) *
	                 invDet;

	result.m[2][1] = (m.m[0][0] * m.m[2][3] * m.m[3][1] + m.m[0][1] * m.m[2][0] * m.m[3][3] + m.m[0][3] * m.m[2][1] * m.m[3][0] - m.m[0][0] * m.m[2][1] * m.m[3][3] -
	                  m.m[0][1] * m.m[2][3] * m.m[3][0] - m.m[0][3] * m.m[2][0] * m.m[3][1]) *
	                 invDet;

	result.m[3][1] = (m.m[0][0] * m.m[2][1] * m.m[3][2] + m.m[0][1] * m.m[2][2] * m.m[3][0] + m.m[0][2] * m.m[2][0] * m.m[3][1] - m.m[0][0] * m.m[2][2] * m.m[3][1] -
	                  m.m[0][1] * m.m[2][0] * m.m[3][2] - m.m[0][2] * m.m[2][1] * m.m[3][0]) *
	                 invDet;

	result.m[0][2] = (m.m[0][1] * m.m[1][2] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[3][1] + m.m[0][3] * m.m[1][1] * m.m[3][2] - m.m[0][1] * m.m[1][3] * m.m[3][2] -
	                  m.m[0][2] * m.m[1][1] * m.m[3][3] - m.m[0][3] * m.m[1][2] * m.m[3][1]) *
	                 invDet;

	result.m[1][2] = (m.m[0][0] * m.m[1][3] * m.m[3][2] + m.m[0][2] * m.m[1][0] * m.m[3][3] + m.m[0][3] * m.m[1][2] * m.m[3][0] - m.m[0][0] * m.m[1][2] * m.m[3][3] -
	                  m.m[0][2] * m.m[1][3] * m.m[3][0] - m.m[0][3] * m.m[1][0] * m.m[3][2]) *
	                 invDet;

	result.m[2][2] = (m.m[0][0] * m.m[1][1] * m.m[3][3] + m.m[0][1] * m.m[1][3] * m.m[3][0] + m.m[0][3] * m.m[1][0] * m.m[3][1] - m.m[0][0] * m.m[1][3] * m.m[3][1] -
	                  m.m[0][1] * m.m[1][0] * m.m[3][3] - m.m[0][3] * m.m[1][1] * m.m[3][0]) *
	                 invDet;

	result.m[3][2] = (m.m[0][0] * m.m[1][2] * m.m[3][1] + m.m[0][1] * m.m[1][0] * m.m[3][2] + m.m[0][2] * m.m[1][1] * m.m[3][0] - m.m[0][0] * m.m[1][1] * m.m[3][2] -
	                  m.m[0][1] * m.m[1][2] * m.m[3][0] - m.m[0][2] * m.m[1][0] * m.m[3][1]) *
	                 invDet;

	result.m[0][3] = (m.m[0][1] * m.m[1][3] * m.m[2][2] + m.m[0][2] * m.m[1][1] * m.m[2][3] + m.m[0][3] * m.m[1][2] * m.m[2][1] - m.m[0][1] * m.m[1][2] * m.m[2][3] -
	                  m.m[0][2] * m.m[1][3] * m.m[2][1] - m.m[0][3] * m.m[1][1] * m.m[2][2]) *
	                 invDet;

	result.m[1][3] = (m.m[0][0] * m.m[1][2] * m.m[2][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] + m.m[0][3] * m.m[1][0] * m.m[2][2] - m.m[0][0] * m.m[1][3] * m.m[2][2] -
	                  m.m[0][2] * m.m[1][0] * m.m[2][3] - m.m[0][3] * m.m[1][2] * m.m[2][0]) *
	                 invDet;

	result.m[2][3] = (m.m[0][0] * m.m[1][3] * m.m[2][1] + m.m[0][1] * m.m[1][0] * m.m[2][3] + m.m[0][3] * m.m[1][1] * m.m[2][0] - m.m[0][0] * m.m[1][1] * m.m[2][3] -
	                  m.m[0][1] * m.m[1][3] * m.m[2][0] - m.m[0][3] * m.m[1][0] * m.m[2][1]) *
	                 invDet;

	result.m[3][3] = (m.m[0][0] * m.m[1][1] * m.m[2][2] + m.m[0][1] * m.m[1][2] * m.m[2][0] + m.m[0][2] * m.m[1][0] * m.m[2][1] - m.m[0][0] * m.m[1][2] * m.m[2][1] -
	                  m.m[0][1] * m.m[1][0] * m.m[2][2] - m.m[0][2] * m.m[1][1] * m.m[2][0]) *
	                 invDet;

	return result;
}

SelfMatrix4x4 MatrixMath::Transpose(const SelfMatrix4x4& m) {
	return {
	    {{m.m[0][0], m.m[1][0], m.m[2][0], m.m[3][0]}, {m.m[0][1], m.m[1][1], m.m[2][1], m.m[3][1]}, {m.m[0][2], m.m[1][2], m.m[2][2], m.m[3][2]}, {m.m[0][3], m.m[1][3], m.m[2][3], m.m[3][3]}}
    };
}

SelfMatrix4x4 MatrixMath::MakeIdentity4x4() {
	return {
	    {{1.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f}}
    };
}

SelfMatrix4x4 MatrixMath::MakeTranslateMatrix(const SelfVec3& translate) {
	return {
	    {{1.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}, {translate.x, translate.y, translate.z, 1.0f}}
    };
}

SelfMatrix4x4 MatrixMath::MakeScaleMatrix(const SelfVec3& scale) {
	return {
	    {{scale.x, 0.0f, 0.0f, 0.0f}, {0.0f, scale.y, 0.0f, 0.0f}, {0.0f, 0.0f, scale.z, 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f}}
    };
}

SelfMatrix4x4 MatrixMath::MakeRotateXMatrix(const float& radian) {
	return {
	    {{1.0f, 0.0f, 0.0f, 0.0f}, {0.0f, std::cos(radian), std::sin(radian), 0.0f}, {0.0f, -std::sin(radian), std::cos(radian), 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f}}
    };
}

SelfMatrix4x4 MatrixMath::MakeRotateYMatrix(const float& radian) {
	return {
	    {{std::cos(radian), 0.0f, -std::sin(radian), 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, {std::sin(radian), 0.0f, std::cos(radian), 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f}}
    };
}

SelfMatrix4x4 MatrixMath::MakeRotateZMatrix(const float& radian) {
	return {
	    {{std::cos(radian), std::sin(radian), 0.0f, 0.0f}, {-std::sin(radian), std::cos(radian), 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f}}
    };
}

SelfMatrix4x4 MatrixMath::MakeRotatedMatrix(const SelfVec3& radian) {
	SelfMatrix4x4 matrixRotatedX{
	    {{1.0f, 0.0f, 0.0f, 0.0f}, {0.0f, cosf(radian.x), sinf(radian.x), 0.0f}, {0.0f, -sinf(radian.x), cosf(radian.x), 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f}}
    };

	SelfMatrix4x4 matrixRotatedY{
	    {{cosf(radian.y), 0.0f, -sinf(radian.y), 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, {sinf(radian.y), 0.0f, cosf(radian.y), 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f}}
    };

	SelfMatrix4x4 matrixRotatedZ{
	    {{cosf(radian.z), sinf(radian.z), 0.0f, 0.0f}, {-sinf(radian.z), cosf(radian.z), 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f}}
    };

	SelfMatrix4x4 result = MatrixMath::Multiply(matrixRotatedX, matrixRotatedY);
	return MatrixMath::Multiply(result, matrixRotatedZ);
}

KamataEngine::Matrix4x4 ToKamataEngine(const SelfMatrix4x4& m) {
	KamataEngine::Matrix4x4 result = {
	    {{m.m[0][0], m.m[0][1], m.m[0][2], m.m[0][3]}, {m.m[1][0], m.m[1][1], m.m[1][2], m.m[1][3]}, {m.m[2][0], m.m[2][1], m.m[2][2], m.m[2][3]}, {m.m[3][0], m.m[3][1], m.m[3][2], m.m[3][3]}}
    };

	return result;
}

SelfMatrix4x4 MatrixMath::MakeAffineMatrix(SelfVec3 scale, SelfVec3 radian, SelfVec3 translate) {
	float rotatedXCos = std::cos(radian.x);
	float rotatedXSin = std::sin(radian.x);
	float rotatedYCos = std::cos(radian.y);
	float rotatedYSin = std::sin(radian.y);
	float rotatedZCos = std::cos(radian.z);
	float rotatedZSin = std::sin(radian.z);

	SelfMatrix4x4 result = {
	    {{scale.x * (rotatedYCos * rotatedZCos), scale.x * (rotatedYCos * rotatedZSin), scale.x * (-rotatedYSin), 0.0f},
	     {scale.y * (rotatedXSin * rotatedYSin * rotatedZCos - rotatedXCos * rotatedZSin), scale.y * (rotatedXSin * rotatedYSin * rotatedZSin + rotatedXCos * rotatedZCos),
	      scale.y * (rotatedXSin * rotatedYCos), 0.0f},
	     {scale.z * (rotatedXCos * rotatedYSin * rotatedZCos + rotatedXSin * rotatedZSin), scale.z * (rotatedXCos * rotatedYSin * rotatedZSin - rotatedXSin * rotatedZCos),
	      scale.z * (rotatedXCos * rotatedYCos), 0.0f},
	     {translate.x, translate.y, translate.z, 1.0f}}
    };

	return result;
}

SelfMatrix4x4 MatrixMath::MakeAffineMatrix(const KamataEngine::Vector3& scale, const KamataEngine::Vector3& radian, const KamataEngine::Vector3& translate) {
	float rotatedXCos = std::cos(radian.x);
	float rotatedXSin = std::sin(radian.x);
	float rotatedYCos = std::cos(radian.y);
	float rotatedYSin = std::sin(radian.y);
	float rotatedZCos = std::cos(radian.z);
	float rotatedZSin = std::sin(radian.z);

	SelfMatrix4x4 result = {
	    {{scale.x * (rotatedYCos * rotatedZCos), scale.x * (rotatedYCos * rotatedZSin), scale.x * (-rotatedYSin), 0.0f},
	     {scale.y * (rotatedXSin * rotatedYSin * rotatedZCos - rotatedXCos * rotatedZSin), scale.y * (rotatedXSin * rotatedYSin * rotatedZSin + rotatedXCos * rotatedZCos),
	      scale.y * (rotatedXSin * rotatedYCos), 0.0f},
	     {scale.z * (rotatedXCos * rotatedYSin * rotatedZCos + rotatedXSin * rotatedZSin), scale.z * (rotatedXCos * rotatedYSin * rotatedZSin - rotatedXSin * rotatedZCos),
	      scale.z * (rotatedXCos * rotatedYCos), 0.0f},
	     {translate.x, translate.y, translate.z, 1.0f}}
    };

	return result;
}

SelfMatrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip) {
	SelfMatrix4x4 result = {
	    {
         {1.0f / (std::tanf(fovY / 2.0f) * aspectRatio), 0.0f, 0.0f, 0.0f},
         {0.0f, 1.0f / std::tanf(fovY / 2.0f), 0.0f, 0.0f},
         {0.0f, 0.0f, farClip / (farClip - nearClip), 1.0f},
         {
	            0.0f,
	            0.0f,
	            -nearClip * farClip / (farClip - nearClip),
	            0.0f,
	        }, }
    };

	return result;
}

SelfMatrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip) {
	SelfMatrix4x4 result = {
	    {{2.0f / (right - left), 0.0f, 0.0f, 0.0f},
	     {0.0f, 2.0f / (top - bottom), 0.0f, 0.0f},
	     {
	         0.0f,
	         0.0f,
	         1.0f / (farClip - nearClip),
	         0.0f,
	     }, {(left + right) / (left - right), (top + bottom) / (bottom - top), nearClip / (nearClip - farClip), 1.0f}}
    };

	return result;
}

SelfMatrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth) {
	SelfMatrix4x4 result = {
	    {
         {width / 2.0f, 0.0f, 0.0f, 0.0f},
         {0.0f, -height / 2.0f, 0.0f, 0.0f},
         {0.0f, 0.0f, maxDepth - minDepth, 0.0f},
         {left + width / 2.0f, top + height / 2.0f, minDepth, 1.0f},
	     }
    };

	return result;
}


} // namespace NemotoLibrary