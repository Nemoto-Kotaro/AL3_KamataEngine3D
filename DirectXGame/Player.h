#pragma once
#include "KamataEngine.h"
#include "SelfVector.h"

enum class LRDirection {
	kLeft,
	kRight
};

class Player {
private:
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::WorldTransform worldTransform_;

	KamataEngine::Camera* camera_ = nullptr;

	//移動
	static inline const float kAcceleration = 0.006f;
	static inline const float kAttenuation = 0.07f;
	static inline const float kLimitRunSpeed = 0.5f;
	SelfVec3 velocity_ = {};

	//回転
	LRDirection lrDirection_ = LRDirection::kRight;
	float turnFirstRotationY_ = 0.0f;
	float turnTimer_ = 0.0f;

	static inline const float kTimerTurn = 0.3f;

	//ジャンプ
	bool onGround_ = true;
	static inline const float kGravityAcceleration = 0.025f;
	static inline const float kLimitFallSpeed = 0.4f;
	static inline const float kJumpAcceleration = 0.38f;

public:
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& position);
	void Update();
	void Draw();

	KamataEngine::WorldTransform& GetWorldTransform() { return worldTransform_; };
	const SelfVec3& GetVelocity() const { return velocity_; };
};
