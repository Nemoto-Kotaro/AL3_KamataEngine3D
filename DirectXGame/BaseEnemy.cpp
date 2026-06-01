#include "BaseEnemy.h"
#define NOMINMAX
#include "Player.h"
#include "GameScene.h"
#include "WorldTransform.h"
#include "easing.h"
#include "mathTypes.h"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <numbers>

using namespace KamataEngine;
using namespace NemotoLibrary;




void BaseEnemy::UpdateMatrix() { WorldTransformUpdate(worldTransform_); }


void BaseEnemy::Draw() { model_->Draw(worldTransform_, *camera_); }





///=============取得関数=============

SelfVec3 BaseEnemy::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return ToMyEngine(worldPos);
}

AABB BaseEnemy::GetAABB() { return AABB(GetWorldPosition(), GetSize()); }