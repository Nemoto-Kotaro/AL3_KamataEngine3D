#define NOMINMAX
#include "Player.h"
#include "MapChipField.h"
#include "WorldTransform.h"
#include "easing.h"
#include "mathTypes.h"
#include <algorithm>
#include <cassert>
#include <numbers>

using namespace KamataEngine;

void Player::Initialize(Model* model, Camera* camera, const Vector3& position) {
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.rotation_.y = std::numbers::pi_v<float> * -0.5f;

	camera_ = camera;
}

void Player::Update() {
	

	// 移動入力
	MoveInPut();
	CollisionMapInfo collisionMapInfo = {};
	collisionMapInfo.MoveOffset = ChangeVector3(velocity_);

	// 衝突チェック
	MapCollision(collisionMapInfo);

	// 結果を反映して移動
	worldTransform_.translation_ = ChangeVector3(ChangeSelfVec3(collisionMapInfo.MoveOffset) +worldTransform_.translation_);

	//天井に接している場合の処理
	IsHitCeiling(collisionMapInfo);


	// 接地確認
	bool landing = false;
	if (velocity_.y < 0.0f) {
		if (worldTransform_.translation_.y <= 1.0f) {
			landing = true;
		}
	}

	if (onGround_) {
		if (velocity_.y > 0.0f) {
			onGround_ = false;
		}

	} else {
		if (landing) {
			worldTransform_.translation_.y = 1.0f;
			velocity_.x *= (1.0f - kAttenuation);
			velocity_.y = 0.0f;
			onGround_ = true;
		}
	}

	if (turnTimer_ > 0.0f) {
		turnTimer_ -= 1.0f / 60.0f;

		// 回転処理
		float destinationRotationYTable[] = {std::numbers::pi_v<float> / 2.0f, std::numbers::pi_v<float> * -0.5f};
		float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];
		float timeRatio = 1.0f - (turnTimer_ / kTimerTurn);

		worldTransform_.rotation_.y = Lerp(turnFirstRotationY_, destinationRotationY, Ease::InOutSine(timeRatio));
	}

	WorldTransformUpdate(worldTransform_);
}

void Player::Draw() { model_->Draw(worldTransform_, *camera_); }

///=============更新処理=============

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

void Player::MapCollision(CollisionMapInfo& info) {

	MapCollisionTop(info);
	MapCollisionBottom(info);
	MapCollisionRight(info);
	MapCollisionLeft(info);
}

// 上方向の当たり判定
void Player::MapCollisionTop(CollisionMapInfo& info) {
	if (info.MoveOffset.y <= 0.0f) {
		return;
	}

	std::array<SelfVec3, kNumCorner> positionNew;
	for (uint32_t i = 0; i < positionNew.size(); i++) {
		positionNew[i] = CornerPosition(ChangeVector3(ChangeSelfVec3(info.MoveOffset) + worldTransform_.translation_), static_cast<Corner>(i));
	}

	MapChipType mapChipType;

	bool hit = false;
	// 左上
	MapChipField::IndexSet indexSet;
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(ChangeVector3(positionNew[kLeftTop]));
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	if (mapChipType == MapChipType::kBlock) {
		hit = true;
	}

	// 右上
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(ChangeVector3(positionNew[kRightTop]));
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	if (mapChipType == MapChipType::kBlock) {
		hit = true;
	}

	if (hit) {
		indexSet = mapChipField_->GetMapChipIndexSetByPosition(ChangeVector3(positionNew[kLeftTop]));
		MapChipField::Rect rect = mapChipField_->GetRectByIndex(indexSet.xIndex, indexSet.yIndex);
		float moveY = (rect.bottom - worldTransform_.translation_.y) - (kHeight / 2.0f - kBlank);
		info.MoveOffset.y = std::max(0.0f, moveY);
		info.isCeilingHit = true;
	}
}

// 下方向の当たり判定
void Player::MapCollisionBottom(CollisionMapInfo& info) {
	if (info.MoveOffset.y >= 0.0f) {
		return;
	}

	std::array<SelfVec3, kNumCorner> positionNew;
	for (uint32_t i = 0; i < positionNew.size(); i++) {
		positionNew[i] = CornerPosition(ChangeVector3(ChangeSelfVec3(info.MoveOffset) + worldTransform_.translation_), static_cast<Corner>(i));
	}
}

// 右方向の当たり判定
void Player::MapCollisionRight(CollisionMapInfo& info) {
	if (info.MoveOffset.x <= 0.0f) {
		return;
	}

	std::array<SelfVec3, kNumCorner> positionNew;
	for (uint32_t i = 0; i < positionNew.size(); i++) {
		positionNew[i] = CornerPosition(ChangeVector3(ChangeSelfVec3(info.MoveOffset) + worldTransform_.translation_), static_cast<Corner>(i));
	}
}

// 左方向の当たり判定
void Player::MapCollisionLeft(CollisionMapInfo& info) {
	if (info.MoveOffset.x >= 0.0f) {
		return;
	}

	std::array<SelfVec3, kNumCorner> positionNew;
	for (uint32_t i = 0; i < positionNew.size(); i++) {
		positionNew[i] = CornerPosition(ChangeVector3(ChangeSelfVec3(info.MoveOffset) + worldTransform_.translation_), static_cast<Corner>(i));
	}
}

void Player::IsHitCeiling(const CollisionMapInfo& info) {
	if (info.isCeilingHit) {
		DebugText::GetInstance()->ConsolePrintf("hit ceiling\n");
		velocity_.y = 0.0f;
	}
	}

SelfVec3 Player::CornerPosition(const Vector3& center, Corner corner) {
	SelfVec3 offsetTable[kNumCorner] = {
	    {+kWidth / 2.0f, -kHeight / 2.0f, 0.0f},
	    {-kWidth / 2.0f, -kHeight / 2.0f, 0.0f},
	    {+kWidth / 2.0f, +kHeight / 2.0f, 0.0f},
	    {-kWidth / 2.0f, +kHeight / 2.0f, 0.0f},
	};

	return ChangeSelfVec3(center) + offsetTable[static_cast<uint32_t>(corner)];
}