#pragma once
#include <vector>
#include "KamataEngine.h"
#include "WorldTransform.h"
#include "Player.h"
#include "Skydome.h"

class GameScene {
private:
	KamataEngine::Camera camera_;

	//プレイヤー
	KamataEngine::Model* playerModel_ = nullptr;
	Player* player_ = nullptr;

	//ブロック
	KamataEngine::Model* blockModel_ = nullptr;
	std::vector < std::vector<KamataEngine::WorldTransform*>> worldTransFormBlocks_;

	//天球
	KamataEngine::Model* skyDomeModel_ = nullptr;
	Skydome* skyDome_ = nullptr;
	
	// デバック
	bool isDebugCameraActive_ = false;
	KamataEngine::DebugCamera* debugCamera_ = nullptr;

public:
	GameScene();
	~GameScene();
	void Initialize();
	void Update();
	void Draw();
};
