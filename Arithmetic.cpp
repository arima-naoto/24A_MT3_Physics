#include "Arithmetic.h"

Vector2 operator-(const Vector2& v1, const Vector2& v2) { return Vector2(v1.x - v2.x, v1.y - v2.y); }

Vector3 operator+(const Vector3& v1, const Vector3& v2) { return Calculator::AddVector(v1, v2); }

Vector3 operator-(const Vector3& v1, const Vector3& v2) { return Calculator::SubtractVector(v1, v2); }

Vector3 operator*(float s, const Vector3& v) { return Calculator::MultiplyVector(s, v); }

Vector3 operator*(const Vector3& v, float s) { return s * v; }

Vector3 operator/(const Vector3& v, float s) { return Calculator::MultiplyVector(1.0f / s, v); }

Matrix4x4 operator+(const Matrix4x4& m1, const Matrix4x4& m2) { return Calculator::AddMatrix(m1, m2); }

Matrix4x4 operator-(const Matrix4x4& m1, const Matrix4x4& m2) { return Calculator::SubtractMatrix(m1, m2); }

Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2) { return Calculator::MultiplyMatrix(m1, m2); }

Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t) { return Vector3(v1 * (1.0f - t) + v2 * t); }
