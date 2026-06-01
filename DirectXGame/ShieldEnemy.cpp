#include "ShieldEnemy.h"
#define NOMINMAX
#include "GameScene.h"
#include "Player.h"
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
void ShieldEnemy::Initialize(Model* model, Camera* camera, GameScene* gameScene, const SelfVec3& position) {
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = ToKamataEngine(position);
	worldTransform_.rotation_.y = DegTheta(kWalkMotionAngleStart);
	WorldTransformUpdate(worldTransform_);

	velocity_ = SelfVec3(-kWalkSpeed, 0.0f, 0.0f);
	camera_ = camera;

	gameScene_ = gameScene;

	walkTimer_ = 0.0f;
}

void ShieldEnemy::Update() {
	if (behaviorRequest_ != Behavior::kUnknown) {
		behavior_ = behaviorRequest_;
		switch (behavior_) {
		case Behavior::kRoot:
			BehaviorRootInitialize();
			break;
		case Behavior::kDeath:
			BehaviorDeathInitialize();
			break;
		case Behavior::kGuard:
			BehaviorGuardInitialize();
			break;
		default:
			break;
		}

		behaviorRequest_ = Behavior::kUnknown;
	}

	switch (behavior_) {
	case Behavior::kRoot:
		BehaviorRootUpdate();
		break;
	case Behavior::kDeath:
		BehaviorDeathUpdate();
		break;
	case Behavior::kGuard:
		BehaviorGuardUpdate();
		break;
	default:
		break;
	}
}

//===========各ビヘイビア===========

void ShieldEnemy::BehaviorRootInitialize() { isCollisionDisabled_ = false; }

void ShieldEnemy::BehaviorRootUpdate() {
	worldTransform_.translation_ = ToKamataEngine(velocity_ + worldTransform_.translation_);

	// 歩きアニメーション
	walkTimer_ += 1.0f / 60.0f;

	float param = std::cos(walkTimer_);
	float degree = kWalkMotionAngleStart + kWalkMotionAngleEnd * (param + 1.0f) / 2.0f;
	worldTransform_.rotation_.y = DegTheta(degree);
}

void ShieldEnemy::BehaviorDeathInitialize() {
	deathCounter_ = 0.0f;
	isCollisionDisabled_ = true;
}

void ShieldEnemy::BehaviorDeathUpdate() {
	deathCounter_ += 1.0f / 60.0f;
	float t = deathCounter_ / deathDuration_;
	worldTransform_.rotation_.x = Lerp(0.0f, std::numbers::pi_v<float> * 0.5f, Ease::InSine(t));
	worldTransform_.rotation_.y = Lerp(std::numbers::pi_v<float> * -1.5f, std::numbers::pi_v<float> * -5.5f, Ease::InSine(t));

	if (deathCounter_ >= deathDuration_) {
		isDead_ = true;
	}
}

void ShieldEnemy::BehaviorGuardInitialize() { guardCounter_ = 0.0f; }

void ShieldEnemy::BehaviorGuardUpdate() {
	guardCounter_ += 1.0f / 60.0f;
	float t = guardCounter_ / guardDuration_;
	float param = std::sin(t * std::numbers::pi_v<float>);
	worldTransform_.rotation_.x = param * DegTheta(60.0f);
	if (guardCounter_ >= guardDuration_) {
		behaviorRequest_ = Behavior::kRoot;
	}
}

///=============更新処理の関数=============

void ShieldEnemy::OnCollision(Player* player) {
	if (behavior_ == Behavior::kDeath) {
		return;
	}

	if (player->IsAttack()) {
		// 左右向かい合う(向いている向きが違う)ならガード
		if (player->GetLRDirection() != lrDirection_) {
			player->RequestKnockback();
			SelfVec3 effectPos = ((ToMyEngine(worldTransform_.translation_) + player->GetWorldPosition()) / 2.0f);
			gameScene_->CreateGuardEffect(effectPos);
			behaviorRequest_ = Behavior::kGuard;
			return;
		}

		behaviorRequest_ = Behavior::kDeath;

		SelfVec3 effectPos = ((ToMyEngine(worldTransform_.translation_) + player->GetWorldPosition()) / 2.0f);
		gameScene_->CreateHitEffect(effectPos);
	}
}
