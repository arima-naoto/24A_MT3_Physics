#pragma once
#include "World.h"
#include "Camera.h"
#include "Graphics.h"

class Game : public Graphics
{
public:

	~Game();

	void Initialize();

	void Update();

	void Draw();

	void DisplaySize();

	void StartFrame(char* keys, char* preKeys);

	void Create_RenderingPipeline();

	void MoveScale(Affine &camera);

	void MoveRotation(Affine& camera);

	void CameraControl();

	void DrawDebugText();

	void MainLoop();

private:

	Affine worldAffine_;
	World* world_;

	Affine cameraAffine_;
	Camera* camera_;

	Vector2 prevMouse;
	Vector2 mouse;

	Ball ball_;

	Vector3 center_ = {0.0f,0.0f,0.0f};

	bool isCircleMove = false;

	float deltaTime = 1.f / 90.f;

	float radius = 8;

	float theta = 0;

};

