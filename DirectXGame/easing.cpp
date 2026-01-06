#define _USE_MATH_DEFINES
#include <math.h>
#include "easing.h"

//変数でイージング指定
float Easing(const EaseSelect& ease, float t) {
	switch (ease.type) {
	case SINE:
		switch (ease.mode) {
		case EASE_IN:
			return Ease::InSine(t);
		case EASE_OUT:
			return Ease::OutSine(t);
		case EASE_INOUT:
			return Ease::InOutSine(t);
		default:
			break;
		}

		break;
	case QUAD:
		switch (ease.mode) {
		case EASE_IN:
			return Ease::InQuad(t);
		case EASE_OUT:
			return Ease::OutQuad(t);
		case EASE_INOUT:
			return Ease::InOutQuad(t);
		default:
			break;
		}

		break;
	case CUBIC:
		switch (ease.mode) {
		case EASE_IN:
			return Ease::InCubic(t);
		case EASE_OUT:
			return Ease::OutCubic(t);
		case EASE_INOUT:
			return Ease::InOutCubic(t);
		default:
			break;
		}

		break;
	case QUART:
		switch (ease.mode) {
		case EASE_IN:
			return Ease::InQuart(t);
		case EASE_OUT:
			return Ease::OutQuart(t);
		case EASE_INOUT:
			return Ease::InOutQuart(t);
		default:
			break;
		}

		break;
	case QUINT:
		switch (ease.mode) {
		case EASE_IN:
			return Ease::InQuint(t);
		case EASE_OUT:
			return Ease::OutQuint(t);
		case EASE_INOUT:
			return Ease::InOutQuint(t);
		default:
			break;
		}

		break;
	case EXPO:
		switch (ease.mode) {
		case EASE_IN:
			return Ease::InExpo(t);
		case EASE_OUT:
			return Ease::OutExpo(t);
		case EASE_INOUT:
			return Ease::InOutExpo(t);
		default:
			break;
		}

		break;
	case CIRC:
		switch (ease.mode) {
		case EASE_IN:
			return Ease::InCirc(t);
		case EASE_OUT:
			return Ease::OutCirc(t);
		case EASE_INOUT:
			return Ease::InOutCirc(t);
		default:
			break;
		}

		break;
	case BACK:
		switch (ease.mode) {
		case EASE_IN:
			return Ease::InBack(t);
		case EASE_OUT:
			return Ease::OutBack(t);
		case EASE_INOUT:
			return Ease::InOutBack(t);
		default:
			break;
		}

		break;
	case ELASTIC:
		switch (ease.mode) {
		case EASE_IN:
			return Ease::InElastic(t);
		case EASE_OUT:
			return Ease::OutElastic(t);
		case EASE_INOUT:
			return Ease::InOutElastic(t);
		default:
			break;
		}

		break;
	case BOUNCE:
		switch (ease.mode) {
		case EASE_IN:
			return Ease::InBounce(t);
		case EASE_OUT:
			return Ease::OutBounce(t);
		case EASE_INOUT:
			return Ease::InOutBounce(t);
		default:
			break;
		}

		break;
	default:
		break;
	}

	return t;
}

//=============ここからイージング処理=============

float Ease::InSine(float t) {
	return 1.0f - cosf(t * static_cast<float>(M_PI) / 2.0f);
}

float Ease::OutSine(float t) {
	return sinf(t * static_cast<float>(M_PI) / 2.0f);
}

float Ease::InOutSine(float t) {
	return -(cosf(static_cast<float>(M_PI) * t) - 1.0f) / 2.0f;
}

float Ease::InQuad(float t) {
	return t * t;
}

float Ease::OutQuad(float t) {
	return 1.0f - (1.0f - t) * (1.0f - t);
}

float Ease::InOutQuad(float t) {
	if (t < 0.5f) {
		return 2.0f * t * t;
	} else {
		return 1.0f - powf(-2.0f * t + 2.0f, 2.0f) / 2.0f;
	}
}

float Ease::InCubic(float t) {
	return t * t * t;
}

float Ease::OutCubic(float t) {
	return 1.0f - powf(1.0f - t, 3.0f);
}

float Ease::InOutCubic(float t) {
	if (t < 0.5f) {
		return 4.0f * t * t * t;
	} else {
		return 1.0f - powf(-2.0f * t + 2.0f, 3.0f) / 2.0f;
	}
}

float Ease::InQuart(float t) {
	return t * t * t * t;
}

float Ease::OutQuart(float t) {
	return 1.0f - powf(1.0f - t, 4.0f);
}

float Ease::InOutQuart(float t) {
	if (t < 0.5f) {
		return 8.0f * t * t * t * t;
	} else {
		return 1.0f - powf(-2.0f * t + 2.0f, 4.0f) / 2.0f;
	}
}

float Ease::InQuint(float t) {
	return t * t * t * t * t;
}

