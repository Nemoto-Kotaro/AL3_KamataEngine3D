#include "Enemy.h"
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

///=============初期化処理=============

void Enemy::Initialize(Model* model, Camera* camera, GameScene* gameScene, const SelfVec3& position) {
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = ToKamataEngine(position);
	worldTransform_.rotation_.y = std::numbers::pi_v<float> * -1.5f;
	WorldTransformUpdate(worldTransform_);

	velocity_ = SelfVec3(-kWalkSpeed, 0.0f, 0.0f);
	camera_ = camera;

	gameScene_ = gameScene;

	walkTimer_ = 0.0f;
}

///=============更新処理=============

void Enemy::Update() {
	if (behaviorRequest_ != Behavior::kUnknown) {
		behavior_ = behaviorRequest_;
		switch (behavior_) {
		case Enemy::Behavior::kRoot:
			BehaviorRootInitialize();
			break;
		case Enemy::Behavior::kDeath:
			BehaviorDeathInitialize();
			break;
		default:
			break;
		}

		behaviorRequest_ = Behavior::kUnknown;
	}

	switch (behavior_) {
	case Enemy::Behavior::kRoot:
		BehaviorRootUpdate();
		break;
	case Enemy::Behavior::kDeath:
		BehaviorDeathUpdate();
		break;
	default:
		break;
	}
}

void Enemy::UpdateMatrix() { WorldTransformUpdate(worldTransform_); }

///=============描画処理=============

void Enemy::Draw() { model_->Draw(worldTransform_, *camera_); }

//===========各ビヘイビア===========

void Enemy::BehaviorRootInitialize() { isCollisionDisabled_ = false; }

void Enemy::BehaviorRootUpdate() {
	worldTransform_.translation_ = ToKamataEngine(velocity_ + worldTransform_.translation_);

	// 歩きアニメーション
	walkTimer_ += 1.0f / 60.0f;

	float param = std::sin(walkTimer_);
	float degree = kWalkMotionAngleStart + kWalkMotionAngleEnd * (param + 1.0f) / 2.0f;
	worldTransform_.rotation_.x = DegTheta(degree);
}

void Enemy::BehaviorDeathInitialize() {
	deathCounter_ = 0.0f;
	isCollisionDisabled_ = true;
}

void Enemy::BehaviorDeathUpdate() {
	deathCounter_ += 1.0f / 60.0f;
	float t = deathCounter_ / deathDuration_;
	worldTransform_.rotation_.x = Lerp(0.0f, std::numbers::pi_v<float> * 0.5f, Ease::InSine(t));
	worldTransform_.rotation_.y = Lerp(std::numbers::pi_v<float> * -1.5f, std::numbers::pi_v<float> * -5.5f, Ease::InSine(t));

	if (deathCounter_ >= deathDuration_) {
		isDead_ = true;
	}
}

///=============更新処理の関数=============

void Enemy::OnCollision(const Player* player) {
	if (behavior_ == Behavior::kDeath) {
		return;
	}

	if (player->IsAttack()) {
		behaviorRequest_ = Behavior::kDeath;

		SelfVec3 effectPos = ((ToMyEngine(worldTransform_.translation_) + player->GetWorldPosition()) / 2.0f);
		gameScene_->CreateHitEffect(effectPos);
	}
}

///=============取得関数=============

SelfVec3 Enemy::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return ToMyEngine(worldPos);
}

AABB Enemy::GetAABB() { return AABB(GetWorldPosition(), SelfVec2(kWidth, kHeight)); }
