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
	enum class Behavior { kRoot, kDeath, kGuard, kUnknown };
	// 振るまい
	Behavior behavior_ = Behavior::kRoot;
	Behavior behaviorRequest_ = Behavior::kUnknown;

private:
	// 当たり判定
	static inline float kWidth = 0.8f;
	static inline float kHeight = 0.8f;
	bool isCollisionDisabled_ = false;

	// 移動
	static inline float kWalkSpeed = 0.02f;
	NemotoLibrary::SelfVec3 velocity_;

	float walkTimer_ = 0.0f;

	// デス演出
	float deathCounter_ = 0.0f;
	static inline float deathDuration_ = 1.0f;

	static inline float kWalkMotionAngleStart = 45.0f;
	static inline float kWalkMotionAngleEnd = 90.0f;
	static inline float kWalkMotionTime = 1.0f;

	//ガード
	float guardCounter_ = 0.0f;
	static inline float guardDuration_ = 0.35f;


	LRDirection lrDirection_ = LRDirection::kLeft;

	void BehaviorRootInitialize();
	void BehaviorRootUpdate();

	void BehaviorDeathInitialize();
	void BehaviorDeathUpdate();

	void BehaviorGuardInitialize();
	void BehaviorGuardUpdate();

public:
	static void RegisterGlobalVariables();
	static void ApplyGlobalVariables();

	void Initialize(Model* model, Camera* camera, GameScene* gameScene, const NemotoLibrary::SelfVec3& position) override;
	void Update() override;
	void OnCollision(Player* player) override;

	NemotoLibrary::SelfVec2 GetSize() { return NemotoLibrary::SelfVec2(kWidth, kHeight); };
};
