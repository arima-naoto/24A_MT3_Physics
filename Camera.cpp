#include "Camera.h"

void Camera::Initialize(Affine affine) {

	affine_ = affine;

	cameraMatrix_ = {};

	viewMatrix_ = {};

	projectionMatrix_ = {};

	viewProjectionMatrix_ = {};

	viewportMatrix_ = {};

}

void Camera::CreateAffineMatrix(Affine affine) { cameraMatrix_ = Rendering::STRAffineMatrix(affine); }

void Camera::CreateViewMatrix() { viewMatrix_ = Rendering::Inverse(cameraMatrix_); }

void Camera::CreateProjectionMatrix() {
	projectionMatrix_ = Rendering::MakePerspectiveFovMatrix(0.45f, Camera::kWindowWidth_ / Camera::kWindowHeight_, 0.1f, 100.0f);
}

void Camera::CreateViewProjectionMatrix(){ viewProjectionMatrix_ = viewMatrix_ * projectionMatrix_; }

void Camera::CreateViewportMatrix() { viewportMatrix_ = Rendering::ViewportMatrix(0, 0, kWindowWidth_, kWindowHeight_, 0.0f, 1.0f); }

Matrix4x4 Camera::GetViewMatrix() { return this->viewMatrix_; }

Matrix4x4 Camera::GetProjectionMatrix() { return this->projectionMatrix_; }

Matrix4x4 Camera::GetViewProjectionMatrix() { return this->viewProjectionMatrix_; }

Matrix4x4 Camera::GetViewportMatrix() { return this->viewportMatrix_; }

float Camera::GetWindowWidth() { return Camera::kWindowWidth_; }

float Camera::GetWindowHeight() { return Camera::kWindowHeight_; }