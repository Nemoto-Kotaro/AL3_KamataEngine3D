#pragma once
#include <vector>
#include "KamataEngine.h"
#include "SelfVector.h"
#include "WorldTransform.h"
#include "Fade.h"

class TitleScene {
private:
	enum class Phase {
		kFadeIn,
		kMain,
		kFadeOut,
	};


	bool finished_ = false;
	Phase phase_ = Phase::kFadeIn;


	KamataEngine::Camera camera_;

	//フェード
	Fade* fade_ = nullptr;
	const float fadeInDuration_ = 2.0f;
	const float fadeOutDuration_ = 2.0f;

	// プレイヤー
	KamataEngine::Model* playerModel_ = nullptr;
	KamataEngine::WorldTransform playerWorldTransform_;

	//　タイトル文字
	KamataEngine::Model* titleModel_ = nullptr;
	KamataEngine::WorldTransform titleWorldTransform_;

	float swayTimer = 0.0f;
	static inline float swayDuration = 1.0f; //往復間隔
	

public:
	TitleScene();
	~TitleScene();

	void Initialize();
	void Update();
	void Draw();

	bool IsFinished() const { return finished_; };
};
