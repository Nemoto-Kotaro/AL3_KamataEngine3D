#define NOMINMAX
#include "Player.h"
#include "GlobalVariables.h"
#include "MapChipField.h"
#include "WorldTransform.h"
#include "easing.h"
#include "mathTypes.h"
#include <algorithm>
#include <cassert>
#include <numbers>

using namespace KamataEngine;
using namespace NemotoLibrary;

void Player::RegisterGlobalVariables() {
	GlobalVariables* globalVariables = GlobalVariables::GetInstance();
	const char* groupName = "Player";
	GlobalVariables::GetInstance()->CreatGroup(groupName);

	globalVariables->AddItem(groupName, "kWidth", kWidth);
	globalVariables->AddItem(groupName, "kHeight", kHeight);
	globalVariables->AddItem(groupName, "kBlank", kBlank);
	globalVariables->AddItem(groupName, "deathDuration_", deathDuration_);
	globalVariables->AddItem(groupName, "deathVanishDuration_", deathVanishDuration_);
	globalVariables->AddItem(groupName, "kAcceleration", kAcceleration);
	globalVariables->AddItem(groupName, "kLimitRunSpeed", kLimitRunSpeed);
}

void Player::ApplyGlobalVariables() {
	GlobalVariables* globalVariables = GlobalVariables::GetInstance();
	const char* groupName = "Player";
	kWidth = globalVariables->GetFloatValue(groupName, "kWidth");
	kHeight = globalVariables->GetFloatValue(groupName, "kHeight");
	kBlank = globalVariables->GetFloatValue(groupName, "kBlank");
	deathDuration_ = globalVariables->GetFloatValue(groupName, "deathDuration_");
	deathVanishDuration_ = globalVariables->GetFloatValue(groupName, "deathVanishDuration_");
	kAcceleration = globalVariables->GetFloatValue(groupName, "kAcceleration");
	kLimitRunSpeed = globalVariables->GetFloatValue(groupName, "kLimitRunSpeed");
}

///=============初期化処理=============

void Player::Initialize(Model* model, Model* modelAttack, Camera* camera, const SelfVec3& position) {

	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = ToKamataEngine(position);
	worldTransform_.rotation_.y = std::numbers::pi_v<float> * -0.5f;

	assert(modelAttack);
	modelAttack_ = modelAttack;
	worldTransformAttack_.Initialize();
	objectColor_.Initialize();
	camera_ = camera;
}

///=============更新処理=============

void Player::Update() {
	// このif文ちょい汚いが死んでるか死んでないかしかないのでいまは許容
	if (!isDead_) {

		if (isRequestKnockback_) {
			behaviorRequest_ = Behavior::kKnockback;
			isRequestKnockback_ = false;
		}

		if (behaviorRequest_ != Behavior::kUnknown) {
			behavior_ = behaviorRequest_;
			switch (behavior_) {
			case Player::Behavior::kRoot:
				BehaviorRootInitialize();
				break;
			case Player::Behavior::kAttack:
				BehaviorAttackInitialize();
				break;
			case Player::Behavior::kKnockback:
				BehaviorKnockbackInitialize();
				break;
			default:
				break;
			}

			behaviorRequest_ = Behavior::kUnknown;
		}

		switch (behavior_) {
		case Player::Behavior::kRoot:
			BehaviorRootUpdate();
			break;
		case Player::Behavior::kAttack:
			BehaviorAttackUpdate();
			break;
		case Player::Behavior::kKnockback:
			BehaviorKnockbackUpdate();
			break;
		default:
			break;
		}

		CollisionMapInfo collisionMapInfo = {};
		collisionMapInfo.MoveOffset = velocity_;
		// 衝突チェック
		MapCollision(collisionMapInfo);

		// 結果を反映して移動
		worldTransform_.translation_ = ToKamataEngine(collisionMapInfo.MoveOffset + worldTransform_.translation_);

		// 天井に接している場合の処理
		IsHitCeiling(collisionMapInfo);

		// 地面に接しているときの処理
		IsHitGround(collisionMapInfo);

		// 壁に接しているときの処理
		IsHitWall(collisionMapInfo);

		if (turnTimer_ > 0.0f) {
			turnTimer_ -= 1.0f / 60.0f;

			// 回転処理
			float destinationRotationYTable[] = {std::numbers::pi_v<float> / 2.0f, std::numbers::pi_v<float> * -0.5f};
			float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];
			float timeRatio = 1.0f - (turnTimer_ / kTimerTurn);

			worldTransform_.rotation_.y = Lerp(turnFirstRotationY_, destinationRotationY, Ease::InOutSine(timeRatio));
		}

	} else {

		// スクロールで死んだときのデス演出
		if (isScrollPushDead_) {
			deathCounter_ += 1.0f / 60.0f;

			float t = std::clamp(deathCounter_ / deathDuration_, 0.0f, 1.0f);
			worldTransform_.rotation_.x = Lerp(0.0f, std::numbers::pi_v<float> * 0.5f, Ease::InSine(t));
			worldTransform_.rotation_.y = Lerp(deathDirectionStrat, deathDirectionEnd, Ease::InSine(t));

			Vector4 color_ = {1.0f, 1.0f, 1.0f, 1.0f};
			color_.w = std::clamp(1.0f - Ratio(deathCounter_, 0.0f, deathVanishDuration_), 0.0f, 1.0f);
			objectColor_.SetColor(color_);
		}
	}
}

