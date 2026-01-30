#include "Enemy.h"
#define NOMINMAX
#include "WorldTransform.h"
#include "easing.h"
#include "mathTypes.h"
#include <algorithm>
#include <cassert>
#include <numbers>

using namespace KamataEngine;


void Enemy::Initialize(Model* model, Camera* camera, const Vector3& position) {
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.rotation_.y = std::numbers::pi_v<float> * -1.5f;

	camera_ = camera;
}

void Enemy::Update() { WorldTransformUpdate(worldTransform_); }

void Enemy::Draw() { model_->Draw(worldTransform_, *camera_); }