#pragma once
#include "KamataEngine.h"
#include "SelfVector.h"
class Player;

struct Rect {
	float left = 0.0f;
	float right = 1.0f;
	float bottom = 0.0f;
	float top = 1.0f;
};

class CameraController {
private:
	KamataEngine::Camera* camera_;
	Player* target_ = nullptr;
	NemotoLibrary::SelfVec3 targetOffset_ = {0.0f,0.0f,-15.0f};
	Rect movableArea_ = {11.0f,88.0f,6.0f,20.0f};

	NemotoLibrary::SelfVec3 targetTransform;
	static inline const float kInterpolationRate = 0.04f;
	static inline const float kVelocityBias = 0.07f;

	static inline const Rect margin = {-6.0f,6.0f,-6.0f,6.0f};

public:
	void Initialize(KamataEngine::Camera* camera);
	void Update();

	void Reset();
	void SetTarget(Player* target) { target_ = target; };
	void SetMovableArea(Rect area) { movableArea_ = area; };
};
