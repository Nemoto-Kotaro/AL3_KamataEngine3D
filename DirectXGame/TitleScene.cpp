#include "TitleScene.h"
#include "easing.h"
#include "mathTypes.h"
#include <cmath>
#include <numbers>

#ifdef _DEBUG
#include "imgui.h"
#endif // _DEBUG

using namespace KamataEngine;
using namespace NemotoLibrary;

TitleScene::TitleScene() {}

TitleScene::~TitleScene() {
	delete fade_;
	delete playerModel_;
	delete titleModel_;
}

void TitleScene::Initialize() {
	camera_.Initialize();
	camera_.translation_ = {0.0f,0.0f,-7.0f};

	//フェード初期化
	fade_ = new Fade();
	fade_->Initialize();
	fade_->Start(Fade::Status::FadeIn, fadeInDuration_);
	phase_ = Phase::kFadeIn;

	//プレイヤー初期化
	playerModel_ = Model::CreateFromOBJ("Player", true);
	playerWorldTransform_.Initialize();
	playerWorldTransform_.translation_ = {0.0f, -1.2f, 0.0f};
	playerWorldTransform_.rotation_ = {0.0f, 6.0f, 0.0f};

	//タイトル文字初期化
	titleModel_ = Model::CreateFromOBJ("TitleFont", true);
	titleWorldTransform_.Initialize();
	titleWorldTransform_.translation_ = {0.0f, 1.0f, 0.0f};
	swayTimer = 0.0f;
}

void TitleScene::Update() {

	switch (phase_) {
	case TitleScene::Phase::kFadeIn:
		if (fade_->IsFinished()) {
			phase_ = Phase::kMain;
		}

		break;
	case TitleScene::Phase::kMain:
		if (Input::GetInstance()->PushKey(DIK_SPACE)) {
			fade_->Start(Fade::Status::FadeOut, fadeOutDuration_);
			phase_ = Phase::kFadeOut;
		}

		break;
	case TitleScene::Phase::kFadeOut:
		if (fade_->IsFinished()) {
			finished_ = true;
		}

		break;
	default:
		break;
	}

	
	
	// フェード処理
	fade_->Update();







	//タイトルの周期運動
	swayTimer += 1.0f / 60.0f;

	float t = std::fmod(swayTimer, swayDuration * 2.0f) / swayDuration;
	if (t > 1.0f) {
		t = 2.0f - t;
	}

	float titleSwayPosY = Lerp(1.1f, 1.3f, Ease::InQuad(t));
	titleWorldTransform_.translation_.y = titleSwayPosY;

	WorldTransformUpdate(playerWorldTransform_);
	WorldTransformUpdate(titleWorldTransform_);


	camera_.UpdateMatrix();
}

void TitleScene::Draw() {
	Model::PreDraw();




	//モデル描画
	playerModel_->Draw(playerWorldTransform_, camera_);
	titleModel_->Draw(titleWorldTransform_, camera_);

	Model::PostDraw();

	switch (phase_) {
	case TitleScene::Phase::kFadeIn:
	case TitleScene::Phase::kFadeOut:
		// フェード描画
		fade_->Draw();
		break;
	default:
		break;
	}
}