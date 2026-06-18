#include "GameScene.h"
#include "KamataEngine.h"
#include "StageManager.h"
#include "TitleScene.h"
#include <Windows.h>
#include <fstream>
#include <sstream>
#include "GlobalVariables.h"

using namespace KamataEngine;

enum class Scene {
	kUnknown = 0,
	kTitle,
	kGame,
};

Scene scene = Scene::kUnknown;

GameScene* gameScene = nullptr;
TitleScene* titleScene = nullptr;
StageManager* stageManager = nullptr;

///=============
/// 関数
///=============
void ChangeScene();
void UpdateScene();
void DrawScene();
void LoadDebugSettings();

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	KamataEngine::Initialize(L"LE1A_19_ネモト_コタロウ_AL3");

	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	ImGuiManager* imguiManager = ImGuiManager::GetInstance();

	stageManager = new StageManager();

	stageManager->StageLoadCSV();

	scene = Scene::kTitle;

#ifdef _DEBUG
	LoadDebugSettings();

	scene = Scene::kGame;
#endif // _DEBUG
	GlobalVariables::GetInstance()->LoadFiles();

	// シーン切り替え
	switch (scene) {
	case Scene::kTitle:
		titleScene = new TitleScene();
		titleScene->Initialize();
		break;
	case Scene::kGame:
		gameScene = new GameScene();
		gameScene->Initialize(stageManager);
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
		
		GlobalVariables::GetInstance()->Update();
		
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
	delete stageManager;
	stageManager = nullptr;

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
			gameScene->Initialize(stageManager);
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
		} else if (gameScene->IsRequestReload()) {
			delete gameScene;
			gameScene = nullptr;
			gameScene = new GameScene;
			gameScene->Initialize(stageManager);
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


void LoadDebugSettings() {
	const std::string filePath = "DebugSettings.ini";
	std::ifstream file;
	file.open(filePath);
	if (!file.is_open()) {
		return;
	}

	std::stringstream debugSettingCSV;
	debugSettingCSV << file.rdbuf();
	file.close();

	std::string line;

	getline(debugSettingCSV, line);

	std::string key;
	std::string value;
	std::istringstream iss(line);
	iss >> key;
	iss >> value;

	if (key == "InitialStage") {
		stageManager->SetCurrentStageIndexByName(value);
	}
}