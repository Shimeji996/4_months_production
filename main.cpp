#include <Novice.h>
#include "GameManager.h"

const char kWindowTitle[] = "4ヶ月制作";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1920, 1024);

	GameManager* gameManager = new GameManager();
	
	gameManager->Run();

	return 0;
}
