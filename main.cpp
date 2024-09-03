#include <Novice.h>
#include "Game.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	Game* game = new Game();
	game->Initialize();

	game->MainLoop();

	// ライブラリの終了
	Novice::Finalize();
	delete game;
	return 0;
}
