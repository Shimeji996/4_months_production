﻿#include "Stage1.h"

Stage1::Stage1()
{
}

Stage1::~Stage1()
{
	delete enemy_;
}

void Stage1::Initialize() {

	playerPosStart = { 400.0f,768.0f };
	playerPos = playerPosStart;
	playerRad = 128.0f;
	speed = 5.0f;
	playerColor = 0xFFFFFFFF;

	//敵の初期化
	enemy_ = new Enemy();

	//藁の初期化
	WalaPos = { 784.0, 640.0f };
	WalaRad = 129.0f;

	isJump = false;
	isGravity = false;

	isHitP2E = false;

	CreateMap();
}

void Stage1::Update() {
	//デバイス関連
	GetDevice();

	//プレイヤーの更新
	PlayerUpdate();

	//敵の更新関数
	enemy_->Update();

	//当たり判定
	GetAllCollision();
}

void Stage1::Draw() {
#ifdef _DEBUG
	Novice::ScreenPrintf(0, 0, "Stage1");
	Novice::ScreenPrintf(0, 20, "playerPos : %2.0f %2.0f", playerPos.x, playerPos.y);
	Novice::ScreenPrintf(0, 40, "playerMapPos : %d %d", int(playerPos.x) / blockSize, int(playerPos.y) / blockSize);
	Novice::ScreenPrintf(0, 60, "mapPos : rightBottom:%d %d %d, leftBottom:%d %d %d",
		int((playerPos.x) / blockSize), int((playerPos.y + playerRad) / blockSize) - 1, map[int((playerPos.y + playerRad) / blockSize) - 1][int((playerPos.x) / blockSize)],
		int((playerPos.x + playerRad) / blockSize), int((playerPos.y + playerRad) / blockSize) - 1, map[int((playerPos.y + playerRad) / blockSize) - 1][int((playerPos.x + playerRad) / blockSize)]);
#endif

	//プレイヤーの描画
	Novice::DrawBox(int(playerPos.x), int(playerPos.y), int(playerRad), int(playerRad), 0.0f, playerColor, kFillModeSolid); 

	//敵の描画関数
	enemy_->Draw(); 

	//ブロックの描画
	for (int y = 0; y < 100; y++) {
		for (int x = 0; x < 100; x++) {
			if (map[y][x] == 1) {
				Novice::DrawSprite(int(block[y][x].pos.x), int(block[y][x].pos.y), gh1, 1, 1, 0.0f, block[y][x].color);
			}
			else if (map[y][x] == 3) {
				Novice::DrawSprite(int(block[y][x].pos.x), int(block[y][x].pos.y), gh3, 1, 1, 0.0f, block[y][x].color);
			}
		}
	}
}

void Stage1::PlayerUpdate()
{
	//移動処理
	PlayerMove();

	//重力処理
	if (map[int((playerPos.y + playerRad) / blockSize)][int((playerPos.x) / blockSize)] != BLOCK &&
		map[int((playerPos.y + playerRad) / blockSize)][int((playerPos.x + playerRad - 1) / blockSize)] != BLOCK) {
		isGravity = true;
	}
	else {
		isGravity = false;
	}
	if (isGravity && !isJump) {
		playerPos.y += 10.0f;
	}

	//ジャンプ処理
	if (!isJump) {
		if (IsTriggerJump()) {
			//ジャンプ開始
			PlayerJumpInitialize();
		}
	}
	else {
		//ジャンプ更新処理
		PlayerJumpUpdate();
	}
}

void Stage1::PlayerMove()
{
	//移動
	//左ボタンを押しているとき
	if (IsPushLeft()) {
		playerPos.x -= speed;
	}
	//右ボタンを押しているとき
	else if (IsPushRight()) {
		playerPos.x += speed;
	}
}

void Stage1::PlayerJumpInitialize()
{
	isJump = true;
	jumpSpeed = -18.0f;
}

void Stage1::PlayerJumpUpdate()
{
	if (jumpSpeed <= 0) {
		playerPos.y += jumpSpeed;
	}
	else {
		if (map[int(playerPos.y + playerRad + jumpSpeed) / blockSize][int(playerPos.x) / blockSize] != BLOCK &&
			map[int(playerPos.y + playerRad + jumpSpeed) / blockSize][int(playerPos.x + playerRad - 1) / blockSize] != BLOCK) {
			playerPos.y += jumpSpeed;
		}
		else {
			isJump = false;
		}
	}
	if (isJump) {
		jumpSpeed += 1;
	}
}

void Stage1::GetAllCollision()
{
	//プレイヤーとマップの当たり判定
	AllPushingBack();

	//プレイヤーと敵の当たり判定
	Player2EnemyCollision();

	//プレイヤーと藁の当たり判定
	PlayerWalaCollision();
}

