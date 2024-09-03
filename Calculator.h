#pragma once
#include "MyStruct.h"
#define _USE_MATH_DEFINES
#include "cmath"

/// 計算クラスを宣言
class Calculator
{
public://メンバ関数

	static Vector3 AddVector(const Vector3& v1, const Vector3& v2);
	
	static Vector3 SubtractVector(const Vector3& v1, const Vector3& v2);
	
	static Vector3 MultiplyVector(float scalar, const Vector3 &v);
	
	static float Dot(const Vector3& v1, const Vector3& v2);
	
	static float Length(const Vector3& v);
	
	static Vector3 Normalize(const Vector3& v);

	static Vector3 Perpendicular(const Vector3& vector);

	static Vector3 Cross(const Vector3& v1, const Vector3& v2);

	static Matrix4x4 AddMatrix(const Matrix4x4 m1, const Matrix4x4& m2);

	static Matrix4x4 SubtractMatrix(const Matrix4x4& m1, const Matrix4x4& m2);

	static Matrix4x4 MultiplyMatrix(const Matrix4x4& m1, const Matrix4x4& m2);

	
};

