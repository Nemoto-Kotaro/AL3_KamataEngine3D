#include "GameScene.h"
#include "KamataEngine.h"
#include "TitleScene.h"
#include <Windows.h>

using namespace KamataEngine;

enum class Scene {
	kUnknown = 0,
	kTitle,
	kGame,
};

Scene scene = Scene::kUnknown;

GameScene* gameScene = nullptr;
TitleScene* titleScene = nullptr;

///=============
/// 関数
///=============
void ChangeScene();
void UpdateScene();
void DrawScene();

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	KamataEngine::Initialize(L"LC1A_20_ネモト_コタロウ_AL3");

	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	ImGuiManager* imguiManager = ImGuiManager::GetInstance();

	scene = Scene::kTitle;

#ifdef _DEBUG
	scene = Scene::kGame;
#endif // _DEBUG

	//シーン切り替え
	switch (scene) {
	case Scene::kTitle:
		titleScene = new TitleScene();
		titleScene->Initialize();
		break;
	case Scene::kGame:
		gameScene = new GameScene();
		gameScene->Initialize();
		break;
	default:
		break;
	}


	while (true) {

		if (KamataEngine::Update()) {
			break;
		}

		//============================
		// 更新処理
		//============================
		imguiManager->Begin();

		// シーンチェンジ
		ChangeScene();

		// 更新処理
		UpdateScene();

		imguiManager->End();

		//============================
		// 描画処理
		//============================
		dxCommon->PreDraw();
		// 描画処理
		DrawScene();

		AxisIndicator::GetInstance()->Draw();

		imguiManager->Draw();
		dxCommon->PostDraw();
	}

	// シーン解放
	delete titleScene;
	titleScene = nullptr;
	delete gameScene;
	gameScene = nullptr;

	KamataEngine::Finalize();
	return 0;
}

void ChangeScene() {
	switch (scene) {
	case Scene::kTitle:
		if (titleScene->IsFinished()) {
			// シーンを切り替える
			scene = Scene::kGame;
			// 解放を忘れない
			delete titleScene;
			titleScene = nullptr;
			gameScene = new GameScene;
			gameScene->Initialize();
		}
		break;
	case Scene::kGame:
		if (gameScene->IsFinished()) {
			// シーンを切り替える
			scene = Scene::kTitle;
			// 解放を忘れない
			delete gameScene;
			gameScene = nullptr;
			titleScene = new TitleScene;
			titleScene->Initialize();
		}

		break;
	default:
		break;
	}
}

void UpdateScene() {
	switch (scene) {
	case Scene::kTitle:
		titleScene->Update();
		break;
	case Scene::kGame:
		gameScene->Update();
		break;
	default:
		break;
	}
}

void DrawScene() {
	switch (scene) {
	case Scene::kTitle:
		titleScene->Draw();
		break;
	case Scene::kGame:
		gameScene->Draw();
		break;
	default:
		break;
	}
}