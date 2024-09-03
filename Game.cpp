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

	spring_ = {
		.anchor = { 0,1,0 },
	    .naturalLenght = 0.7f,
	    .stiffness = 100.0f,
		.dampingCoefficient = 2.0f
	};

	ball_ = {
		.position = {0.8f,0.2f,0.0f},
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

	Game::MoveSpring(spring_, ball_);

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

	Vector3 localAxis[2];
	localAxis[0] = { spring_.anchor };
	localAxis[1] = { ball_.position };

	Vector3 screenAxis[2];
	screenAxis[0] = Transform(Transform(localAxis[0], camera_->GetViewProjectionMatrix()), camera_->GetViewportMatrix());
	screenAxis[1] = Transform(Transform(localAxis[1], camera_->GetViewProjectionMatrix()), camera_->GetViewportMatrix());

	Novice::DrawLine((int)screenAxis[0].x, (int)screenAxis[0].y, (int)screenAxis[1].x, (int)screenAxis[1].y, WHITE);

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
	camera.scale.z = (std::max)(camera.scale.z, 0.5f);
	camera.scale.z = (std::min)(camera.scale.z, 1.0f);

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

void Game::MoveSpring(Spring& spring, Ball& ball) {

	Vector3 diff = ball.position - spring.anchor;
	
	float length = Calculator::Length(diff);

	const Vector3 kGravity = { 0.0f,-9.8f,0.0f };

	if (isSpring == true && length != 0.0f) {

		Vector3 direction = Calculator::Normalize(diff);

		Vector3 restPosition = spring.anchor + direction * spring.naturalLenght;

		Vector3 displacement = length * (ball.position - restPosition);

		Vector3 restoringForce = -spring.stiffness * displacement;

		Vector3 dampingForce = -spring.dampingCoefficient * ball.velocity;

		Vector3 force = restoringForce + dampingForce + kGravity;

		ball.acceletation = force / ball.mass;

	}
	else {
		return;
	}
	
	float deltaTime = 1.f / 60.f;

	ball.velocity += ball.acceletation * deltaTime;
	ball.position += ball.velocity * deltaTime;

}

void Game::DrawDebugText() {

	ImGui::Begin("DebugWindow");
	if (ImGui::Button("Start")) {
		isSpring = true;
	}
	ImGui::End();
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