#pragma once
#include <vector>
#include "KamataEngine.h"
#include "Player.h"

class GameScene {
private:
	KamataEngine::Camera camera_;

	//プレイヤー
	uint32_t playerTextureHandle_ = 0;
	KamataEngine::Model* playerModel_ = nullptr;
	Player* player_ = nullptr;

	//ブロック
	uint32_t blockTextureHandle_ = 0;
	KamataEngine::Model* blockModel_ = nullptr;
	std::vector < std::vector<KamataEngine::WorldTransform*>> worldTransFormBlocks_;

	
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