void Stage1::AllPushingBack()
{
	//止まる処理
	//左
	if (map[int(playerPos.y) / blockSize][int(playerPos.x) / blockSize] == BLOCK) {
		playerPos.x = block[int(playerPos.y) / blockSize][int(playerPos.x + blockSize - 1) / blockSize].pos.x;
	}
	//右
	else if (map[int(playerPos.y) / blockSize][int(playerPos.x + blockSize - 1) / blockSize] == BLOCK) {
		playerPos.x = block[int(playerPos.y) / blockSize][int(playerPos.x) / blockSize].pos.x;
	}
	//上
	if (map[int(playerPos.y) / blockSize][int(playerPos.x) / blockSize] == BLOCK ||
		map[int(playerPos.y) / blockSize][int(playerPos.x + blockSize - 1) / blockSize] == BLOCK) {
		playerPos.y = block[int(playerPos.y + blockSize - 1) / blockSize][int(playerPos.x) / blockSize].pos.y;
	}
	//下
	else if (map[int(playerPos.y + blockSize - 1) / blockSize][int(playerPos.x) / blockSize] == BLOCK ||
		map[int(playerPos.y + blockSize - 1) / blockSize][int(playerPos.x + blockSize - 1) / blockSize] == BLOCK) {
		playerPos.y = block[int(playerPos.y) / blockSize][int(playerPos.x) / blockSize].pos.y;
	}
}

void Stage1::Player2EnemyCollision()
{
	if (playerPos.y <= enemy_->GetPosition().y + enemy_->GetRad() &&
		playerPos.y + playerRad >= enemy_->GetPosition().y) {
		if (playerPos.x <= enemy_->GetPosition().x + enemy_->GetRad() &&
			playerPos.x + playerRad >= enemy_->GetPosition().x) {
			isHitP2E = true;
		}
		else {
			isHitP2E = false;
		}
	}
	else {
		isHitP2E = false;
	}

	//当たっている間
	if (isHitP2E) { playerColor = BLUE; }
	else { playerColor = 0xFFFFFFFF; }
}

void Stage1::PlayerWalaCollision()
{
	if (playerPos.y <= WalaPos.y + WalaRad &&
		playerPos.y + playerRad >= WalaPos.y) {
		if (playerPos.x <= WalaPos.x + WalaRad &&
			playerPos.x + playerRad >= WalaPos.x)
		{
			RotateFlag = true;
			isHitP2E = true;
		}
		else
		{
			RotateFlag = false;
		}
	}
	else
	{
		RotateFlag = false;
	}
}

void Stage1::Reset()
{
	playerPos = playerPosStart;

	isJump = false;
	
	isGravity = false;

	isHitP2E = false;

	//ステージを次に移動してマップを作り直す
	stage++;
	CreateMap();
}

 void Stage1::CreateMap()
{
	//仮マップ
	int mapTmp1[100][100] = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,3,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,1,0,0,0,0,2,0,0,1,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, };

	//マップ生成
	for (int y = 0; y < 100; y++) {
		for (int x = 0; x < 100; x++) {
			//map[y][x] = mapTmp[stage][y][x];
			map[y][x] = mapTmp1[y][x];

			//ブロックの座標、サイズ設定
			block[y][x].pos.x = float(x * blockSize);
			block[y][x].pos.y = float(y * blockSize);
			block[y][x].size.x = 128.0f;
			block[y][x].size.y = 128.0f;

			//敵がいる場合
			if (map[y][x] == 2) {
				block[y][x].state = ENEMY;
				enemy_->Initialize({ float(x * blockSize), float((y + enemy_->GetRad()) * blockSize) });
			}

			else if (map[y][x] == 3) {
				block[y][x].state = WALA;
				block[y][x].color = blockColor;
			}

			//ブロックがある場合
			else if (map[y][x] == 1) {
				block[y][x].state = BLOCK;
				block[y][x].imagePos.x = 0.0f;
				block[y][x].imagePos.y = 128.0f;
				block[y][x].color = blockColor;
			}

			//ブロックがない場合
			else if (map[y][x] == 0) {
				block[y][x].state = NONE;
				block[y][x].imagePos.x = 128.0f;
				block[y][x].imagePos.y = 0.0f;
			}
			else {}
		}
	}
}

void Stage1::GetDevice()
{
	memcpy(preKeys, keys, 256);
	Novice::GetHitKeyStateAll(keys);
	Novice::GetAnalogInputLeft(0, &stickPosX, &stickPosY);
}

bool Stage1::IsTriggerJump() {
	return keys[DIK_RETURN] && !preKeys[DIK_RETURN] ||
		Novice::IsTriggerButton(0, PadButton::kPadButton10) ? true : false;
}

bool Stage1::IsPushLeft()
{
	return keys[DIK_A] || stickPosX <= -20000 ? true : false;
}

bool Stage1::IsPushRight()
{
	return keys[DIK_D] || stickPosX >= 20000 ? true : false;
}
