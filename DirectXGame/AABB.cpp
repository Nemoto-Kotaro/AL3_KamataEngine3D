#include "AABB.h"

using namespace NemotoLibrary;

AABB::AABB() {
	min = 0.0f;
	max = 0.0f;
}



AABB::AABB(SelfVec3 pos, SelfVec2 size) {
	min = {pos.x - size.x / 2.0f, pos.y - size.y / 2.0f, pos.z - size.x / 2.0f};
	max = {pos.x + size.x / 2.0f, pos.y + size.y / 2.0f, pos.z + size.x / 2.0f};
}

bool NemotoLibrary::AABBCollision(AABB a, AABB b) {
	if ((a.min.x <= b.max.x && a.max.x >= b.min.x) && (a.min.y <= b.max.y && a.max.y >= b.min.y) && (a.min.z <= b.max.z && a.max.z >= b.min.z)) {
		return true;
	}

	return false;
 }