#pragma once
#include "World.h"
#include "Camera.h"
#include "Graphics.h"

#include "memory"
using namespace std;

class Game : public Graphics
{
public:

	void Initialize();

	void Update();

	void Draw();

	void DisplaySize();

	void StartFrame(char* keys, char* preKeys);

	void Create_RenderingPipeline();

	void MoveScale(Affine &camera);

	void MoveRotation(Affine& camera);

	void MovePendulum(ConicalPendulum &conicalPendulum, Ball& ball);

	void CameraControl();

	void DrawDebugText();

	void DrawAxis();

	void MainLoop();

private:

	Affine worldAffine_;
	unique_ptr<World> world_ = nullptr;

	Affine cameraAffine_;
	unique_ptr<Camera> camera_ = nullptr;

	Vector2 prevMouse;
	Vector2 mouse;

	ConicalPendulum conicalPendulum_;
	Ball ball_;
	
	bool isPendulum = false;

	float deltaTime = 1.f / 60.f;

};

