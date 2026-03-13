#include "SelfVector.h"
#include "SelfMatrix.h"


using namespace KamataEngine;
using namespace NemotoLibrary;

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

KamataEngine::Vector2 SelfVec2::ToKamataEngine() const { return {x, y}; }


SelfVec2 NemotoLibrary::ToMyEngine(const KamataEngine::Vector2& vector2) { return {vector2.x, vector2.y}; };
KamataEngine::Vector2 NemotoLibrary::ToKamataEngine(const SelfVec2& vector2) { return {vector2.x, vector2.y}; }

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

KamataEngine::Vector3 SelfVec3::ToKamataEngine() const { return {x, y, z}; };

SelfVec3 NemotoLibrary::ToMyEngine(const KamataEngine::Vector3& vector3) { return {vector3.x, vector3.y, vector3.z}; };
KamataEngine::Vector3 NemotoLibrary::ToKamataEngine(const SelfVec3& vector3) { return {vector3.x, vector3.y, vector3.z}; };


SelfVec3 NemotoLibrary::TransformCoord(const SelfVec3& v, const SelfMatrix4x4& m) {
	SelfVec3 result;

	result.x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + m.m[3][0];
	result.y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + m.m[3][1];
	result.z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + m.m[3][2];
	float w = v.x * m.m[0][3] + v.y * m.m[1][3] + v.z * m.m[2][3] + m.m[3][3];

	if (w != 0.0f) {
		result.x /= w;
		result.y /= w;
		result.z /= w;
	}

	return result;
}


SelfVec3 NemotoLibrary::Lerp(SelfVec3 start, SelfVec3 end, float ratio) { 
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

KamataEngine::Vector4 SelfVec4::ToKamataEngine() const { return {x, y, z, w}; }

SelfVec4 NemotoLibrary::ToMyEngine(const KamataEngine::Vector4& vector4) { return {vector4.x, vector4.y, vector4.z, vector4.w}; };
KamataEngine::Vector4 NemotoLibrary::ToKamataEngine(const SelfVec4& vector4) { return {vector4.x, vector4.y, vector4.z, vector4.w}; };