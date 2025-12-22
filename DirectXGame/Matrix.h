#pragma once
#include "KamataEngine.h"

KamataEngine::Matrix4x4 ScaleMatrix(KamataEngine::Vector3 scale);
KamataEngine::Matrix4x4 RotatedMatrix(KamataEngine::Vector3 theta);
KamataEngine::Matrix4x4 TranslateMatrix(KamataEngine::Vector3 translate);

KamataEngine::Matrix4x4 Multiply(const KamataEngine::Matrix4x4& matrixA, const KamataEngine::Matrix4x4& matrixB);

KamataEngine::Matrix4x4 MakeAffineMatrix(KamataEngine::Vector3 scale, KamataEngine::Vector3 theta, KamataEngine::Vector3 translate);