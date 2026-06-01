#include "GuardEffect.h"
#include "Random.h"
#include "WorldTransform.h"
#include "easing.h"
#include "mathTypes.h"
#include <cassert>
#include <numbers>

KamataEngine::Model* GuardEffect::model_ = nullptr;

using namespace KamataEngine;
using namespace NemotoLibrary;

void GuardEffect::Initialize(SelfVec3& position) {
	circleWorldTransform_.translation_ = ToKamataEngine(position);
	circleWorldTransform_.Initialize();

	for (WorldTransform& worldTransform : ellipseWorldTransforms_) {
		worldTransform.scale_ = {0.5f, 0.1f, 1.0f};
		float randomAngle = Random::Range(0.0f, (std::numbers::pi_v<float> * 2.0f));
		worldTransform.rotation_ = {0.0f, 0.0f, randomAngle};
		worldTransform.translation_ = ToKamataEngine(position);
		worldTransform.Initialize();
	}

	objectColor_.Initialize();
	color_ = {1.0f, 1.0f, 1.0f, 1.0f};
}

void GuardEffect::Update() {
	counter_ += 1.0f / 60.0f;

	switch (state_) {
	case State::kSpread: {

		float easeT = Ease::InSine(counter_ / spreadDuration_);
		circleWorldTransform_.scale_.x = Lerp(0.25f, 1.0f, easeT);
		circleWorldTransform_.scale_.y = Lerp(0.25f, 1.0f, easeT);
		;

		for (WorldTransform& worldTransform : ellipseWorldTransforms_) {
			worldTransform.scale_.x = Lerp(0.5f, 2.0f, easeT);
			;
		}

		if (counter_ >= spreadDuration_) {
			counter_ = 0.0f;
			state_ = State::kFadeOut;
		}

		break;
	}
	case State::kFadeOut: {

		float easeT = Ease::InSine(counter_ / spreadDuration_);
		color_.w = std::clamp(Lerp(1.0f, 0.0f, easeT), 0.0f, 1.0f);
		objectColor_.SetColor(ToKamataEngine(color_));

		if (counter_ >= fadeDuration_) {
			state_ = State::kFinished;
		}

		break;
	}
	default:
		break;
	}
}

void GuardEffect::UpdateMatrix() {
	WorldTransformUpdate(circleWorldTransform_);
	for (WorldTransform& worldTransform : ellipseWorldTransforms_) {
		WorldTransformUpdate(worldTransform);
	}
}

void GuardEffect::Draw() {
	model_->Draw(circleWorldTransform_, *camera_, &objectColor_);
	for (WorldTransform& worldTransform : ellipseWorldTransforms_) {
		model_->Draw(worldTransform, *camera_, &objectColor_);
	}
}

GuardEffect* GuardEffect::Create(SelfVec3& position) {
	GuardEffect* instance = new GuardEffect();
	assert(instance);
	instance->Initialize(position);
	return instance;
}