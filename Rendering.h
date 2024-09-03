#pragma once
#include "Arithmetic.h"

class Rendering
{
public:

	static float Cot(float x);

	static Matrix4x4 MakeScaleMatrix(const Vector3& scale);

	static Matrix4x4 MakeRotateXMatrix(float radian);

	static Matrix4x4 MakeRotateYMatrix(float radian);

	static Matrix4x4 MakeRotateZMatrix(float radian);

	static Matrix4x4 MakeRotateMatrix(const Vector3& rotate);

	static Matrix4x4 MakeTranslateMatrix(const Vector3& translate);

	static Matrix4x4 SRTAffineMatrix(const Affine& affine);

	static Matrix4x4 STRAffineMatrix(const Affine& affine);

	static Matrix4x4 Inverse(const Matrix4x4& m);

	static Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);

	static Matrix4x4 ViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);

	static Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix4x4);

};

