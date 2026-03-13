#include <Windows.h>
#include "KamataEngine.h"
#include "GameScene.h"
#include "TitleScene.h"

using namespace KamataEngine;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	
	KamataEngine::Initialize(L"LC1A_20_ネモト_コタロウ_AL3");

	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	ImGuiManager* imguiManager = ImGuiManager::GetInstance();
	GameScene* gameScene = new GameScene();
	TitleScene* titleScene = nullptr;

	titleScene = new TitleScene();
	titleScene->Initialize();

	gameScene->Initialize();

	while (true) {
		
		if (KamataEngine::Update()) {
			break;
		}

		//============================
		// 更新処理
		//============================
		imguiManager->Begin();


		titleScene->Update();


		imguiManager->End();

		//============================
		// 描画処理
		//============================
		dxCommon->PreDraw();
		titleScene->Draw();

		AxisIndicator::GetInstance()->Draw();

		imguiManager->Draw();
		dxCommon->PostDraw();

	}

	delete titleScene;
	titleScene = nullptr;
	KamataEngine::Finalize();
	return 0;
}