void Player::UpdateMatrix() {
	WorldTransformUpdate(worldTransform_);

	if (behavior_ == Behavior::kAttack) {
		worldTransformAttack_.translation_ = worldTransform_.translation_;
		worldTransformAttack_.rotation_ = worldTransform_.rotation_;
		WorldTransformUpdate(worldTransformAttack_);
	}
}

///=============描画処理=============

void Player::Draw() {
	model_->Draw(worldTransform_, *camera_, &objectColor_);
	if (behavior_ == Behavior::kAttack) {
		modelAttack_->Draw(worldTransformAttack_, *camera_);
	}
}

//==============各ビヘイビアの処理=================

//---ルートビヘイビア---
void Player::BehaviorRootInitialize() { velocity_ = SelfVec3(0.0f, 0.0f, 0.0f); }

void Player::BehaviorRootUpdate() {
	if (Input::GetInstance()->PushKey(DIK_SPACE)) {
		behaviorRequest_ = Behavior::kAttack;
	}

	// 移動入力
	MoveInPut();
}

//---アタックビヘイビア---
void Player::BehaviorAttackInitialize() {
	attackPhase_ = AttackPhase::kCharge;
	attackCounter_ = 0.0f;
}

void Player::BehaviorAttackUpdate() {
	attackCounter_ += 1.0f / 60.0f;

	switch (attackPhase_) {
	case Player::AttackPhase::kCharge:
	default: {
		float t = attackCounter_ / attackChargeDuration;
		worldTransform_.scale_.z = Lerp(1.0f, 0.3f, Ease::OutSine(t));
		worldTransform_.scale_.y = Lerp(1.0f, 1.6f, Ease::OutSine(t));

		if (attackCounter_ >= attackChargeDuration) {
			attackPhase_ = AttackPhase::kDash;
			attackCounter_ = 0.0f;
		}

		break;
	}

	case Player::AttackPhase::kDash: {

		float t = attackCounter_ / attackDashDuration;
		worldTransform_.scale_.z = Lerp(0.3f, 1.3f, Ease::OutSine(t));
		worldTransform_.scale_.y = Lerp(1.6f, 0.7f, Ease::OutSine(t));

		if (attackCounter_ >= attackDashDuration) {
			attackPhase_ = AttackPhase::kRecovery;
			attackCounter_ = 0.0f;
		}

		velocity_ = kAttackVelocity;
		if (lrDirection_ != LRDirection::kRight) {
			velocity_.x *= -1.0f;
		}

		break;
	}
	case Player::AttackPhase::kRecovery: {
		float t = attackCounter_ / attackRecoveryDuration;
		worldTransform_.scale_.z = Lerp(1.3f, 1.0f, Ease::OutSine(t));
		worldTransform_.scale_.y = Lerp(0.7f, 1.0f, Ease::OutSine(t));
		if (attackCounter_ >= attackRecoveryDuration) {
			behaviorRequest_ = Behavior::kRoot;
		}
		break;
	}
	}
}

//---ノックバックビヘイビア---

