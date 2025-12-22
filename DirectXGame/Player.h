#pragma once
#include "KamataEngine.h"


class Player {
private:
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::WorldTransform worldTransform_;
	int32_t textureHandle_ = 0;

	KamataEngine::Camera* camera_ = nullptr;


public:


	void Initialize(KamataEngine::Model* model, uint32_t textureHandle, KamataEngine::Camera* camera);
	void Update();
	void Draw();
};
