#include "Random.h"

int Random ::Range(int min, int max) {
	std::uniform_int_distribution<int> dist(min, max);
	return dist(GetEngine());
}

float Random ::Range(float min, float max) {
	std::uniform_real_distribution<float> dist(min, max);
	return dist(GetEngine());
}

std::mt19937& Random ::GetEngine() {
	static std::mt19937 engine(std::random_device{}());
	return engine;
}