void Player::BehaviorKnockbackInitialize() {
	knockbackPhase_ = KnockbackPhase::kKnockback;
	knockbackCounter_ = 0.0f;
	lerpStrat_.z = worldTransform_.scale_.z;
	lerpStrat_.y = worldTransform_.scale_.y;
}

void Player::BehaviorKnockbackUpdate() {
	knockbackCounter_ += 1.0f / 60.0f;
	switch (knockbackPhase_) {
	case Player::KnockbackPhase::kKnockback: {

		float t = knockbackCounter_ / knockbackDuration;
		worldTransform_.scale_.z = Lerp(lerpStrat_.z, 1.0f, Ease::OutSine(t));
		worldTransform_.scale_.y = Lerp(lerpStrat_.y, 1.0f, Ease::OutSine(t));

		float force = Lerp(1.0f, 0.5f, Ease::OutSine(t));
		velocity_.x = knockbackPower * force;
		if (lrDirection_ != LRDirection::kRight) {
			velocity_.x *= -1.0f;
		}

		if (knockbackCounter_ >= knockbackDuration) {
			knockbackCounter_ = 0.0f;
			knockbackPhase_ = KnockbackPhase::kDown;
		}

		break;
	}
	case Player::KnockbackPhase::kDown:
		if (knockbackCounter_ >= knockbackDownDuration) {
			behaviorRequest_ = Behavior::kRoot;
		}
		break;
	default:
		break;
	}
}

///=============更新処理の関数=============

// 移動入力
void Player::MoveInPut() {
	if (onGround_) {
		if (Input::GetInstance()->PushKey(DIK_RIGHT) || Input::GetInstance()->PushKey(DIK_LEFT)) {
			SelfVec3 acceleration = {};

			if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
				if (velocity_.x < 0.0f) {
					velocity_.x *= (1.0f - kAttenuation);
				}

				acceleration.x += kAcceleration;

				if (lrDirection_ != LRDirection::kRight) {
					lrDirection_ = LRDirection::kRight;
					turnFirstRotationY_ = worldTransform_.rotation_.y;
					turnTimer_ = kTimerTurn;
				}

			} else if (Input::GetInstance()->PushKey(DIK_LEFT)) {
				if (velocity_.x > 0.0f) {
					velocity_.x *= (1.0f - kAttenuation);
				}

				acceleration.x -= kAcceleration;

				if (lrDirection_ != LRDirection::kLeft) {
					lrDirection_ = LRDirection::kLeft;
					turnFirstRotationY_ = worldTransform_.rotation_.y;
					turnTimer_ = kTimerTurn;
				}
			}

			velocity_ += acceleration;

			velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);
		} else {
			velocity_.x *= (1.0f - kAttenuation);
		}

		// ジャンプ入力
		if (Input::GetInstance()->PushKey(DIK_UP)) {
			velocity_ += SelfVec3(0.0f, kJumpAcceleration, 0.0f);
		}

	} else {
		velocity_ += SelfVec3(0.0f, -kGravityAcceleration, 0.0f);
		velocity_.y = std::max(velocity_.y, -kLimitFallSpeed);
	}
}

#pragma region 衝突と衝突時処理

void Player::MapCollision(CollisionMapInfo& info) {

	MapCollisionTop(info);
	MapCollisionBottom(info);
	MapCollisionRight(info);
	MapCollisionLeft(info);
}

