#include "Fade.h"
#include <algorithm>

using namespace KamataEngine;
using namespace NemotoLibrary;

Fade::Fade() {}

Fade::~Fade() {}

void Fade::Initialize() {
	fadeTextureHandle = TextureManager::Load("white1x1.png");
	sprite_ = Sprite::Create(fadeTextureHandle, {1, 1});
	sprite_->SetSize(Vector2(1280.0f, 720.0f));
	sprite_->SetColor(Vector4(0.0f, 0.0f, 0.0f, 1.0f));
}
void Fade::Update() {
	switch (status_) {
	case Fade::Status::None:
		break;
	case Fade::Status::FadeIn:
		counter_ += 1.0f / 60.0f;
		counter_ = (std::min)(counter_, duration_);

		sprite_->SetColor(Vector4(0.0f, 0.0f, 0.0f, std::clamp(1.0f - counter_ / duration_, 0.0f, 1.0f)));
		break;
	case Fade::Status::FadeOut:
		counter_ += 1.0f / 60.0f;
		counter_ = (std::min)(counter_, duration_);

		sprite_->SetColor(Vector4(0.0f, 0.0f, 0.0f, std::clamp(counter_ / duration_, 0.0f, 1.0f)));
		break;
	default:
		break;
	}
}

void Fade::Draw() {
	if (status_ == Status::None) {
		return;
	}

	Sprite::PreDraw();
	sprite_->Draw();
	Sprite::PostDraw();
}

void Fade::Start(Status status, float duration) {
	status_ = status;
	duration_ = duration;
	counter_ = 0.0f;
}

void Fade::Stop() { status_ = Status::None; }

bool Fade::IsFinished() const {
	switch (status_) {
	case Fade::Status::FadeIn:
	case Fade::Status::FadeOut:
		if (counter_ >= duration_) {
			return true;
		} else {
			return false;
		}
	}

	return true;
}