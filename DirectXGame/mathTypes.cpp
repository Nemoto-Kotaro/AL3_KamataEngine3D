#define _USE_MATH_DEFINES
#include <math.h>
#include"mathTypes.h"


//====================
//便利な数学関数
//====================


//=======クランプ=======
int Clamp(const int& num, const int min, const int max) {
	if (num < min) {
		return  min;
	} else if (num > max) {
		return  max;
	}

	return num;
}

float Clamp(const float& num, const float min, const float max) {
	if (num < min) {
		return  min;
	} else if (num > max) {
		return  max;
	}

	return num;
}

//=======比率取得=======
float Ratio(const int value, const int min, const int max) {
	if (max - min != 0) {
		return static_cast<float>(Clamp(value, min, max) - min) / static_cast<float>(max - min);
	}

	return 0.0f;
}

float Ratio(const float value, const float min, const float max) {
	if (max - min != 0.0f) {
		return (Clamp(value, min, max) - min) / (max - min);
	}

	return 0.0f;
}


//=======数字は範囲内にあるか？=======
bool IsInRange(int num, const int min, const int max) {
	if (min <= num && max >= num) {
		return true;
	}

	return false;
}


//=======線形補間=======


float Lerp(const float& start, const float& end, const float t) {
	return  (1.0f - t) * start + t * end;
}



//=======deg⇒rad変換=======
float DegTheta(float degree) {
	return degree / 180.0f * static_cast<float>(M_PI);
}

//=======角度を円を分割した値で求める=======
float AngleByIndex(int index, int divisions) {
	return 2.0f * float(M_PI) * float(index) / float(divisions);
}

