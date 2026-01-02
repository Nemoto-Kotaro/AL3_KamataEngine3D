#include "GameScene.h"
#include "Matrix.h"

using namespace KamataEngine;

GameScene::GameScene() {}

GameScene::~GameScene() {
	//プレイヤー	
	delete playerModel_;
	delete player_;

	//ブロック
	delete mapChipField_;
	delete blockModel_;
	for (std::vector<WorldTransform*>& worldTransFormBlockLine : worldTransFormBlocks_) {
		for (WorldTransform* worldTransFormBlock : worldTransFormBlockLine) {
			delete worldTransFormBlock;
		}
	}

	worldTransFormBlocks_.clear();

	//天球
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

	mapChipField_ = new MapChipField;
	mapChipField_->LoadMapChipCsv("Resources/mapData.csv");
	GenerateBlocks();


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




void GameScene::GenerateBlocks() {

	uint32_t kNumBlockVertical = mapChipField_->GetNumBlockVertical();
	uint32_t kNumBlockHorizontal = mapChipField_->GetNumBlockHorizontal();

	worldTransFormBlocks_.resize(kNumBlockVertical);
	for (uint32_t i = 0; i < kNumBlockVertical; i++) {
		worldTransFormBlocks_[i].resize(kNumBlockHorizontal);
	}

	for (uint32_t i = 0; i < kNumBlockVertical; i++) {
		for (uint32_t j = 0; j < kNumBlockHorizontal; j++) {
			if (mapChipField_->GetMapChipTypeByIndex(j,i) == MapChipType::kBlock) {
				WorldTransform * worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransFormBlocks_[i][j] = worldTransform;
				worldTransFormBlocks_[i][j]->translation_ = mapChipField_->GetMapChipPositionByIndex(j,i);
			}
		}
	}
}