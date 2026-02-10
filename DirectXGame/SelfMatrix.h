#pragma once
#include "KamataEngine.h"
namespace NemotoLibrary {
struct SelfVec3;
}

namespace NemotoLibrary {

struct SelfMatrix4x4 {
	float m[4][4];

	void operator+=(const SelfMatrix4x4& rhs);
	SelfMatrix4x4 operator+(const SelfMatrix4x4& rhs) const;

	void operator-=(const SelfMatrix4x4& rhs);
	SelfMatrix4x4 operator-(const SelfMatrix4x4& rhs) const;
};

KamataEngine::Matrix4x4 ToKamataEngine(const SelfMatrix4x4& m);

namespace MatrixMath {

SelfMatrix4x4 Add(const SelfMatrix4x4& m1, const SelfMatrix4x4& m2);
SelfMatrix4x4 Subtract(const SelfMatrix4x4& m1, const SelfMatrix4x4& m2);
SelfMatrix4x4 Multiply(const SelfMatrix4x4& m1, const SelfMatrix4x4& m2);
SelfMatrix4x4 Inverse(const SelfMatrix4x4& m);
SelfMatrix4x4 Transpose(const SelfMatrix4x4& m);
SelfMatrix4x4 MakeIdentity4x4();
SelfMatrix4x4 MakeTranslateMatrix(const SelfVec3& translate);
SelfMatrix4x4 MakeScaleMatrix(const SelfVec3& scale);
SelfMatrix4x4 MakeRotateXMatrix(const float& radian);
SelfMatrix4x4 MakeRotateYMatrix(const float& radian);
SelfMatrix4x4 MakeRotateZMatrix(const float& radian);
SelfMatrix4x4 MakeRotatedMatrix(const SelfVec3& radian);
SelfMatrix4x4 MakeAffineMatrix(SelfVec3 scale, SelfVec3 radian, SelfVec3 translate);
SelfMatrix4x4 MakeAffineMatrix(const KamataEngine::Vector3& scale, const KamataEngine::Vector3& radian, const KamataEngine::Vector3& translate);
}; // namespace MatrixMath

namespace MatrixRenderingPipeline {

SelfMatrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);
SelfMatrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);
SelfMatrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);

};

} // namespace NemotoLibrary
