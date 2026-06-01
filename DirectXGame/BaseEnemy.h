#pragma once
#include "AABB.h"
#include "Character.h"
#include "KamataEngine.h"
#include "SelfVector.h"
class Player;
class GameScene;

using namespace KamataEngine;

class BaseEnemy {
public:

	// デスフラグ
	bool isDead_ = false;

	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::Camera* camera_ = nullptr;
	GameScene* gameScene_ = nullptr;

	bool isCollisionDisabled_ = false;

	virtual void BehaviorRootInitialize() = 0;
	virtual void BehaviorRootUpdate() = 0;

	virtual void BehaviorDeathInitialize() = 0;
	virtual void BehaviorDeathUpdate() = 0;
	virtual NemotoLibrary::SelfVec2 GetSize() = 0;

public:
	virtual ~BaseEnemy() = default;
	virtual void Initialize(Model* model, Camera* camera, GameScene* gameScene, const NemotoLibrary::SelfVec3& position) = 0;
	virtual void Update() = 0;
	void UpdateMatrix();
	void Draw();

	virtual void OnCollision(Player* player) = 0;
	bool IsDead() const { return isDead_; };
	bool IsCollisionDisabled() const { return isCollisionDisabled_; };

	NemotoLibrary::SelfVec3 GetWorldPosition();
	NemotoLibrary::AABB GetAABB();
};
