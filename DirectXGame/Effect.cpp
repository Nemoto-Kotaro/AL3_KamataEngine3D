#include "HitEffect.h"
#include "Random.h"
#include "WorldTransform.h"
#include "easing.h"
#include "mathTypes.h"
#include <cassert>
#include <numbers>

KamataEngine::Camera* Effect::camera_ = nullptr;

using namespace KamataEngine;
using namespace NemotoLibrary;

