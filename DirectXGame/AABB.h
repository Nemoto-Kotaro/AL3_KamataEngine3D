#pragma once
#include "SelfVector.h"
#include "mathTypes.h"

namespace NemotoLibrary {
	struct AABB {
		AABB();
		AABB(SelfVec3 pos, SelfVec2 size);

		SelfVec3 min;
		SelfVec3 max;
	};

	bool AABBCollision(AABB a, AABB b);
}