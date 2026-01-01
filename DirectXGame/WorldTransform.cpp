#include "WorldTransform.h"

void WorldTransformUpdate(KamataEngine::WorldTransform& worldTransform) {
	worldTransform.matWorld_ = MakeAffineMatrix(worldTransform.scale_, worldTransform.rotation_, worldTransform.translation_);
	worldTransform.TransferMatrix();
}