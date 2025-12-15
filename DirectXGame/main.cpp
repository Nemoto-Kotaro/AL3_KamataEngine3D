#include <Windows.h>
#include "KamataEngine.h"
#include "GameScene.h"

using namespace KamataEngine;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	
	KamataEngine::Initialize(L"LC1A_20_ネモト_コタロウ_AL3");

	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	ImGuiManager* imguiManager = ImGuiManager::GetInstance();
	GameScene* gameScene = new GameScene();
	gameScene->Initialize();

	while (true) {
		
		if (KamataEngine::Update()) {
			break;
		}

		//============================
		// 更新処理
		//============================
		imguiManager->Begin();


		gameScene->Update();


		imguiManager->End();

		//============================
		// 描画処理
		//============================
		dxCommon->PreDraw();
		gameScene->Draw();

		AxisIndicator::GetInstance()->Draw();

		imguiManager->Draw();
		dxCommon->PostDraw();

	}

	delete gameScene;
	gameScene = nullptr;
	KamataEngine::Finalize();
	return 0;
}
