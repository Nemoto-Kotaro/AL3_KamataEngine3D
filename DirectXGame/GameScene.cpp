#include "GameScene.h"
#include "Matrix.h"

using namespace KamataEngine;

GameScene::GameScene() {}

GameScene::~GameScene() {
	// プレイヤー
	delete playerModel_;
	delete player_;

	delete enemyModel_;
	for (Enemy* enemies : enemies_) {
		delete enemies;
	}

	// ブロック
	delete mapChipField_;
	delete blockModel_;
	for (std::vector<WorldTransform*>& worldTransFormBlockLine : worldTransFormBlocks_) {
		for (WorldTransform* worldTransFormBlock : worldTransFormBlockLine) {
			delete worldTransFormBlock;
		}
	}

	worldTransFormBlocks_.clear();

	// 天球
	delete skyDomeModel_;
	delete skyDome_;

	// カメラ
	delete camaraController_;

	delete debugCamera_;
}

void GameScene::Initialize() {

	// カメラ
	camera_.farZ = 2000.0f;
	camera_.Initialize();

	// ブロック
	blockModel_ = Model::CreateFromOBJ("Block_Crate", true);

	mapChipField_ = new MapChipField;
	mapChipField_->LoadMapChipCsv("Resources/mapData.csv");
	GenerateBlocks();

	// プレイヤー
	Vector3 playerPosition = mapChipField_->GetMapChipPositionByIndex(3, 18);
	playerModel_ = Model::CreateFromOBJ("Player", true);
	player_ = new Player();
	player_->Initialize(playerModel_, &camera_, playerPosition);

	player_->SetMapChipField(mapChipField_);

	// エネミー
	enemyModel_ = Model::CreateFromOBJ("Enemy", true);
	for (int i = 0; i < 3; i++) {
		Enemy* newEnemy = new Enemy();
		Vector3 enemyPosition = mapChipField_->GetMapChipPositionByIndex(10 + i, 18);
		newEnemy->Initialize(enemyModel_, &camera_, enemyPosition);

		enemies_.push_back(newEnemy);
	}

	// 天球
	skyDomeModel_ = Model::CreateFromOBJ("CelestialSphere", true);
	skyDome_ = new Skydome();
	skyDome_->Initialize(skyDomeModel_, &camera_);

	// カメラコントローラ
	camaraController_ = new CameraController();
	camaraController_->Initialize(&camera_);
	camaraController_->SetTarget(player_);
	camaraController_->Reset();

	// デバック
	debugCamera_ = new DebugCamera(1280, 720);
}

void GameScene::Update() {
	// プレイヤー
	player_->Update();

	// エネミー

	for (Enemy* enemies : enemies_) {
		if (enemies != nullptr) {
			enemies->Update();
		}
	}

	// ブロック
	for (std::vector<WorldTransform*>& worldTransFormBlockLine : worldTransFormBlocks_) {
		for (WorldTransform* worldTransFormBlock : worldTransFormBlockLine) {
			if (!worldTransFormBlock) {
				continue;
			}

			WorldTransformUpdate(*worldTransFormBlock);
		}
	}

	// 天球
	skyDome_->Update();

// デバック
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
		camaraController_->Update();
	}



	//当たり判定をおこなう
	CheckAllCollisions();



}

void GameScene::Draw() {
	Model::PreDraw();
	// 天球
	skyDome_->Draw();

	// プレイヤー
	player_->Draw();

	// エネミー

	for (Enemy* enemies : enemies_) {
		if (enemies != nullptr) {
			enemies->Draw();
		}
	}

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
			if (mapChipField_->GetMapChipTypeByIndex(j, i) == MapChipType::kBlock) {
				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransFormBlocks_[i][j] = worldTransform;
				worldTransFormBlocks_[i][j]->translation_ = mapChipField_->GetMapChipPositionByIndex(j, i);
			}
		}
	}
}


void GameScene::CheckAllCollisions() {
#pragma region playerToEnemy
	AABB aabb1 = player_->GetAABB();
	AABB aabb2;
	for (Enemy* enemy : enemies_) {
		aabb2 = enemy->GetAABB();
		if (AABBCollision(aabb1, aabb2)) {
			player_->OnCollision(enemy);
			enemy->OnCollision(player_);
		}
	}

#pragma endregion
}