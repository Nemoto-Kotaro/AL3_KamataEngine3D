#include "Player.h"
#include "WorldTransform.h"
#include <cassert>

using namespace KamataEngine;


void Player::Initialize(KamataEngine::Model* model ,KamataEngine::Camera* camera) {
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_.x = 1.0f;
	worldTransform_.translation_.y = 0.5f;

	camera_ = camera;
}

void Player::Update() { WorldTransformUpdate(worldTransform_); }

void Player::Draw() {
	model_->Draw(worldTransform_, *camera_);
}