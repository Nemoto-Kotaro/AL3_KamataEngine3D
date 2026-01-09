#pragma once
#include "KamataEngine.h"

//====================
// SelfVec2
//====================
struct SelfVec2 {
	float x;
	float y;

	// 加算
	void operator+=(const SelfVec2& rhs);
	SelfVec2 operator+(const SelfVec2& rhs) const;

	// 減算
	void operator-=(const SelfVec2& rhs);
	SelfVec2 operator-(const SelfVec2& rhs) const;

	// 乗算
	void operator*=(const float& num);
	SelfVec2 operator*(const float& num) const;

	// 除算
	void operator/=(const float& num);
	SelfVec2 operator/(const float& num) const;

	KamataEngine::Vector2 ToVector2() const { return {x, y}; }
};

//====================
// SelfVec3
//====================
struct SelfVec3 {
	float x;
	float y;
	float z;

	void operator+=(const SelfVec3& rhs);
	SelfVec3 operator+(const SelfVec3& rhs) const;

	void operator-=(const SelfVec3& rhs);
	SelfVec3 operator-(const SelfVec3& rhs) const;

	void operator+=(const KamataEngine::Vector3& rhs);
	SelfVec3 operator+(const KamataEngine::Vector3& rhs) const;

	void operator-=(const KamataEngine::Vector3& rhs);
	SelfVec3 operator-(const KamataEngine::Vector3& rhs) const;

	void operator*=(const float& num);
	SelfVec3 operator*(const float& num) const;

	void operator/=(const float& num);
	SelfVec3 operator/(const float& num) const;

	KamataEngine::Vector3 ToVector3() const { return {x, y, z}; }
};

SelfVec3 ChangeSelfVec3(const KamataEngine::Vector3& vector3);
KamataEngine::Vector3 ChangeVector3(const SelfVec3& vector3);

KamataEngine::Vector3 Lerp(KamataEngine::Vector3 start, KamataEngine::Vector3 end, float ratio);

    //====================
// SelfVec4
//====================
struct SelfVec4 {
	float x;
	float y;
	float z;
	float w;

	void operator+=(const SelfVec4& rhs);
	SelfVec4 operator+(const SelfVec4& rhs) const;

	void operator-=(const SelfVec4& rhs);
	SelfVec4 operator-(const SelfVec4& rhs) const;

	void operator*=(const float& num);
	SelfVec4 operator*(const float& num) const;

	void operator/=(const float& num);
	SelfVec4 operator/(const float& num) const;

	KamataEngine::Vector4 ToVector4() const { return {x, y, z, w}; }
};
