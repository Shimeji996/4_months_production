#include "Stage1.h"

void Stage1::Initialize() {

}

void Stage1::Update() {

	memcpy(preKeys, keys, 256);
	Novice::GetHitKeyStateAll(keys);

	Novice::GetAnalogInputLeft(0, &stickPosX, &stickPosY);

	Block block[8][15]{};

	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 15; x++) {
			//ブロックの座標、サイズ設定
			block[y][x].pos.x = float(x * blockSize);
			block[y][x].pos.y = float(y * blockSize);
			block[y][x].size.x = 128;
			block[y][x].size.y = 128;

			//ブロックがある場合
			if (map[y][x] == 1) {
				block[y][x].state = BLOCK;
				block[y][x].imagePos.x = 0;
				block[y][x].imagePos.y = 128;
			}

			//ブロックがない場合
			if (map[y][x] == 0) {
				block[y][x].state = NONE;
				block[y][x].imagePos.x = 128;
				block[y][x].imagePos.y = 0;
			}
		}
	}

	
}

void Stage1::Draw(){
	Novice::ScreenPrintf(0, 0, "Stage1");

	//ブロックの描画
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 30; x++) {
			if (map[y][x] == 1) {
				Novice::DrawSprite(
					x * 128, y * 128, gh1, 1, 1, 0.0f, WHITE);
			}
		}
	}

	
}
