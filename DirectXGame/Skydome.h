#pragma once
#include "KamataEngine.h"


class Skydome {
private:
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Model* model_ = nullptr;

	KamataEngine::Camera* camera_ = nullptr;

public:
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera);
	void Update();
	void UpdateMatrix();
	void Draw();

};
