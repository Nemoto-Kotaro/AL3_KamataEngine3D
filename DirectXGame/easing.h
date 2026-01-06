#pragma once

//イージングの種類
enum EasingType {
	NONE,
	SINE,
	QUAD,
	CUBIC,
	QUART,
	QUINT,
	EXPO,
	CIRC,
	BACK,
	ELASTIC,
	BOUNCE
};

//イン,アウト,インアウトの選択
enum EasingMode {
	EASE_IN,
	EASE_OUT,
	EASE_INOUT,
};

//イージング選択変数
typedef struct EaseSelect {
	EasingType type;
	EasingMode mode;
}EaseSelect;

/// <summary>
/// イージングの関数（変数で選択型）
/// </summary>
/// <param name="ease"> イージング種類の選択 </param>
/// <param name="t"> 0.0fから1.0fの間 </param>
/// <returns>easeT</returns>
float Easing(const EaseSelect& ease, float t);

//イージング
//Ease::で呼び出し
namespace Ease {
	float InSine(float t);
	float OutSine(float t);
	float InOutSine(float t);
	float InQuad(float t);
	float OutQuad(float t);
	float InOutQuad(float t);
	float InCubic(float t);
	float OutCubic(float t);
	float InOutCubic(float t);
	float InQuart(float t);
	float OutQuart(float t);
	float InOutQuart(float t);
	float InQuint(float t);
	float OutQuint(float t);
	float InOutQuint(float t);
	float InExpo(float t);
	float OutExpo(float t);
	float InOutExpo(float t);
	float InCirc(float t);
	float OutCirc(float t);
	float InOutCirc(float t);
	float InBack(float t);
	float OutBack(float t);
	float InOutBack(float t);
	float InElastic(float t);
	float OutElastic(float t);
	float InOutElastic(float t);
	float InBounce(float t);
	float OutBounce(float t);
	float InOutBounce(float t);
}