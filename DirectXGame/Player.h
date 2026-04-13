#pragma once
#include "AABB.h"
#include "Character.h"
#include "KamataEngine.h"
#include "SelfVector.h"
class Enemy;

// 前方宣言
class MapChipField;
namespace MapChip {
struct IndexSet;
}

struct CollisionMapInfo {
	bool isCeilingHit = false;
	bool isGroundHit = false;
	bool isWallHit = false;
	NemotoLibrary::SelfVec3 MoveOffset;
};

enum Corner {
	kRightBottom,
	kLeftBottom,
	kRightTop,
	kLeftTop,

	kNumCorner
};

class Player {
public:
	enum class RectSide {
		kTop,
		kBottom,
		kRight,
		kLeft,

		kDirCount
	};

	enum class Behavior { kRoot, kAttack, kUnknown };

	enum class AttackPhase { kCharge, kDash, kRecovery };

private:
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::WorldTransform worldTransform_;

	// カメラ
	KamataEngine::Camera* camera_ = nullptr;

	// デスフラグ
	bool isDead_ = false;

	// 当たり判定
	MapChipField* mapChipField_ = nullptr;
	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;
	static inline const float kBlank = 0.00001f;

	// 振るまい
	Behavior behavior_ = Behavior::kRoot;
	Behavior behaviorRequest_ = Behavior::kUnknown;

	// 移動
	static inline const float kAcceleration = 0.006f;
	static inline const float kAttenuation = 0.07f;
	static inline const float kLimitRunSpeed = 0.3f;
	NemotoLibrary::SelfVec3 velocity_ = {};

	// 回転
	LRDirection lrDirection_ = LRDirection::kRight;
	float turnFirstRotationY_ = 0.0f;
	float turnTimer_ = 0.0f;

	static inline const float kTimerTurn = 0.3f;

	// ジャンプ
	bool onGround_ = true;
	static inline const float kGravityAcceleration = 0.025f;
	static inline const float kLimitFallSpeed = 0.4f;
	static inline const float kJumpAcceleration = 0.40f;

	// 地形ヒットの減衰
	static inline const float kAttenuationLanding = 0.03f;
	static inline const float kAttenuationWall = 0.03f;

	// 攻撃行動
	AttackPhase attackPhase_;
	float attackCounter_ = 0.0f;

	//攻撃の動作時間
	static inline const float attackChargeDuration = 0.02f;
	static inline const float attackDashDuration = 0.3f;
	static inline const float attackRecoveryDuration = 0.04f;

	//攻撃エフェクト
	KamataEngine::Model* modelAttack_ = nullptr;
	KamataEngine::WorldTransform worldTransformAttack_;



	NemotoLibrary::SelfVec3 kAttackVelocity = {0.35f, 0.0f, 0.0f};

	NemotoLibrary::SelfVec3 CornerPosition(const NemotoLibrary::SelfVec3& position, Corner corner);

	void BehaviorRootInitialize();
	void BehaviorRootUpdate();

	void BehaviorAttackInitialize();
	void BehaviorAttackUpdate();

	void MoveInPut();
	void MapCollision(CollisionMapInfo& info);
	void MapCollisionTop(CollisionMapInfo& info);
	void MapCollisionBottom(CollisionMapInfo& info);
	void MapCollisionRight(CollisionMapInfo& info);
	void MapCollisionLeft(CollisionMapInfo& info);

	bool IsMapBlockEdgeHit(CollisionMapInfo& info, RectSide dir, MapChip::IndexSet& indexSet);

	void IsHitCeiling(const CollisionMapInfo& info);
	void IsHitGround(const CollisionMapInfo& info);
	void IsHitWall(const CollisionMapInfo& info);

public:
	void Initialize(KamataEngine::Model* model, KamataEngine::Model* modelAttack, KamataEngine::Camera* camera, const NemotoLibrary::SelfVec3& position);
	void Update();
	void UpdateMatrix();
	void Draw();

	void OnCollision(const Enemy* enemy);

	// ゲッタセッタ系
	NemotoLibrary::SelfVec3 GetWorldPosition() const;
	NemotoLibrary::AABB GetAABB();

	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; };
	KamataEngine::WorldTransform& GetWorldTransform() { return worldTransform_; };
	const NemotoLibrary::SelfVec3& GetVelocity() const { return velocity_; };
	bool IsDead() const { return isDead_; };
	bool IsAttack() const;
};
