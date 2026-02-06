#include "SelfVector.h"


using namespace KamataEngine;

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

void SelfVec3::operator+=(const Vector3& rhs) {
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
}

SelfVec3 SelfVec3::operator+(const Vector3& rhs) const { return {x + rhs.x, y + rhs.y, z + rhs.z}; }

void SelfVec3::operator-=(const Vector3& rhs) {
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
}

SelfVec3 SelfVec3::operator-(const Vector3& rhs) const { return {x - rhs.x, y - rhs.y, z - rhs.z}; }

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

SelfVec3 ChangeSelfVec3(const Vector3& vector3) { return {vector3.x, vector3.y, vector3.z}; };
Vector3 ChangeVector3(const SelfVec3& vector3) { return {vector3.x, vector3.y, vector3.z}; };


SelfVec3 TransformCoord(const SelfVec3& v, const Matrix4x4& m) {
	SelfVec3 result;

	result.x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + m.m[3][0];
	result.y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + m.m[3][1];
	result.z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + m.m[3][2];

	return result;
}


KamataEngine::Vector3 Lerp(KamataEngine::Vector3 start, KamataEngine::Vector3 end, float ratio) {
	return {(1.0f - ratio) * start.x + ratio * end.x, (1.0f - ratio) * start.y + ratio * end.y, (1.0f - ratio) * start.z + ratio * end.z};
}

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

Vector4 ChangeVector4(const SelfVec4& vector4) { return {vector4.x, vector4.y, vector4.z, vector4.w}; };