#include "GameScene.h"

using namespace KamataEngine;

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete sprite_;
	delete model_;
	delete debugCamera_;
}

void GameScene::Initialize() {
	textureHandle_ = TextureManager::Load("./Resources/sample.png");
	sprite_ = Sprite::Create(textureHandle_, {100, 50});
	model_ = Model::Create();
	worldTransform_.Initialize();
	camera_.Initialize();
	soundDataHandle_ = Audio::GetInstance()->LoadWave("./Resources/fanfare.wav");
	voiceHandle_ = Audio::GetInstance()->PlayWave(soundDataHandle_, true);
	debugCamera_ = new DebugCamera(1280, 720);
	PrimitiveDrawer::GetInstance()->SetCamera(&camera_);
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetCamera(&debugCamera_->GetCamera());
}

void GameScene::Update() {
	// 画像
	Vector2 position = sprite_->GetPosition();
	position.x += 2.0f;
	position.y += 1.0f;
	sprite_->SetPosition(position);

	// 音声
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		Audio::GetInstance()->StopWave(voiceHandle_);
	}


	//カメラ
	debugCamera_->Update();

#ifdef _DEBUG
	// ImGui
	ImGui::ShowDemoWindow();

	ImGui::Begin("Debug1");
	ImGui::Text("Nemoto kotarou %d.%d.%d", 2050, 12, 31);
	ImGui::InputFloat3("inputFloat3", inputFloat3);
	ImGui::SliderFloat3("SliderFloat3", inputFloat3, 0.0f, 1.0f);
	ImGui::End();
#endif // _DEBUG
}

void GameScene::Draw() {
	/*Sprite::PreDraw();
	sprite_->Draw();
	Sprite::PostDraw();*/
	Model::PreDraw();

	//model_->Draw(worldTransform_, camera_, textureHandle_);
	model_->Draw(worldTransform_, debugCamera_->GetCamera(), textureHandle_);
	Model::PostDraw();

	PrimitiveDrawer::GetInstance()->DrawLine3d({0, 0, 0}, {0, 10, 0}, {1.0f, 0.0f, 0.0f, 1.0f});
}