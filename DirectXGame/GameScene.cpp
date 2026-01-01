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

	delete skyDomeModel_;
	delete skyDome_;
	
	delete debugCamera_;
}

void GameScene::Initialize() {

	camera_.farZ = 2000.0f;
	camera_.Initialize();

	// プレイヤー
	playerModel_ = Model::CreateFromOBJ("Player", true);
	player_ = new Player();
	player_->Initialize(playerModel_,  &camera_);

	// ブロック
	blockModel_ = Model::CreateFromOBJ("Block_Crate", true);
	const uint32_t kNumBlockVertical = 10;
	const uint32_t kNumBlockHorizontal = 20;
	const float kBlockWight = 1.0f;
	const float kBlockHeight = 1.0f;
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

	//天球
	skyDomeModel_ = Model::CreateFromOBJ("CelestialSphere",true);
	skyDome_ = new Skydome();
	skyDome_->Initialize(skyDomeModel_, &camera_);

	
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

			WorldTransformUpdate(*worldTransFormBlock);
		}
	}

	//天球
	skyDome_->Update();



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
	Model::PreDraw();
	// 天球
	skyDome_->Draw();

	// プレイヤー
	player_->Draw();

	// ブロック
	for (std::vector<WorldTransform*>& worldTransFormBlockLine : worldTransFormBlocks_) {
		for (WorldTransform* worldTransFormBlock : worldTransFormBlockLine) {
			if (!worldTransFormBlock) {
				continue;
			}

			blockModel_->Draw(*worldTransFormBlock, camera_);
		}
	}


	Model::PostDraw();
}
