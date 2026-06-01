#pragma once
#include "KamataEngine.h"
#include "SelfVector.h"
#include <array>

class Effect {
public:
protected:
	static KamataEngine::Camera* camera_;

public:
	virtual ~Effect() = default;

	virtual void Initialize(NemotoLibrary::SelfVec3& position) = 0;
	virtual void Update() = 0;
	virtual void UpdateMatrix() = 0;
	virtual void Draw() = 0;

	// セッターゲッター
	static void SetCamera(KamataEngine::Camera* camera) { camera_ = camera; };
	virtual bool IsDead() const = 0;
};
