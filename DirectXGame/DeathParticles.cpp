#include "DeathParticles.h"
#include "Matrix.h"
#include "mathTypes.h"
#include "WorldTransform.h"
#include <algorithm>
#include <cassert>
#include <numbers>

using namespace KamataEngine;

void DeathParticles::Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& position) {
	assert(model);
	model_ = model;

	for (WorldTransform& worldTransform : worldTransforms_) {
		worldTransform.Initialize();
		worldTransform.translation_ = position;
	}

	objectColor_.Initialize();
	color_ = {1.0f, 1.0f, 1.0f, 1.0f};
	camera_ = camera;
}

void DeathParticles::Update() {
	if (isFinished_) {
		return;
	}

	for (uint32_t i = 0; i < 8; i++) {
		SelfVec3 velocity = {kSpeed, 0.0f, 0.0f};
		float angle = kAngleUnit * i;
		Matrix4x4 matrixRotation = MakeRotatedZMatrix(angle);
		velocity = TransformCoord(velocity, matrixRotation);
		worldTransforms_[i].translation_ = ChangeVector3(velocity + ChangeSelfVec3(worldTransforms_[i].translation_));
	}

	counter_ += 1.0f / 60.0f;
	if (counter_ >= kDuration) {
		counter_ = kDuration;
		isFinished_ = true;
	}

	color_.w = std::clamp(1.0f - Ratio(counter_, 0.0f, kDuration), 0.0f, 1.0f);
	objectColor_.SetColor(ChangeVector4( color_));

	for (WorldTransform& worldTransform : worldTransforms_) {
		WorldTransformUpdate(worldTransform);
	}
}

void DeathParticles::Draw() {
	if (isFinished_) {
		return;
	}

	for (WorldTransform& worldTransform : worldTransforms_) {
		model_->Draw(worldTransform, *camera_,&objectColor_);
	}
}
