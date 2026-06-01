#pragma once
#include "AABB.h"
#include "BaseEnemy.h"
#include "Character.h"
#include "KamataEngine.h"
#include "SelfVector.h"
class Player;
class GameScene;

using namespace KamataEngine;

class ShieldEnemy : public BaseEnemy {
private:
	enum class Behavior { kRoot, kDeath, kUnknown };
	// 振るまい
	Behavior behavior_ = Behavior::kRoot;
	Behavior behaviorRequest_ = Behavior::kUnknown;

private:
	// 当たり判定
	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;
	bool isCollisionDisabled_ = false;

	// 移動
	static inline const float kWalkSpeed = 0.02f;
	NemotoLibrary::SelfVec3 velocity_;

	float walkTimer_ = 0.0f;

	// デス演出
	float deathCounter_ = 0.0f;
	static inline const float deathDuration_ = 1.0f;

	static inline const float kWalkMotionAngleStart = 45.0f;
	static inline const float kWalkMotionAngleEnd = 90.0f;
	static inline const float kWalkMotionTime = 1.0f;

	
	LRDirection lrDirection_ = LRDirection::kLeft;

	void BehaviorRootInitialize() override;
	void BehaviorRootUpdate() override;

	void BehaviorDeathInitialize() override;
	void BehaviorDeathUpdate() override;

public:
	void Initialize(Model* model, Camera* camera, GameScene* gameScene, const NemotoLibrary::SelfVec3& position) override;
	void Update() override;
	void OnCollision(Player* player) override;

	NemotoLibrary::SelfVec2 GetSize() { return NemotoLibrary::SelfVec2(kWidth, kHeight); };
};
