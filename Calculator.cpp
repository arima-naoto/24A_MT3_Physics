#include "Calculator.h"


Vector3 Calculator::AddVector(const Vector3& v1, const Vector3& v2)
{
	return { v1.x + v2.x,v1.y + v2.y,v1.z + v2.z };
}

Vector3 Calculator::SubtractVector(const Vector3& v1, const Vector3& v2)
{
	return  { v1.x - v2.x,v1.y - v2.y,v1.z - v2.z };
}

Vector3 Calculator::MultiplyVector(float scalar, const Vector3& v)
{
	return { scalar * v.x ,scalar * v.y,scalar * v.z };
}

float Calculator::Dot(const Vector3& v1, const Vector3& v2)
{
	return { v1.x * v2.x + v1.y * v2.y + v1.z * v2.z };
}

float Calculator::Length(const Vector3& v)
{
	float result = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	return result;
}

Vector3 Calculator::Normalize(const Vector3& v)
{
	float length = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	Vector3 resultNormalize = { v.x,v.y,v.z };

	if (length != 0.0f)
	{
		resultNormalize = { v.x / length,v.y / length,v.z / length };
	}
	return resultNormalize;
}

Vector3 Calculator::Perpendicular(const Vector3& vector) {

	if (vector.x != 0.0f || vector.y != 0.0f) {
		return { -vector.y ,vector.x,0.0f };
	}

	return { 0.0,-vector.z,vector.y };

}

Vector3 Calculator::Cross(const Vector3& v1, const Vector3& v2)
{
	//クロス積を求める
	return {
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x
	};
}

Matrix4x4 Calculator::AddMatrix(const Matrix4x4 m1, const Matrix4x4& m2)
{
	Matrix4x4 add{};

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			add.m[i][j] = m1.m[i][j] + m2.m[i][j];
		}
	}

	return add;
}

Matrix4x4 Calculator::SubtractMatrix(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 subtract{};

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			subtract.m[i][j] = m1.m[i][j] - m2.m[i][j];
		}
	}

	return subtract;
}

Matrix4x4 Calculator::MultiplyMatrix(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 multiply{};

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			multiply.m[i][j] = 0;
			for (int k = 0; k < 4; k++)
			{
				multiply.m[i][j] += m1.m[i][k] * m2.m[k][j];
			}
		}
	}

	return multiply;
}



