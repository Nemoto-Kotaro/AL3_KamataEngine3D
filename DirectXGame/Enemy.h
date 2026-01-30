#pragma once
#include "KamataEngine.h"
#include "Character.h"

using namespace KamataEngine;

class Enemy {
private:
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::Camera* camera_ = nullptr;


public:
	void Initialize(Model* model, Camera* camera, const Vector3& position);
	void Update();
	void Draw();
};
