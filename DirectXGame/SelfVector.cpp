#include "SelfVector.h"

//=======================================
// SelfVec2
//=======================================

void SelfVec2::operator+=(const SelfVec2& rhs) {
	x += rhs.x;
	y += rhs.y;
}

SelfVec2 SelfVec2::operator+(const SelfVec2& rhs) const { return {x + rhs.x, y + rhs.y}; }

void SelfVec2::operator-=(const SelfVec2& rhs) {
	x -= rhs.x;
	y -= rhs.y;
}

SelfVec2 SelfVec2::operator-(const SelfVec2& rhs) const { return {x - rhs.x, y - rhs.y}; }

void SelfVec2::operator*=(const float& num) {
	x *= num;
	y *= num;
}

SelfVec2 SelfVec2::operator*(const float& num) const { return {x * num, y * num}; }

void SelfVec2::operator/=(const float& num) {
	if (num == 0.0f) {
		x = 0.0f;
		y = 0.0f;
		return;
	}
	x /= num;
	y /= num;
}

SelfVec2 SelfVec2::operator/(const float& num) const {
	if (num == 0.0f) {
		return {0.0f, 0.0f};
	}
	return {x / num, y / num};
}

//=======================================
// SelfVec3
//=======================================

void SelfVec3::operator+=(const SelfVec3& rhs) {
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
}

SelfVec3 SelfVec3::operator+(const SelfVec3& rhs) const { return {x + rhs.x, y + rhs.y, z + rhs.z}; }

void SelfVec3::operator-=(const SelfVec3& rhs) {
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
}

SelfVec3 SelfVec3::operator-(const SelfVec3& rhs) const { return {x - rhs.x, y - rhs.y, z - rhs.z}; }

void SelfVec3::operator*=(const float& num) {
	x *= num;
	y *= num;
	z *= num;
}

SelfVec3 SelfVec3::operator*(const float& num) const { return {x * num, y * num, z * num}; }

void SelfVec3::operator/=(const float& num) {
	if (num == 0.0f) {
		x = y = z = 0.0f;
		return;
	}
	x /= num;
	y /= num;
	z /= num;
}

SelfVec3 SelfVec3::operator/(const float& num) const {
	if (num == 0.0f) {
		return {0.0f, 0.0f, 0.0f};
	}
	return {x / num, y / num, z / num};
}

SelfVec3 ChangeVec3(const KamataEngine::Vector3& vector3) { return {vector3.x, vector3.y, vector3.z}; };

//=======================================
// SelfVec4
//=======================================

void SelfVec4::operator+=(const SelfVec4& rhs) {
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	w += rhs.w;
}

SelfVec4 SelfVec4::operator+(const SelfVec4& rhs) const { return {x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w}; }

void SelfVec4::operator-=(const SelfVec4& rhs) {
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	w -= rhs.w;
}

SelfVec4 SelfVec4::operator-(const SelfVec4& rhs) const { return {x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w}; }

void SelfVec4::operator*=(const float& num) {
	x *= num;
	y *= num;
	z *= num;
	w *= num;
}

SelfVec4 SelfVec4::operator*(const float& num) const { return {x * num, y * num, z * num, w * num}; }

void SelfVec4::operator/=(const float& num) {
	if (num == 0.0f) {
		x = y = z = w = 0.0f;
		return;
	}
	x /= num;
	y /= num;
	z /= num;
	w /= num;
}

SelfVec4 SelfVec4::operator/(const float& num) const {
	if (num == 0.0f) {
		return {0.0f, 0.0f, 0.0f, 0.0f};
	}
	return {x / num, y / num, z / num, w / num};
}