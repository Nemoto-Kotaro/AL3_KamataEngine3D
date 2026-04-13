#pragma once
#include "KamataEngine.h"
#include "SelfVector.h"
#include <array>

class HitEffect {
public:
	enum class State { kSpread, kFadeOut, kFinished };

private:
	State state_ = State::kSpread;

	static KamataEngine::Model* model_;
	static KamataEngine::Camera* camera_;
	//中心のエフェクト
	KamataEngine::WorldTransform circleWorldTransform_;
	//尖ったエフェクト
	std::array<KamataEngine::WorldTransform, 2> ellipseWorldTransforms_;

	//
	float counter_ = 0.0f;
	static inline const float spreadDuration_ = 0.3f;
	static inline const float fadeDuration_ = 0.2f;

	KamataEngine::ObjectColor objectColor_;
	NemotoLibrary::SelfVec4 color_;

public:
	
	static HitEffect* Create(NemotoLibrary::SelfVec3& position);

	void Initialize(NemotoLibrary::SelfVec3& position);
	void Update();
	void UpdateMatrix();
	void Draw();

	//セッターゲッター
	static void SetModel(KamataEngine::Model* model) { model_ = model; };
	static void SetCamera(KamataEngine::Camera* camera) { camera_ = camera; };
	bool IsDead() const { return state_ == State::kFinished; };
};
