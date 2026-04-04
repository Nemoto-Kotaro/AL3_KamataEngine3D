#pragma once
#include <vector>
#include "KamataEngine.h"
#include "SelfVector.h"
#include "WorldTransform.h"

class TitleScene {
private:

	bool finished_ = false;

	KamataEngine::Camera camera_;


	// プレイヤー
	KamataEngine::Model* playerModel_ = nullptr;
	KamataEngine::WorldTransform playerWorldTransform_;

	//　タイトル文字
	KamataEngine::Model* titleModel_ = nullptr;
	KamataEngine::WorldTransform titleWorldTransform_;

	float swayTimer = 0.0f;
	static inline const float swayDuration = 1.0f; //往復間隔
	

public:
	TitleScene();
	~TitleScene();

	void Initialize();
	void Update();
	void Draw();

	bool IsFinished() const { return finished_; };
};