// 方向処理の共通化
bool Player::IsMapBlockEdgeHit(CollisionMapInfo& info, RectSide dir, IndexSet& indexSet) {
	int dirNum = static_cast<int>(dir);

	// 方向ごとの処理テーブル
	static constexpr Corner corner[static_cast<int>(RectSide::kDirCount)][2] = {
	    {kLeftTop,    kRightTop   },
	    {kLeftBottom, kRightBottom},
	    {kRightTop,   kRightBottom},
	    {kLeftTop,    kLeftBottom },
	};

	// mapChipTypeNext判定で使う
	static constexpr int DirectionOffset[static_cast<int>(RectSide::kDirCount)][2] = {
	    {0,  1 }, //  上
	    {0,  -1}, //  下
	    {-1, 0 }, //  左
	    {1,  0 }, //  右
	};

	// 移動後を中心にして頂点を取得
	std::array<SelfVec3, kNumCorner> positionNew;
	for (uint32_t i = 0; i < positionNew.size(); i++) {
		positionNew[i] = CornerPosition(info.MoveOffset + worldTransform_.translation_, static_cast<Corner>(i));
	}

	MapChipType mapChipType;
	MapChipType mapChipTypeNext;
	bool hit = false;

	for (int i = 0; i < 2; i++) {
		indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionNew[corner[dirNum][i]]);
		// 現在のチップと、進行方向1つ隣のチップを取得
		mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
		mapChipTypeNext = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex + DirectionOffset[dirNum][0], indexSet.yIndex + DirectionOffset[dirNum][1]);
		// 連続したブロックを認識して処理
		if (mapChipType == MapChipType::kBlock && mapChipTypeNext != MapChipType::kBlock) {
			hit = true;
		}
	}

	if (hit) {
		// hit時はここの値がrectに参照される
		indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionNew[corner[dirNum][0]]);
		IndexSet indexSetShow = mapChipField_->GetMapChipIndexSetByPosition(CornerPosition(ToMyEngine(worldTransform_.translation_), corner[dirNum][0]));
		uint32_t cmpIndexSet[2] = {indexSet.xIndex, indexSet.yIndex};
		uint32_t cmpIndexSetShow[2] = {indexSetShow.xIndex, indexSetShow.yIndex};

		// 移動方向に応じて比較する軸を切り替える
		// 横移動ならx比較、縦移動ならy比較、DirectionOffsetを再利用してるので分かりずらい
		// abs(Next[dirNum][1]) : 0=x軸, 1=y軸
		if (cmpIndexSet[abs(DirectionOffset[dirNum][1])] != cmpIndexSetShow[abs(DirectionOffset[dirNum][1])]) {
			return true;
		}
	}

	return false;
}

// 上方向の当たり判定
void Player::MapCollisionTop(CollisionMapInfo& info) {
	if (info.MoveOffset.y <= 0.0f) {
		return;
	}

	IndexSet indexSet;
	// ここのヒット関数でindexの更新も行っている
	if (IsMapBlockEdgeHit(info, RectSide::kTop, indexSet)) {
		MapChipField::Rect rect = mapChipField_->GetRectByIndex(indexSet.xIndex, indexSet.yIndex);
		float moveY = (rect.bottom - worldTransform_.translation_.y) - (kHeight / 2.0f + kBlank);
		info.MoveOffset.y = std::max(0.0f, moveY);
		info.isCeilingHit = true;
	}
}

// 下方向の当たり判定
void Player::MapCollisionBottom(CollisionMapInfo& info) {
	if (info.MoveOffset.y >= 0.0f) {
		return;
	}

	IndexSet indexSet;
	if (IsMapBlockEdgeHit(info, RectSide::kBottom, indexSet)) {
		MapChipField::Rect rect = mapChipField_->GetRectByIndex(indexSet.xIndex, indexSet.yIndex);
		float moveY = (rect.top - worldTransform_.translation_.y) + (kHeight / 2.0f + kBlank);
		info.MoveOffset.y = std::min(0.0f, moveY);
		info.isGroundHit = true;
	}
}

// 右方向の当たり判定
void Player::MapCollisionRight(CollisionMapInfo& info) {
	if (info.MoveOffset.x <= 0.0f) {
		return;
	}

	IndexSet indexSet;
	if (IsMapBlockEdgeHit(info, RectSide::kRight, indexSet)) {
		MapChipField::Rect rect = mapChipField_->GetRectByIndex(indexSet.xIndex, indexSet.yIndex);
		float moveX = (rect.left - worldTransform_.translation_.x) - (kWidth / 2.0f + kBlank);
		info.MoveOffset.x = std::max(0.0f, moveX);
		info.isWallHit = true;
	}
}

// 左方向の当たり判定
void Player::MapCollisionLeft(CollisionMapInfo& info) {
	if (info.MoveOffset.x >= 0.0f) {
		return;
	}

	IndexSet indexSet;
	if (IsMapBlockEdgeHit(info, RectSide::kLeft, indexSet)) {
		MapChipField::Rect rect = mapChipField_->GetRectByIndex(indexSet.xIndex, indexSet.yIndex);
		float moveX = (rect.right - worldTransform_.translation_.x) + (kWidth / 2.0f + kBlank);
		info.MoveOffset.x = std::min(0.0f, moveX);
		info.isWallHit = true;
	}
}

