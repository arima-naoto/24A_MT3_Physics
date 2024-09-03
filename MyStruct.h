#pragma once

struct Vector2 {
	int x;
	int y;
};

/// 3次元ベクトル構造体の宣言
struct Vector3 {
	float x;
	float y;
	float z;

	Vector3 operator+=(const Vector3& obj) {
		this->x += obj.x;
		this->y += obj.y;
		this->z += obj.z;
		return *this;
	}

	Vector3 operator-=(const Vector3& obj) {
		this->x -= obj.x;
		this->y -= obj.y;
		this->z -= obj.z;
		return *this;
	}

};

/// 行列4x4構造体の宣言
struct Matrix4x4 {
	float m[4][4];
};

///アフィン構造体
struct Affine
{
	Vector3 scale;
	Vector3 rotate;
	Vector3 translate;
};



///線分構造体
struct Segment {
	Vector3 origin;//始点
	Vector3 diff; //終点への差分ベクトル
};

/// 球体の構造体
struct Sphere
{
	Vector3 center;
	float radius;
};

///平面構造体
struct Plane {

	Vector3 normal;//法線
	float distance;//距離
};

//三角形構造体
struct Triangle {
	Vector3 vertices[3];
};

//軸並行境界箱構造体
struct AABB {

	Vector3 min;//最小店
	Vector3 max;//最大店

};

struct Spring 
{
	Vector3 anchor;
	float naturalLenght;
	float stiffness;
	float dampingCoefficient;
};

struct Ball
{
	Vector3 position;
	Vector3 velocity;
	Vector3 acceletation;
	float mass;
	float radius;
	unsigned int color;
};