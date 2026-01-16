#define NOMINMAX
#include "CameraController.h"
#include "Player.h"
#include <algorithm>

using namespace KamataEngine;

void CameraController::Initialize(Camera* camera) { camera_ = camera; }

void CameraController::Update() {
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();
	SelfVec3 targetVelocity = target_->GetVelocity() * kVelocityBias;
	targetTransform = ChangeVector3(ChangeSelfVec3(targetWorldTransform.translation_) + targetOffset_ + targetVelocity);
	camera_->translation_ = Lerp(camera_->translation_, targetTransform, kInterpolationRate);

	camera_->translation_.x = std::clamp(camera_->translation_.x, targetWorldTransform.translation_.x + margin.left, targetWorldTransform.translation_.x + margin.right);
	camera_->translation_.y = std::clamp(camera_->translation_.y, targetWorldTransform.translation_.y + margin.bottom, targetWorldTransform.translation_.y + margin.top);

	camera_->translation_.x = std::clamp(camera_->translation_.x, movableArea_.left, movableArea_.right);
	camera_->translation_.y = std::clamp(camera_->translation_.y, movableArea_.bottom, movableArea_.top);

	camera_->UpdateMatrix();
}

void CameraController::Reset() {
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();
	camera_->translation_ =ChangeVector3(ChangeSelfVec3(targetWorldTransform.translation_) + targetOffset_);
}
