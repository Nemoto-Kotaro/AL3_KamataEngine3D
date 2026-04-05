#pragma once
#include "KamataEngine.h"
#include "SelfVector.h"



class Fade {
public:
	enum class Status {
		None,
		FadeIn,
		FadeOut,
	};

private:
	

	//フェードのスプライト画像
	uint32_t fadeTextureHandle = 0;
	KamataEngine::Sprite* sprite_ = nullptr;


	Status status_ = Status::None;

	//フェードの時間とカウンター
	float duration_ = 0.0f;
	float counter_ = 0.0f;


public:
	

	Fade();
	~Fade();

	void Initialize();
	void Update();
	void Draw();

	void Start(Status status,float duration);
	void Stop();

	
	// 終了判定
	bool IsFinished() const;
};