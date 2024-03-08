#include "Stage1.h"

Stage1::Stage1()
{
}

Stage1::~Stage1()
{
	delete enemy_;
}

void Stage1::Initialize() {

	playerPos = { 600.0f,768.0f };
	playerRad = 128.0f;
	speed = 5.0f;

	//敵の初期化
	enemy_ = new Enemy();

	isJump = false;
	isLanding = false;
	isHitLeftRight = false;
	isHitBottom = false;
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
	Novice::ScreenPrintf(0, 60, "bottom pos : left:%d %d, right:%d %d", leftBottomX, leftBottomY, rightBottomX, rightBottomY);
	Novice::ScreenPrintf(0, 80, "mapPos : leftTop:%d %d %d, leftBottom:%d %d %d",
		leftTopX, leftTopY, map[leftTopX - 1][leftTopY - 1],
		leftBottomX, leftBottomY, map[leftBottomX - 1][leftBottomY + 1]);
	Novice::ScreenPrintf(0, 100, "mapPos : rightTop:%d %d %d, rihgtBottom:%d %d %d",
		rightTopX, rightTopY, map[rightTopX + 1][rightTopY - 1],
		rightBottomX, rightBottomY, map[rightBottomX + 1][rightBottomY + 1]);
	Novice::ScreenPrintf(0, 200, "tmp : %d %d, %d", int(playerPos.x / blockSize), int(playerPos.y / blockSize + 1), map[int(playerPos.y / blockSize + 1)][int(playerPos.x / blockSize)]);

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

	//敵の描画関数
	enemy_->Draw();

	//プレイヤーの描画
	Novice::DrawBox(int(playerPos.x), int(playerPos.y), int(playerRad), int(playerRad), 0.0f, playerColor, kFillModeSolid);
}

void Stage1::GetDevice()
{
	memcpy(preKeys, keys, 256);
	Novice::GetHitKeyStateAll(keys);
	Novice::GetAnalogInputLeft(0, &stickPosX, &stickPosY);
}

void Stage1::CreateMap()
{
	//仮マップ
	int mapTmp1[100][100] = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
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

			//ブロックがある場合
			else if (map[y][x] == 1) {
				block[y][x].state = BLOCK;
				block[y][x].imagePos.x = 0.0f;
				block[y][x].imagePos.y = 128.0f;
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

void Stage1::PlayerUpdate()
{
	//移動処理
	PlayerMove();

	if (!isJump) {
		//ジャンプボタンを押したら
		if (isTriggerSpace()) {
			//ジャンプ開始
			PlayerJumpInitialize();
		}

		//重力
		Gravity();
	}
	else {
		//ジャンプ更新処理
		PlayerJumpUpdate();
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

	//上側押し出し処理
	TopPushingBack();

	//着地
	if (map[leftBottomY][leftBottomX] == BLOCK ||
		map[rightBottomY][rightBottomX] == BLOCK) {
		isLanding = true;
	}

	if (isLanding) {
		//下側押し出し処理
		BottomPushingBack();

		//ジャンプ終了
		isLanding = false;
		isJump = false;
	}
}

void Stage1::Gravity()
{
	//重力処理
	float gravity = 0.1f;
	while (map[int((playerPos.y + playerRad) / blockSize)][int((playerPos.x) / blockSize)] != BLOCK &&
		map[int((playerPos.y + playerRad) / blockSize)][int((playerPos.x + playerRad) / blockSize)] != BLOCK) {
		playerPos.y += gravity;
	}

	//下側押し出し処理
	BottomPushingBack();
}

void Stage1::GetAllCollision()
{
	//右上座標
	rightTopX = int((playerPos.x + playerRad) - 1) / blockSize;
	rightTopY = int((playerPos.y)) / blockSize;

	// 右下座標
	rightBottomX = int((playerPos.x + playerRad) - 1) / blockSize;
	rightBottomY = int((playerPos.y + playerRad) - 1) / blockSize;

	// 左上座標
	leftTopX = int((playerPos.x)) / blockSize;
	leftTopY = int((playerPos.y)) / blockSize;

	// 左下座標
	leftBottomX = int((playerPos.x)) / blockSize;
	leftBottomY = int((playerPos.y + playerRad) - 1) / blockSize;

	//プレイヤーとマップチップの当たり判定
	//Player2MapCollision();

	//左右押し出し処理
	AllPushingBack();

	//プレイヤーと敵の当たり判定
	Player2EnemyCollision();
}

void Stage1::AllPushingBack()
{
	//押し出し処理
	//左
	LeftPushingBack();
	//右
	RightPushingBack();
}

void Stage1::LeftPushingBack()
{
	while (map[int((playerPos.y + playerRad / 2) / blockSize)][int((playerPos.x) / blockSize)] == BLOCK) {
		isHitLeftRight = true;

		playerPos.x += 0.1f;
	}
	isHitLeftRight = false;
}

void Stage1::RightPushingBack()
{
	while (map[int((playerPos.y + playerRad / 2) / blockSize)][int((playerPos.x + playerRad) / blockSize)] == BLOCK) {
		isHitLeftRight = true;

		playerPos.x -= 0.1f;
	}
	isHitLeftRight = false;
}

void Stage1::TopPushingBack()
{
	while (map[int((playerPos.y) / blockSize)][int((playerPos.x + playerRad / 2) / blockSize)] == BLOCK) {
		playerPos.y += 0.1f;
	}
}

void Stage1::BottomPushingBack()
{
	while (map[int((playerPos.y + playerRad) / blockSize)][int((playerPos.x + playerRad / 2) / blockSize)] == BLOCK) {
		isHitBottom = true;

		playerPos.y -= 0.1f;
	}
	isHitBottom = false;
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

void Stage1::Reset()
{
	playerPos = { 400.0f,768.0f };

	isJump = false;
	isLanding = false;
	isHitLeftRight = false;
	isHitBottom = false;
	isHitP2E = false;

	//ステージを次に移動してマップを作り直す
	stage++;
	CreateMap();
}

bool Stage1::isTriggerSpace() {
	if (keys[DIK_SPACE] && !preKeys[DIK_SPACE] ||
		Novice::IsTriggerButton(0, PadButton::kPadButton10)) {
		return true;
	}
	return false;
}

//使用していない
//void Stage1::Player2MapCollision()
//{
//	//実ポジションを仮ポジションに代入
//	Vector2 playerPosOld = playerPos;
//
//	//ブロックに当たった時
//	if (map[leftBottomY][leftBottomX] == BLOCK ||
//		map[leftTopY][leftTopX] == BLOCK ||
//		map[rightTopY][rightTopX] == BLOCK ||
//		map[rightBottomY][rightBottomX] == BLOCK) {
//		isHitP2M = true;
//	}
//	else {
//		isHitP2M = false;
//	}
//
//	//当たっている間移動不可
//	if (isHitP2M) {
//		playerPos.x = playerPosOld.x;
//	}
//}
