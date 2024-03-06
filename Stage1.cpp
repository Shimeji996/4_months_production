#include "Stage1.h"

Stage1::Stage1()
{
}

Stage1::~Stage1()
{
	delete enemy_;
}

void Stage1::Initialize() {

	playerRad = 64.0f;
	speed = 5.0f;

	//各クラスの初期化関数
	enemy_->Initialize();

	Reset();
}

void Stage1::Update() {

	//デバイス関連
	GetDevice();

	//各クラスの更新関数
	enemy_->Update();

	//ブロックに当たっていないなら
	if (!isHitP2M) {
		//移動処理
		PlayerMove();
	}

	//ジャンプ処理
	if (!isJump) {
		if (isTriggerSpace()) {
			PlayerJumpInitialize();
		}
	}
	else if (isJump) {
		PlayerJumpUpdate();
	}
	else {}

	//当たり判定
	Player2MapCollision();
}

void Stage1::Draw() {
#ifdef _DEBUG
	Novice::ScreenPrintf(0, 0, "Stage1");
	Novice::ScreenPrintf(0, 20, "playerPos : %2.0f %2.0f", playerPos.x, playerPos.y);
	Novice::ScreenPrintf(0, 40, "left pos : %d %d", int(playerPos.x) / blockSize - 1, int(playerPos.y) / blockSize);
#endif

	//ブロックの描画
	for (int y = 0; y < 100; y++) {
		for (int x = 0; x < 100; x++) {
			if (map[y][x] == 1) {
				Novice::DrawSprite(
					x * 128, y * 128, gh1, 1, 1, 0.0f, WHITE);
			}
		}
	}

	//プレイヤーの描画
	Novice::DrawBox(int(playerPos.x), int(playerPos.y), int(playerRad), int(playerRad), 0.0f, 0xFFFFFFFF, kFillModeSolid);

	//各クラスの描画関数
	enemy_->Draw();
}

void Stage1::GetDevice()
{
	memcpy(preKeys, keys, 256);
	Novice::GetHitKeyStateAll(keys);
	Novice::GetAnalogInputLeft(0, &stickPosX, &stickPosY);
}

void Stage1::CreateMap()
{
	int mapTmp1[100][100] = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,1,0,0,0,0,0,1,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, };

	for (int y = 0; y < 100; y++) {
		for (int x = 0; x < 100; x++) {
			if (stage == 1) {
				map[y][x] = mapTmp1[y][x];

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
}

void Stage1::Player2MapCollision()
{
	//実ポジションを仮ポジションに代入
	Vector2 playerPosOld = playerPos;

	//右上座標
	int rightTopX = int((playerPos.x + playerRad) - 1) / blockSize;
	int rightTopY = int(playerPos.y - playerRad) / blockSize;

	// 右下座標
	int rightBottomX = int((playerPos.x + playerRad) - 1) / blockSize;
	int rightBottomY = int((playerPos.y + playerRad) - 1) / blockSize;

	// 左上座標
	int leftTopX = int((playerPos.x - playerRad) / blockSize + 0.5f);
	int leftTopY = int((playerPos.y - playerRad)) / blockSize;

	// 左下座標
	int leftBottomX = int((playerPos.x - playerRad) / blockSize + 0.5f);
	int leftBottomY = int((playerPos.y + playerRad) - 1) / blockSize;

	//ブロックに当たった時
	if (map[leftTopY][leftTopX] == BLOCK ||
		map[leftBottomY][leftBottomX] == BLOCK ||
		map[rightTopY][rightTopX] == BLOCK ||
		map[rightBottomY][rightBottomX] == BLOCK) {
		isHitP2M = true;
	}
	else {
		isHitP2M = false;
	}

	//当たっている間移動不可
	if (isHitP2M) {
		playerPos.x = playerPosOld.x;
		playerPos.y = playerPosOld.y;
	}
}

void Stage1::PlayerMove()
{
	if (keys[DIK_A] || stickPosX <= -20000) {
		playerPos.x -= speed;
	}
	else if (keys[DIK_D] || stickPosX >= 20000) {
		playerPos.x += speed;
	}
	else {}
}

void Stage1::PlayerJumpInitialize()
{
	isJump = true;
	jumpSpeed = -18.0f;
}

void Stage1::PlayerJumpUpdate()
{
	jumpSpeed += playerAcceleration;
	playerPos.y += jumpSpeed;

	// 右下座標
	int rightBottomX = int((playerPos.x + playerRad) - 1) / blockSize;
	int rightBottomY = int((playerPos.y + playerRad) - 1) / blockSize;

	// 左下座標
	int leftBottomX = int((playerPos.x - playerRad) / blockSize + 0.5f);
	int leftBottomY = int((playerPos.y + playerRad) - 1) / blockSize;

	//着地
	if (map[leftBottomY][leftBottomX] == BLOCK) {
		float tmp = float(1024 - blockSize - (map[leftBottomY - 1][leftBottomX] + playerRad));
		if (tmp < 0) {
			tmp *= -1;
		}
		playerPos.y = tmp;
		isJump = false;
	}
	else if (map[rightBottomY][rightBottomX] == BLOCK) {
		float tmp = float(1024 - blockSize - (map[rightBottomY - 1][rightBottomX] + playerRad));
		if (tmp < 0) {
			tmp *= -1;
		}
		playerPos.y = tmp;
		isJump = false;
	}
	else {}
}

void Stage1::Reset()
{
	playerPos = { 400.0f,832.0f };

	stage++;
	CreateMap();
}

bool Stage1::isTriggerSpace() {
	if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
		{
			return true;
		}

		return false;
	}
