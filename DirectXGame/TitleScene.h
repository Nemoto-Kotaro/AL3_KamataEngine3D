#pragma once
#include <vector>
#include "KamataEngine.h"

class TitleScene {
private:

	bool finished_ = false;

public:
	void Initialize();
	void Update();
	void Draw();

	bool IsFinished() const { return finished_; };
};
