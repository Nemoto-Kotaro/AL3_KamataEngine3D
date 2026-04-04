#pragma once
#include "Character.h"
#include "SelfVector.h"
#include "KamataEngine.h"
#include "AABB.h"
class Player;


using namespace KamataEngine;

class Enemy {
private:
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::Camera* camera_ = nullptr;

	//当たり判定
	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;


	//移動
	static inline const float kWalkSpeed = 0.02f;
	NemotoLibrary::SelfVec3 velocity_;

	static inline const float kWalkMotionAngleStart = 0.0f;
	static inline const float kWalkMotionAngleEnd = 20.0f;
	static inline const float kWalkMotionTime = 1.0f;

	float walkTimer_ = 0.0f;

public:
	void Initialize(Model* model, Camera* camera, const NemotoLibrary::SelfVec3& position);
	void Update();
	void Draw();

	void OnCollision(const Player* player);

	NemotoLibrary::SelfVec3 GetWorldPosition();
	NemotoLibrary::AABB GetAABB();
};
