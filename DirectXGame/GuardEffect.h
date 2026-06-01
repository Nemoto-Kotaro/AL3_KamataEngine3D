#pragma once
#include "Effect.h"

class GuardEffect : public Effect {
private:
	static KamataEngine::Model* model_;

	enum class State { kSpread, kFadeOut, kFinished };
	State state_ = State::kSpread;
	// 中心のエフェクト
	KamataEngine::WorldTransform circleWorldTransform_;

	//
	float counter_ = 0.0f;
	static inline const float spreadDuration_ = 0.1f;
	static inline const float fadeDuration_ = 0.2f;

	KamataEngine::ObjectColor objectColor_;
	NemotoLibrary::SelfVec4 color_;

public:
	// スタティックなので各々
	static GuardEffect* Create(NemotoLibrary::SelfVec3& position);
	static void SetModel(KamataEngine::Model* model) { model_ = model; };

	// こっちはオーバーロード
	void Initialize(NemotoLibrary::SelfVec3& position) override;
	void Update() override;
	void UpdateMatrix() override;
	void Draw() override;
	bool IsDead() const override { return state_ == State::kFinished; };
};
