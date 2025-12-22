#include "GameScene.h"
#include "Matrix.h"

using namespace KamataEngine;

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete playerModel_;
	delete player_;

	delete blockModel_;
	for (std::vector<WorldTransform*>& worldTransFormBlockLine : worldTransFormBlocks_) {
		for (WorldTransform* worldTransFormBlock : worldTransFormBlockLine) {
			delete worldTransFormBlock;
		}
	}

	worldTransFormBlocks_.clear();

	
	delete debugCamera_;
}

void GameScene::Initialize() {


	camera_.Initialize();

	// プレイヤー
	playerTextureHandle_ = TextureManager::Load("./Resources/uvChecker.png");
	playerModel_ = Model::Create();
	player_ = new Player();
	player_->Initialize(playerModel_, playerTextureHandle_, &camera_);

	// ブロック
	blockTextureHandle_ = TextureManager::Load("./Resources/cube/cube.jpg");
	blockModel_ = Model::Create();
	const uint32_t kNumBlockVertical = 10;
	const uint32_t kNumBlockHorizontal = 20;
	const float kBlockWight = 2.0f;
	const float kBlockHeight = 2.0f;
	worldTransFormBlocks_.resize(kNumBlockVertical);
	for (uint32_t i = 0; i < kNumBlockVertical; i++) {
		worldTransFormBlocks_[i].resize(kNumBlockHorizontal);
	}

	for (uint32_t i = 0; i < kNumBlockVertical; i++) {
		for (uint32_t j = 0; j < kNumBlockHorizontal; j++) {
			if ((i % 2 == 0 && j % 2 == 0) || (i % 2 == 1 && j % 2 == 1)) {
				worldTransFormBlocks_[i][j] = new WorldTransform();
				worldTransFormBlocks_[i][j]->Initialize();
				worldTransFormBlocks_[i][j]->translation_.x = kBlockWight * j;
				worldTransFormBlocks_[i][j]->translation_.y = kBlockHeight * i;
			}
		}
	}

	
	// デバック
	debugCamera_ = new DebugCamera(1280, 720);
}

void GameScene::Update() {
	// プレイヤー
	player_->Update();

	// ブロック
	for (std::vector<WorldTransform*>& worldTransFormBlockLine : worldTransFormBlocks_) {
		for (WorldTransform* worldTransFormBlock : worldTransFormBlockLine) {
			if (!worldTransFormBlock) {
				continue;
			}

			worldTransFormBlock->matWorld_ = MakeAffineMatrix(worldTransFormBlock->scale_, worldTransFormBlock->rotation_, worldTransFormBlock->translation_);
			worldTransFormBlock->TransferMatrix();
		}
	}

	//デバック
	

	#ifdef _DEBUG
	if (Input::GetInstance()->TriggerKey(DIK_RETURN)) {
		isDebugCameraActive_ = !isDebugCameraActive_;
	}
#endif // _DEBUG

	if (isDebugCameraActive_) {
		debugCamera_->Update();
		camera_.matView = debugCamera_->GetCamera().matView;
		camera_.matProjection = debugCamera_->GetCamera().matProjection;
		camera_.TransferMatrix();
	} else {
		camera_.UpdateMatrix();
	}
}

void GameScene::Draw() {
	// プレイヤー
	player_->Draw();

	// ブロック

	Model::PreDraw();
	for (std::vector<WorldTransform*>& worldTransFormBlockLine : worldTransFormBlocks_) {
		for (WorldTransform* worldTransFormBlock : worldTransFormBlockLine) {
			if (!worldTransFormBlock) {
				continue;
			}

			blockModel_->Draw(*worldTransFormBlock, camera_, blockTextureHandle_);
		}
	}

	Model::PostDraw();
}
