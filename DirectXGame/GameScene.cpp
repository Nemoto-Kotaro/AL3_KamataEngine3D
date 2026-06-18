#include "GameScene.h"
#include "GuardEffect.h"
#include "HitEffect.h"
#include "SelfMatrix.h"
#include "ShieldEnemy.h"
#include "StageManager.h"

using namespace KamataEngine;
using namespace NemotoLibrary;

GameScene::GameScene() {}

GameScene::~GameScene() {
	//===フェード===
	delete fade_;

	//=====プレイヤー=====
	delete playerModel_;
	delete player_;

	//=====エネミー=====
	delete enemyModel_;
	delete shieldEnemyModel_;
	for (BaseEnemy* enemies : enemies_) {
		delete enemies;
	}

	//=====エフェクト=====
	delete hitEffectModel_;
	delete guardEffectModel_;
	for (Effect* hitEffects : hitEffects_) {
		delete hitEffects;
	}

	//=====ブロック=====
	delete mapChipField_;
	delete blockModel_;
	for (std::vector<WorldTransform*>& worldTransFormBlockLine : worldTransFormBlocks_) {
		for (WorldTransform* worldTransFormBlock : worldTransFormBlockLine) {
			delete worldTransFormBlock;
		}
	}

	worldTransFormBlocks_.clear();

	//======パーティクル======
	delete deathParticles_;

	//=====天球=====
	delete skyDomeModel_;
	delete skyDome_;

	//=====カメラ=====
	delete camaraController_;
	delete debugCamera_;
}

void GameScene::Initialize(StageManager* stageManger) {
	stageManger_ = stageManger;

	//======フェード初期化======
	fade_ = new Fade();
	fade_->Initialize();
	fade_->Start(Fade::Status::FadeIn, fadeInDuration_);
	phase_ = Phase::kFadeIn;

	//======カメラ======
	camera_.farZ = 2000.0f;
	camera_.Initialize();

	//======ブロック======
	blockModel_ = Model::CreateFromOBJ("Block_Crate", true);

	mapChipField_ = new MapChipField;
	const StageData& stageData = stageManger_->GetCurrentStageData();
	std::string stageFileNama = "Resources/fields/" + stageData.name + ".csv";

	mapChipField_->LoadMapChipCsv(stageFileNama);

	GenerateMapChips();

	//=====エフェクト=====
	hitEffectModel_ = Model::CreateFromOBJ("hitEffect", true);
	guardEffectModel_ = Model::CreateFromOBJ("GuardEffect", true);
	HitEffect::SetModel(hitEffectModel_);
	GuardEffect::SetModel(guardEffectModel_);
	Effect::SetCamera(&camera_);

	//=====パーティクル=====
	particleModel_ = Model::CreateFromOBJ("Particle", true);

	//======天球======
	skyDomeModel_ = Model::CreateFromOBJ("CelestialSphere", true);
	skyDome_ = new Skydome();
	skyDome_->Initialize(skyDomeModel_, &camera_);

	//======カメラコントローラ======
	camaraController_ = new CameraController();
	camaraController_->Initialize(&camera_);
	camaraController_->SetTarget(player_);
	camaraController_->Reset();

	//======デバック======
	debugCamera_ = new DebugCamera(1280, 720);
}

void GameScene::Update() {
	GameScene::ChangePhase();
#ifdef _DEBUG
	ImGui::Begin("Debug");
	if (ImGui::Button("Reload")) {
		reloadRequested_ = true;
	}

	const char* modeNames[] = {"Follow", "ForcedScroll"};
	int mode = static_cast<int>(camaraController_->GetMode());
	if (ImGui::Combo("Camera Mode", &mode, modeNames, IM_ARRAYSIZE(modeNames))) {
		camaraController_->SetMode(static_cast<Mode>(mode));
	}

	ImGui::End();
#endif // _DEBUG

	//======更新処理=======

	switch (phase_) {
	case Phase::kPlay:
		GamePlayPhaseUpdate();
		break;
	case Phase::kDeath:
		DeathPhaseUpdate();
		break;
	case Phase::kFadeIn:
	case Phase::kFadeOut:
		fade_->Update();
		break;
	default:
		break;
	}

	//======カメラ======
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

	//======matrix更新======
	UpdateMatrix();
}

