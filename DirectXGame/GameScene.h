#pragma once
#include <vector>
#include "KamataEngine.h"
#include "WorldTransform.h"
#include "Player.h"
#include "Enemy.h"
#include "Skydome.h"
#include "MapChipField.h"
#include "CameraController.h"
#include "DeathParticles.h"
#include "Fade.h"

class GameScene {
private:
	enum class Phase {
		kFadeIn,
		kPlay,
		kDeath,
		kFadeOut
	};

	Phase phase_;


	//終了フラグ
	bool finished_ = false;

	//フェード
	Fade* fade_ = nullptr;
	const float fadeInDuration_ = 2.0f;
	const float fadeOutDuration_ = 2.0f;

	KamataEngine::Camera camera_;

	//カメラコントローラー
	CameraController* camaraController_ = nullptr;

	//プレイヤー
	KamataEngine::Model* playerModel_ = nullptr;
	Player* player_ = nullptr;

	//エネミー
	KamataEngine::Model* enemyModel_ = nullptr;
	std::list<Enemy*> enemies_;


	//ブロック
	MapChipField* mapChipField_;

	KamataEngine::Model* blockModel_ = nullptr;
	std::vector < std::vector<KamataEngine::WorldTransform*>> worldTransFormBlocks_;

	//パーティクル
	KamataEngine::Model* particleModel_ = nullptr;
	DeathParticles* deathParticles_ = nullptr;




	//天球
	KamataEngine::Model* skyDomeModel_ = nullptr;
	Skydome* skyDome_ = nullptr;
	
	// デバック
	bool isDebugCameraActive_ = false;
	KamataEngine::DebugCamera* debugCamera_ = nullptr;

	void GamePlayPhaseUpdate();
	void DeathPhaseUpdate();
	void ChangePhase();

public:
	GameScene();
	~GameScene();
	void Initialize();
	void Update();
	void UpdateMatrix();
	void Draw();

	void CheckAllCollisions();
	void GenerateBlocks();

	//ゲッターセッター
	bool IsFinished() const { return finished_; };
};
