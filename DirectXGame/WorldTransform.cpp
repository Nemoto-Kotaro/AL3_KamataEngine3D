#include "WorldTransform.h"
using namespace NemotoLibrary;

void WorldTransformUpdate(KamataEngine::WorldTransform& worldTransform) {
	worldTransform.matWorld_ = ToKamataEngine(MatrixMath::MakeAffineMatrix(worldTransform.scale_, worldTransform.rotation_, worldTransform.translation_));
	worldTransform.TransferMatrix();
}