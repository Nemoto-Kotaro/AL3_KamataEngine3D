#include "TitleScene.h"

using namespace KamataEngine;

TitleScene::TitleScene() {}

TitleScene::~TitleScene() {
	delete playerModel_;
	delete titleModel_;
}

void TitleScene::Initialize() { 
	playerModel_ = Model::CreateFromOBJ("Player", true);
	titleModel_ = Model::CreateFromOBJ("title", true);

}

void TitleScene::Update() {
	if (Input::GetInstance()->PushKey(DIK_SPACE)) {
		finished_ = true;
	}
}

void TitleScene::Draw() {}