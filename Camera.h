#pragma once
#include "Rendering.h"

class Camera : public Rendering
{
public:

	void Initialize(Affine affine);

	void CreateAffineMatrix(Affine affine);

	void CreateViewMatrix();

	void CreateProjectionMatrix();

	void CreateViewProjectionMatrix();

	void CreateViewportMatrix();

public:

	Matrix4x4 GetViewMatrix();

	Matrix4x4 GetProjectionMatrix();
	
	Matrix4x4 GetViewProjectionMatrix();
	
	Matrix4x4 GetViewportMatrix();
	
	static float GetWindowWidth();
	
	static float GetWindowHeight();

private:

	Affine affine_;

	Matrix4x4 cameraMatrix_;

	Matrix4x4 viewMatrix_;

	Matrix4x4 projectionMatrix_;

	Matrix4x4 viewProjectionMatrix_;

	Matrix4x4 viewportMatrix_;

	static inline const float kWindowWidth_ = 1280.0f;
	static inline const float kWindowHeight_ = 720.0f;

};

