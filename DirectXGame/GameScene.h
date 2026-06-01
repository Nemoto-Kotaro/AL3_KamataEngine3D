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
#include "HitEffect.h"

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
	KamataEngine::Model* playerAttackModel_ = nullptr;


	//エネミー
	KamataEngine::Model* enemyModel_ = nullptr;
	KamataEngine::Model* shieldEnemyModel_ = nullptr;
	std::list<BaseEnemy*> enemies_;

	

	//エフェクト
	KamataEngine::Model* hitEffectModel_ = nullptr;
	std::list<HitEffect*> hitEffects_;


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

	// エフェクトの生成
	void CreateHitEffect(NemotoLibrary::SelfVec3& position);

	//ゲッターセッター
	bool IsFinished() const { return finished_; };
};
