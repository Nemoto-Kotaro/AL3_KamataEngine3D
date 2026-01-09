#pragma once
#include "KamataEngine.h"
#include "SelfVector.h"
class MapChipField;

enum class LRDirection { kLeft, kRight };

struct CollisionMapInfo {
	bool isCeilingHit = false;
	bool isGroundHit = false;
	bool isWallHit = false;
	KamataEngine::Vector3 MoveOffset;
};

enum Corner {
	kRightBottom,
	kLeftBottom,
	kRightTop,
	kLeftTop,

	kNumCorner
};

class Player {
private:
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::WorldTransform worldTransform_;

	KamataEngine::Camera* camera_ = nullptr;

	// 当たり判定
	MapChipField* mapChipField_ = nullptr;
	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;
	static inline const float kBlank = 0.00001f;

	// 移動
	static inline const float kAcceleration = 0.006f;
	static inline const float kAttenuation = 0.07f;
	static inline const float kLimitRunSpeed = 0.5f;
	SelfVec3 velocity_ = {};

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

	SelfVec3 CornerPosition(const KamataEngine::Vector3& center, Corner corner);

	void MoveInPut();
	void MapCollision(CollisionMapInfo& info);
	void MapCollisionTop(CollisionMapInfo& info);
	void MapCollisionBottom(CollisionMapInfo& info);
	void MapCollisionRight(CollisionMapInfo& info);
	void MapCollisionLeft(CollisionMapInfo& info);

	void IsHitCeiling(const CollisionMapInfo& info);

public:
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& position);
	void Update();
	void Draw();

	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; };
	KamataEngine::WorldTransform& GetWorldTransform() { return worldTransform_; };
	const SelfVec3& GetVelocity() const { return velocity_; };
};