void Player::IsHitCeiling(const CollisionMapInfo& info) {
	if (info.isCeilingHit) {
		DebugText::GetInstance()->ConsolePrintf("hit ceiling\n");
		velocity_.y = 0.0f;
	}
}

void Player::IsHitGround(const CollisionMapInfo& info) {

	if (onGround_) {
		if (velocity_.y > 0.0f) {
			onGround_ = false;
		} else {
			// 地面の接触処理
			std::array<SelfVec3, kNumCorner> positionNew;
			for (uint32_t i = 0; i < positionNew.size(); i++) {
				positionNew[i] = CornerPosition(info.MoveOffset + worldTransform_.translation_, static_cast<Corner>(i));
			}

			MapChipType mapChipType;

			bool hit = false;
			// 左下
			IndexSet indexSet;
			indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionNew[kLeftBottom] + SelfVec3(0.0f, -kBlank, 0.0f));
			mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
			if (mapChipType == MapChipType::kBlock) {
				hit = true;
			}

			// 右下
			indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionNew[kRightBottom] + SelfVec3(0.0f, -kBlank, 0.0f));
			mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
			if (mapChipType == MapChipType::kBlock) {
				hit = true;
			}

			if (!hit) {
				onGround_ = false;
			}
		}

	} else {
		if (info.isGroundHit) {
			velocity_.x *= (1.0f - kAttenuationLanding);
			velocity_.y = 0.0f;
			onGround_ = true;
		}
	}
}

void Player::IsHitWall(const CollisionMapInfo& info) {
	if (info.isWallHit) {
		velocity_.x *= (1.0f - kAttenuationWall);
	}
}

#pragma endregion

void Player::OnCollision(const BaseEnemy* enemy) {
	if (IsAttack() || IsKnockback()) {
		return;
	}

	(void)enemy;

	isDead_ = true;
}

void Player::ScrollPush(const SelfVec3& cameraTrans, float halfWidth) {
	CollisionMapInfo collisionMapInfo = {};
	collisionMapInfo.MoveOffset.x = std::clamp(worldTransform_.translation_.x, cameraTrans.x - halfWidth + kWidth / 2.0f, cameraTrans.x + halfWidth - kWidth / 2.0f) - worldTransform_.translation_.x;
	IndexSet indexSet;

	// 専用判定を用意した方がいいが流用可能なので利用
	if (IsMapBlockEdgeHit(collisionMapInfo, RectSide::kRight, indexSet)) {
		// めり込んでいた場合死亡

		isDead_ = true;
		isScrollPushDead_ = true;
		deathDirectionStrat = worldTransform_.rotation_.y;
		deathDirectionEnd = worldTransform_.rotation_.y + std::numbers::pi_v<float> * -4.0f;
	}

	// めりこみ関係なく位置は動かしてしまう
	worldTransform_.translation_.x += collisionMapInfo.MoveOffset.x;
}

SelfVec3 Player::CornerPosition(const NemotoLibrary::SelfVec3& center, Corner corner) {
	SelfVec3 offsetTable[kNumCorner] = {
	    {+kWidth / 2.0f, -kHeight / 2.0f, 0.0f},
	    {-kWidth / 2.0f, -kHeight / 2.0f, 0.0f},
	    {+kWidth / 2.0f, +kHeight / 2.0f, 0.0f},
	    {-kWidth / 2.0f, +kHeight / 2.0f, 0.0f},
	};

	return center + offsetTable[static_cast<uint32_t>(corner)];
}

///=============取得関数=============

SelfVec3 Player::GetWorldPosition() const {
	Vector3 worldPos;
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return ToMyEngine(worldPos);
}

AABB Player::GetAABB() { return AABB(GetWorldPosition(), SelfVec2(kWidth, kHeight)); }

bool Player::IsAttack() const {
	if (behavior_ == Behavior::kAttack) {
		return true;
	}
	return false;
}

bool Player::IsKnockback() const {
	if (behavior_ == Behavior::kKnockback) {
		return true;
	}
	return false;
}