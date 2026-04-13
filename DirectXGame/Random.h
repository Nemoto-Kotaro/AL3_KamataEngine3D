#pragma once
#include <random>

class Random {
public:
	static int Range(int min,int max);

	static float Range(float min, float max);

private:
	static std::mt19937& GetEngine();
};
