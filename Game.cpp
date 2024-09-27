#define NOMINMAX
#include "Game.h"
#include "algorithm"
#include "imgui.h"
#include "Calculator.h"

#define GRAY 0xAAAAAAFF

Game::~Game() {
	delete world_, camera_;
}

void Game::Initialize() {

	worldAffine_ = {
		.scale{1,1,1},
		.rotate{0,0,0},
		.translate{0,0,0}
	};

	world_ = new World();
	world_->Initialize(worldAffine_);


	cameraAffine_ = {
		.scale{ 1.0f,1.0f,1.0f },
		.rotate{ 0.26f,0.0f,0.0f },
		.translate{ 0.0f,0.2f,-6.77f }
	};

	camera_ = new Camera();
	camera_->Initialize(cameraAffine_);

	prevMouse = { 0,0 };
	mouse = { 0,0 };

	ball_ = {
		.position = {1.0f,0.0f,0.0f},
		.mass = 2.0f,
		.radius = 0.05f,
		.color = BLUE
	};

}

void Game::Update() {

	///
	/// ↓更新処理ここから
	///

	Game::Create_RenderingPipeline();

	Game::CameraControl();

	if (isCircleMove) {
		theta += deltaTime * float(M_PI);

		ball_.position.x = center_.x + cosf(theta);
		ball_.position.y = center_.y + sinf(theta);
	}

	///
	/// ↑更新処理ここまで
	///

}

void Game::Draw() {

	///
	/// ↓描画処理ここから
	///

	Graphics::DrawGrid(camera_->GetViewProjectionMatrix(), camera_->GetViewportMatrix(), GRAY);

	Sphere sphere = { {ball_.position }, ball_.radius };
	Graphics::DrawSphere(sphere, camera_->GetViewProjectionMatrix(), camera_->GetViewportMatrix(), BLUE);

	Game::DrawDebugText();


	///
	/// ↑描画処理ここまで
	///

}

void Game::DisplaySize() {

	const char kWindowTitle[] = "GC2A_02_アリマ_ナオト";

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, (int)Camera::GetWindowWidth(), (int)Camera::GetWindowHeight());


}

void Game::StartFrame(char *keys,char *preKeys) 
{
	// フレームの開始
	Novice::BeginFrame();

	// キー入力を受け取る
	memcpy(preKeys, keys, 256);
	Novice::GetHitKeyStateAll(keys);
}

void Game::Create_RenderingPipeline() {

	world_->CreateAffineMatrix(worldAffine_);

	camera_->CreateAffineMatrix(cameraAffine_);

	camera_->CreateViewMatrix();

	camera_->CreateProjectionMatrix();

	camera_->CreateViewProjectionMatrix();

	camera_->CreateViewportMatrix();

}

void Game::MoveScale(Affine& camera) {

	int32_t wheel = Novice::GetWheel();

	camera.scale.z += (wheel / (1024.f * 2.f));
	camera.scale.z = std::clamp(camera.scale.z, 0.5f, 1.0f);

}

void Game::MoveRotation(Affine &camera){

	Novice::GetMousePosition(&mouse.x, &mouse.y);

	if (Novice::IsPressMouse(1)) {
		Vector2 delta = mouse - prevMouse;

		camera.rotate.x += delta.y * 0.005f;
		camera.rotate.y += delta.x * 0.005f;
	}

	prevMouse = mouse;
}

void Game::CameraControl() {

	Game::MoveScale(cameraAffine_);

	Game::MoveRotation(cameraAffine_);

}

void Game::DrawDebugText() {

	ImGui::DragFloat3("translate", &ball_.position.x, 0.01f);

	if (ImGui::Button("start")) {
		isCircleMove = true;
	}

}

void Game::MainLoop() {

	Game::DisplaySize();

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {

		Game::StartFrame(keys, preKeys);

		Game::Update();

		Game::Draw();

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}
}