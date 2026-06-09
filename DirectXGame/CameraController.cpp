#define NOMINMAX
#include "CameraController.h"
#include "Player.h"
#include <algorithm>

using namespace KamataEngine;
using namespace NemotoLibrary;

void CameraController::Initialize(Camera* camera) { camera_ = camera; }

void CameraController::Update() {
	switch (mode_) {
	case Mode::kFollow: {

		const WorldTransform& targetWorldTransform = target_->GetWorldTransform();
		SelfVec3 targetVelocity = target_->GetVelocity() * kVelocityBias;
		targetTransform = ToMyEngine(targetWorldTransform.translation_) + targetOffset_ + targetVelocity;
		camera_->translation_ = ToKamataEngine(Lerp(ToMyEngine(camera_->translation_), targetTransform, kInterpolationRate));

		camera_->translation_.x = std::clamp(camera_->translation_.x, targetWorldTransform.translation_.x + margin.left, targetWorldTransform.translation_.x + margin.right);
		camera_->translation_.y = std::clamp(camera_->translation_.y, targetWorldTransform.translation_.y + margin.bottom, targetWorldTransform.translation_.y + margin.top);

		camera_->translation_.x = std::clamp(camera_->translation_.x, movableArea_.left, movableArea_.right);
		camera_->translation_.y = std::clamp(camera_->translation_.y, movableArea_.bottom, movableArea_.top);

		camera_->UpdateMatrix();
	} break;
	case Mode::kForcedScroll: {
		const WorldTransform& targetWorldTransform = target_->GetWorldTransform();
		SelfVec3 targetVelocity = target_->GetVelocity() * kVelocityBias;
		targetTransform.y = ToMyEngine(targetWorldTransform.translation_).y + targetOffset_.y + targetVelocity.y;
		camera_->translation_.y = Lerp(ToMyEngine(camera_->translation_).y, targetTransform.y, kInterpolationRate);

		// スクロールする
		if (isScroll_) {
			camera_->translation_.x += kScrollSpeed * 1.0f / 60.0f;
		}

		camera_->translation_.y = std::clamp(camera_->translation_.y, targetWorldTransform.translation_.y + margin.bottom, targetWorldTransform.translation_.y + margin.top);

		camera_->translation_.x = std::clamp(camera_->translation_.x, movableArea_.left, movableArea_.right);
		camera_->translation_.y = std::clamp(camera_->translation_.y, movableArea_.bottom, movableArea_.top);

		float distance = target_->GetWorldTransform().translation_.z - camera_->translation_.z;
		float halfHeight = distance * std::tan(camera_->fovAngleY * 0.5f);
		float halfWidth = halfHeight * 1280.0f / 720.0f;
		//カメラの範囲をもとにプレイヤーに押し出ししてもらう。
		target_->ScrollPush(ToMyEngine(camera_->translation_), halfWidth);
		camera_->UpdateMatrix();
	} break;
	default:
		break;
	}
}

void CameraController::Reset() {
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();
	camera_->translation_ = ToKamataEngine(targetOffset_ + targetWorldTransform.translation_);
}
