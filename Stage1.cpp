﻿#include "Stage1.h"

void Stage1::Initialize() {

	playerPos = { 200.0f,832.0f };

	playerRad = 64.0f;
	speed = 5.0f;

	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 15; x++) {
			//ブロックの座標、サイズ設定
			block[y][x].pos.x = float(x * blockSize);
			block[y][x].pos.y = float(y * blockSize);
			block[y][x].size.x = 128.0f;
			block[y][x].size.y = 128.0f;

			//ブロックがある場合
			if (map[y][x] == 1) {
				block[y][x].state = BLOCK;
				block[y][x].imagePos.x = 0.0f;
				block[y][x].imagePos.y = 128.0f;
			}

			//ブロックがない場合
			if (map[y][x] == 0) {
				block[y][x].state = NONE;
				block[y][x].imagePos.x = 128.0f;
				block[y][x].imagePos.y = 0.0f;
			}
		}
	}
}

void Stage1::Update() {

	//デバイス関連
	memcpy(preKeys, keys, 256);
	Novice::GetHitKeyStateAll(keys);
	Novice::GetAnalogInputLeft(0, &stickPosX, &stickPosY);

	//実ポジションを仮ポジションに代入
	playerPosOld = playerPos;

	//右上座標
	rightTopX = int((playerPos.x + playerRad) - 1) / blockSize;
	rightTopY = int(playerPos.y - playerRad) / blockSize;

	// 右下座標
	rightBottomX = int((playerPos.x + playerRad) - 1) / blockSize;
	rightBottomY = int((playerPos.y + playerRad) - 1) / blockSize;

	// 左上座標
	leftTopX = int((playerPos.x - playerRad) / blockSize + 0.5f);
	leftTopY = int((playerPos.y - playerRad)) / blockSize;

	// 左下座標
	leftBottomX = int((playerPos.x - playerRad) / blockSize + 0.5f);
	leftBottomY = int((playerPos.y + playerRad) - 1) / blockSize;

	//移動処理
	if (keys[DIK_A] || stickPosX <= -20000) {
		//ブロックに当たった時
		if (map[leftTopY][leftTopX] == BLOCK) {
			playerPos.x = playerPosOld.x;
			playerPos.y = playerPosOld.y;
		}
		else if (map[leftBottomY][leftBottomX] == BLOCK) {
			playerPos.x = playerPosOld.x;
			playerPos.y = playerPosOld.y;
		}
		//ブロックに当たっていないなら
		else { playerPos.x -= speed; }
	}
	else if (keys[DIK_D] || stickPosX >= 20000) {
		//ブロックに当たった時
		if (map[rightTopY][rightTopX] == BLOCK) {
			playerPos.x = playerPosOld.x;
			playerPos.y = playerPosOld.y;
		}
		else if (map[rightBottomY][rightBottomX] == BLOCK) {
			playerPos.x = playerPosOld.x;
			playerPos.y = playerPosOld.y;
		}
		//ブロックに当たっていないなら
		else { playerPos.x += speed; }
	}
	else {}
}

void Stage1::Draw() {
#ifdef _DEBUG
	Novice::ScreenPrintf(0, 0, "Stage1");
	Novice::ScreenPrintf(0, 20, "playerPos : %2.0f %2.0f", playerPos.x, playerPos.y);
	Novice::ScreenPrintf(0, 40, "left pos : %d %d", int(playerPos.x) / blockSize - 1, int(playerPos.y) / blockSize);
	Novice::ScreenPrintf(0, 60, "left player pos : bottom : %d %d , top : %d %d", leftBottomX, leftBottomY, leftTopX, leftTopY);
#endif

	//ブロックの描画
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 30; x++) {
			if (map[y][x] == 1) {
				Novice::DrawSprite(
					x * 128, y * 128, gh1, 1, 1, 0.0f, WHITE);
			}
		}
	}

	Novice::DrawBox(int(playerPos.x), int(playerPos.y), int(playerRad), int(playerRad), 0.0f, 0xFFFFFFFF, kFillModeSolid);

}
