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

	void MoveSpring(Spring& spring, Ball& ball);

	void DrawDebugText();

	void MainLoop();

private:

	Affine worldAffine_;
	World* world_;

	Affine cameraAffine_;
	Camera* camera_;

	Vector2 prevMouse;
	Vector2 mouse;

	Spring spring_;
	Ball ball_;
	
	bool isSpring = false;

};

