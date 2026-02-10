#include "Enemy.h"
#define NOMINMAX
#include "WorldTransform.h"
#include "easing.h"
#include "mathTypes.h"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <numbers>

using namespace KamataEngine;
using namespace NemotoLibrary;

void Enemy::Initialize(Model* model, Camera* camera, const SelfVec3& position) {
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = ToKamataEngine(position);
	worldTransform_.rotation_.y = std::numbers::pi_v<float> * -1.5f;

	velocity_ = SelfVec3(-kWalkSpeed, 0.0f, 0.0f);
	camera_ = camera;

	walkTimer_ = 0.0f;
}

void Enemy::Update() {
	worldTransform_.translation_ = ToKamataEngine(velocity_ + worldTransform_.translation_);

	// 歩きアニメーション
	walkTimer_ += 1.0f / 60.0f;

	float param = std::sin(walkTimer_);
	float degree = kWalkMotionAngleStart + kWalkMotionAngleEnd * (param + 1.0f) / 2.0f;
	worldTransform_.rotation_.x = DegTheta(degree);

	WorldTransformUpdate(worldTransform_);
}

void Enemy::Draw() { model_->Draw(worldTransform_, *camera_); }

SelfVec3 Enemy::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return ToMyEngine(worldPos);
}

AABB Enemy::GetAABB() { return AABB(GetWorldPosition(), SelfVec2(kWidth, kHeight)); }

void Enemy::OnCollision(const Player* player) { (void)player; }