// 位置の更新は別にしておく
void GameScene::UpdateMatrix() {
	// 天球
	skyDome_->UpdateMatrix();
	// プレイヤー
	player_->UpdateMatrix();
	// 敵
	for (BaseEnemy* enemies : enemies_) {
		if (enemies != nullptr) {
			enemies->UpdateMatrix();
		}
	}

	// エフェクト
	for (Effect* hitEffects : hitEffects_) {
		if (hitEffects != nullptr) {
			hitEffects->UpdateMatrix();
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

	if (deathParticles_ != nullptr) {
		deathParticles_->UpdateMatrix();
	}
}

///==========================
/// ゲームフェーズの処理
///==========================
void GameScene::GamePlayPhaseUpdate() {
	// 天球
	skyDome_->Update();

	// プレイヤー
	player_->Update();

	enemies_.remove_if([](BaseEnemy* enemy) {
		if (enemy->IsDead()) {
			delete enemy;
			return true;
		}

		return false;
	});

	// エネミー
	for (BaseEnemy* enemies : enemies_) {
		if (enemies != nullptr) {
			enemies->Update();
		}
	}

	// エフェクト

	hitEffects_.remove_if([](Effect* hitEffect) {
		if (hitEffect->IsDead()) {
			delete hitEffect;
			return true;
		}

		return false;
	});

	for (Effect* hitEffects : hitEffects_) {
		if (hitEffects != nullptr) {
			hitEffects->Update();
		}
	}

	// 当たり判定をおこなう
	CheckAllCollisions();
}

///==========================
/// デスフェーズの処理
///==========================
void GameScene::DeathPhaseUpdate() {
	// 天球
	skyDome_->Update();
	player_->Update();

	// エネミー
	for (BaseEnemy* enemies : enemies_) {
		if (enemies != nullptr) {
			enemies->Update();
		}
	}

	for (Effect* hitEffects : hitEffects_) {
		if (hitEffects != nullptr) {
			hitEffects->Update();
		}
	}

	//======デスパーティクル======
	if (deathParticles_ != nullptr) {
		deathParticles_->Update();
	}

	// 終了条件を満たしたらシーンチェンジのフラグを立てる
	if (deathParticles_ && deathParticles_->IsFinished()) {
		fade_->Start(Fade::Status::FadeOut, fadeOutDuration_);
		phase_ = Phase::kFadeOut;
	}
}

///==========================
/// 描画処理
///==========================
void GameScene::Draw() {
	Model::PreDraw();
	// 天球
	skyDome_->Draw();

	// プレイヤー
	player_->Draw();

	// エネミー
	for (BaseEnemy* enemies : enemies_) {
		if (enemies != nullptr) {
			enemies->Draw();
		}
	}

	for (Effect* hitEffects : hitEffects_) {
		if (hitEffects != nullptr) {
			hitEffects->Draw();
		}
	}

	// パーティクル
	if (deathParticles_ != nullptr) {
		deathParticles_->Draw();
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

	fade_->Draw();
}

///==========================
/// マップ生成
///==========================
void GameScene::GenerateMapChips() {

	uint32_t kNumBlockVertical = mapChipField_->GetNumBlockVertical();
	uint32_t kNumBlockHorizontal = mapChipField_->GetNumBlockHorizontal();

	worldTransFormBlocks_.resize(kNumBlockVertical);
	for (uint32_t i = 0; i < kNumBlockVertical; i++) {
		worldTransFormBlocks_[i].resize(kNumBlockHorizontal);
	}

	for (uint32_t i = 0; i < kNumBlockVertical; i++) {
		for (uint32_t j = 0; j < kNumBlockHorizontal; j++) {
			switch (mapChipField_->GetMapChipTypeByIndex(j, i)) {
			case MapChipType::kBlock: {
				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransFormBlocks_[i][j] = worldTransform;
				worldTransFormBlocks_[i][j]->translation_ = ToKamataEngine(mapChipField_->GetMapChipPositionByIndex(j, i));
				break;
			}
			case MapChipType::kPlayer:
				assert(player_ == nullptr && "自キャラを二重に配置しようとしています");

				//======プレイヤー======
				playerModel_ = Model::CreateFromOBJ("Player", true);
				player_ = new Player();
				playerAttackModel_ = Model::CreateFromOBJ("AttackEffect", true);
				player_->Initialize(playerModel_, playerAttackModel_, &camera_, mapChipField_->GetMapChipPositionByIndex(j, i));
				player_->SetMapChipField(mapChipField_);

				break;
			case MapChipType::kEnemy:
				GenerateEnemy(i, j);
				break;
			default:
				break;
			}
		}
	}
}

void GameScene::GenerateEnemy(const uint32_t& i, const uint32_t& j) {
	uint8_t subID = mapChipField_->GetMapChipSubIDByIndex(j, i);
	switch (subID) {
	case 0: {
		Enemy* newEnemy = new Enemy();
		enemyModel_ = Model::CreateFromOBJ("Enemy", true);
		newEnemy->Initialize(enemyModel_, &camera_, this, mapChipField_->GetMapChipPositionByIndex(j, i));
		enemies_.push_back(newEnemy);
	} break;
	case 1: {
		ShieldEnemy* newEnemy = new ShieldEnemy();
		shieldEnemyModel_ = Model::CreateFromOBJ("ShieldEnemy", true);
		newEnemy->Initialize(shieldEnemyModel_, &camera_, this, mapChipField_->GetMapChipPositionByIndex(j, i));
		enemies_.push_back(newEnemy);
	} break;
	default:
		break;
	}
}

///==========================
/// 衝突確認
///==========================
void GameScene::CheckAllCollisions() {
#pragma region playerToEnemy
	AABB aabb1 = player_->GetAABB();
	AABB aabb2;
	for (BaseEnemy* enemy : enemies_) {
		if (enemy->IsCollisionDisabled()) {
			continue;
		}

		aabb2 = enemy->GetAABB();
		if (AABBCollision(aabb1, aabb2)) {
			player_->OnCollision(enemy);
			enemy->OnCollision(player_);
		}
	}

#pragma endregion
}

///==========================
/// フェーズチェンジ
///==========================
void GameScene::ChangePhase() {
	switch (phase_) {
	case Phase::kFadeIn:
		if (fade_->IsFinished()) {
			phase_ = Phase::kPlay;
			camaraController_->SetIsScroll(true);
		}

		break;
	case Phase::kPlay:
		if (player_->IsDead()) {
			phase_ = Phase::kDeath;
			camaraController_->SetIsScroll(false);
			const SelfVec3& deathParticlesPosition = player_->GetWorldPosition();

			deathParticles_ = new DeathParticles;
			deathParticles_->Initialize(particleModel_, &camera_, deathParticlesPosition);
		}
		break;
	case Phase::kDeath:

		break;
	case Phase::kFadeOut:
		if (fade_->IsFinished()) {
			finished_ = true;
		}
		break;
	default:
		break;
	}
}

void GameScene::CreateHitEffect(NemotoLibrary::SelfVec3& position) {
	Effect* newHitEffect = HitEffect::Create(position);
	hitEffects_.push_back(newHitEffect);
}

void GameScene::CreateGuardEffect(NemotoLibrary::SelfVec3& position) {
	Effect* newHitEffect = GuardEffect::Create(position);
	hitEffects_.push_back(newHitEffect);
}