float Ease::OutQuint(float t) {
	return 1.0f - powf(1.0f - t, 5.0f);
}

float Ease::InOutQuint(float t) {
	if (t < 0.5f) {
		return 16.0f * t * t * t * t * t;
	} else {
		return 1.0f - powf(-2.0f * t + 2.0f, 5.0f) / 2.0f;
	}
}

float Ease::InExpo(float t) {
	if (t == 0.0f) {
		return 0.0f;
	} else {
		return powf(2.0f, 10.0f * t - 10.0f);
	}
}

float Ease::OutExpo(float t) {
	if (t == 1.0f) {
		return 1.0f;
	} else {
		return 1.0f - powf(2.0f, -10.0f * t);
	}
}

float Ease::InOutExpo(float t) {
	if (t == 0.0f) {
		return 0.0f;
	} else if (t == 1.0f) {
		return 1.0f;
	} else if (t < 0.5f) {
		return powf(2.0f, 20.0f * t - 10.0f) / 2.0f;
	} else {
		return (2.0f - powf(2.0f, -20.0f * t + 10.0f)) / 2.0f;
	}
}

float Ease::InCirc(float t) {
	return 1.0f - sqrtf(1.0f - powf(t, 2.0f));
}

float Ease::OutCirc(float t) {
	return sqrtf(1.0f - powf(t - 1.0f, 2.0f));
}

float Ease::InOutCirc(float t) {
	if (t < 0.5f) {
		return (1.0f - sqrtf(1.0f - powf(-2.0f * t, 2.0f))) / 2.0f;
	} else {
		return (sqrtf(1.0f - powf(-2.0f * t + 2.0f, 2.0f)) + 1.0f) / 2.0f;
	}
}

float Ease::InBack(float t) {
	return 2.70158f * t * t * t - 1.70158f * t * t;
}

float Ease::OutBack(float t) {
	return 1.0f + 2.70158f * powf(t - 1.0f, 3.0f) + 1.70158f * powf(t - 1.0f, 2.0f);
}

float Ease::InOutBack(float t) {
	if (t < 0.5f) {
		return (powf(2.0f * t, 2.0f) * ((1.70158f * 1.525f + 1.0f) * 2.0f * t - 1.70158f * 1.525f)) / 2.0f;
	} else {
		return (powf(2.0f * t - 2.0f, 2.0f) * ((1.70158f * 1.525f + 1.0f) * (t * 2.0f - 2.0f) + 1.70158f * 1.525f) + 2.0f) / 2.0f;
	}
}

float Ease::InElastic(float t) {
	if (t == 0.0f) {
		return 0.0f;
	} else if (t == 1.0f) {
		return 1.0f;
	} else {
		return -powf(2.0f, 10.0f * t - 10.0f) * sinf((t * 10.0f - 10.75f) * (2.0f * static_cast<float>(M_PI)) / 3.0f);
	}
}

float Ease::OutElastic(float t) {
	if (t == 0.0f) {
		return 0.0f;
	} else if (t == 1.0f) {
		return 1.0f;
	} else {
		return powf(2.0f, -10.0f * t) * sinf((t * 10.0f - 0.75f) * (2.0f * static_cast<float>(M_PI)) / 3.0f) + 1.0f;
	}
}

float Ease::InOutElastic(float t) {
	if (t == 0.0f) {
		return 0.0f;
	} else if (t == 1.0f) {
		return 1.0f;
	} else if (t < 0.5f) {
		return -(powf(2.0f, 20.0f * t - 10.0f) * sinf((20.0f * t - 11.125f) * (2.0f * static_cast<float>(M_PI)) / 4.5f)) / 2.0f;
	} else {
		return (powf(2.0f, -20.0f * t + 10.0f) * sinf((20.0f * t - 11.125f) * (2.0f * static_cast<float>(M_PI)) / 4.5f)) / 2.0f + 1.0f;
	}
}

float Ease::InBounce(float t) {
	return 1.0f - Ease::OutBounce(1.0f - t);
}

float Ease::OutBounce(float t) {
	if (t < 1.0f / 2.75f) {
		return 7.5625f * t * t;
	} else if (t < 2.0f / 2.75f) {
		t -= 1.5f / 2.75f;
		return 7.5625f * t * t + 0.75f;
	} else if (t < 2.5f / 2.75f) {
		t -= 2.25f / 2.75f;
		return 7.5625f * t * t + 0.9375f;
	} else {
		t -= 2.625f / 2.75f;
		return 7.5625f * t * t + 0.984375f;
	}
}

float Ease::InOutBounce(float t) {
	if (t < 0.5f) {
		return (1.0f - Ease::OutBounce(1.0f - 2.0f * t)) / 2.0f;
	} else {
		return (1.0f + Ease::OutBounce(2.0f * t - 1.0f)) / 2.0f;
	}
}
