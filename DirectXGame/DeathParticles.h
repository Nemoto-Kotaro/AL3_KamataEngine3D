#pragma once
#include "KamataEngine.h"
#include "SelfVector.h"
#include <array>
#include <numbers>

class DeathParticles {
private:
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::Camera* camera_ = nullptr;

	static inline const uint32_t kNumParticles = 8;
	std::array<KamataEngine::WorldTransform, kNumParticles> worldTransforms_;

	static inline const float kDuration = 1.0f;
	static inline const float kSpeed = 0.07f;
	static inline const float kAngleUnit = 2.0f * std::numbers::pi_v<float> / 8.0f;

	bool isFinished_ = false;
	float counter_ = 0.0f;

	KamataEngine::ObjectColor objectColor_;
	NemotoLibrary::SelfVec4 color_;

public:
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const NemotoLibrary::SelfVec3& position);
	void Update();
	void UpdateMatrix();
	void Draw();

	bool IsFinished() const { return isFinished_; };
};
