#pragma once
#include "Character.h"
#include "SelfVector.h"
#include "KamataEngine.h"
#include "AABB.h"
class Player;
class GameScene;


using namespace KamataEngine;

class Enemy {
public:
	enum class Behavior { kRoot, kDeath, kUnknown };

private:
	// 振るまい
	Behavior behavior_ = Behavior::kRoot;
	Behavior behaviorRequest_ = Behavior::kUnknown;

	// デスフラグ
	bool isDead_ = false;

	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::Camera* camera_ = nullptr;
	GameScene* gameScene_ = nullptr;

	//当たり判定
	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;
	bool isCollisionDisabled_ = false;
	

	//移動
	static inline const float kWalkSpeed = 0.02f;
	NemotoLibrary::SelfVec3 velocity_;

	static inline const float kWalkMotionAngleStart = 0.0f;
	static inline const float kWalkMotionAngleEnd = 20.0f;
	static inline const float kWalkMotionTime = 1.0f;

	float walkTimer_ = 0.0f;

	//デス演出
	float deathCounter_ = 0.0f;
	static inline const float deathDuration_ = 1.0f;




	void BehaviorRootInitialize();
	void BehaviorRootUpdate();

	void BehaviorDeathInitialize();
	void BehaviorDeathUpdate();

public:
	void Initialize(Model* model, Camera* camera,GameScene* gameScene ,const NemotoLibrary::SelfVec3& position);
	void Update();
	void UpdateMatrix();
	void Draw();

	void OnCollision(const Player* player);

	NemotoLibrary::SelfVec3 GetWorldPosition();
	NemotoLibrary::AABB GetAABB();
	bool IsDead() const { return isDead_; };
	bool IsCollisionDisabled() const { return isCollisionDisabled_; };
};
