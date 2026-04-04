#pragma once
#include <vector>
#include "KamataEngine.h"

class TitleScene {
private:

	bool finished_ = false;

	KamataEngine::Camera camera_;

	// プレイヤー
	KamataEngine::Model* playerModel_ = nullptr;

	//　タイトル文字
	KamataEngine::Model* titleModel_ = nullptr;



public:
	TitleScene();
	~TitleScene();

	void Initialize();
	void Update();
	void Draw();

	bool IsFinished() const { return finished_; };
};
