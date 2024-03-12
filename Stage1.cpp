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
	speed = 0.0f;
	playerAcceleration = 0.8f;
	pushingSpeed = 4.0f;

	//敵の初期化
	enemy_ = new Enemy();

	isJump = false;
	isLanding = false;
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
	Novice::ScreenPrintf(0, 80, "%d %d %d %d", isLanding, isJump, isHop, map[leftBottomY][leftBottomX] == BLOCK ||
		map[rightBottomY][rightBottomX] == BLOCK);
	Novice::ScreenPrintf(0, 100, "%d %d %d %d", IsHitLeft(), IsHitRight(), IsHitTop(), IsHitBottom());

	Novice::ScreenPrintf(1280, 0, "%d", isJump);
#endif

	//ブロックの描画
	for (int y = 0; y < 100; y++) {
		for (int x = 0; x < 100; x++) {
			if (map[y][x] == 1) {
				Novice::DrawSprite(x * 128, y * 128, gh1, 1, 1, 0.0f, WHITE);
			}
		}
	}

	//敵の描画関数
	enemy_->Draw();

	//プレイヤーの描画
	Novice::DrawBox(int(playerPos.x), int(playerPos.y), int(playerRad), int(playerRad), 0.0f, playerColor, kFillModeSolid);
}

void Stage1::PlayerUpdate()
{
	//移動処理
	PlayerMove();

	if (isJump) {
		playerPos.y += 10.0f;
		BottomPushingBack();
	}

	if (map[int((playerPos.y + playerRad) / blockSize)][int((playerPos.x) / blockSize)] != BLOCK &&
		map[int((playerPos.y + playerRad) / blockSize)][int((playerPos.x + playerRad) / blockSize)] != BLOCK) {
		isJump = true;
	}
	else { isJump = false; }

	//ジャンプ処理
	if (!isHop) {
		//ジャンプボタンを押したら
		if (IsTriggerJump()) {
			//ジャンプ開始
			PlayerJumpInitialize();
		}
	}
	else {
		//ジャンプ更新処理
		PlayerJumpUpdate();
	}

	//重力処理
	if (isJump && !isHop) {
		playerPos.y += 1.0f;
	}
	/*if (!isJump && !isGravity) {
		//浮いているなら
		if (map[int((playerPos.y + playerRad) / blockSize)][int((playerPos.x) / blockSize)] != BLOCK &&
			map[int((playerPos.y + playerRad) / blockSize)][int((playerPos.x + playerRad) / blockSize)] != BLOCK) {
			//重力
			GravityInitialize();
		}
	}
	else {
		//重力更新処理
		GravityUpdate();
	}*/
}

void Stage1::PlayerMove()
{
	//左ボタンを押しているとき
	if (IsPushLeft()) {
		//ブロックにぶつかっている時
		if (IsHitLeft()) {
			//左側押し出し処理
			/*LeftPushingBack();*/
			speed = 0.0f;
		}
		//ぶつかっていない時
		else {
			speed = -5.0f;
		}
	}
	//右ボタンを押しているとき
	else if (IsPushRight()) {
		//ブロックにぶつかっている時
		if (IsHitRight()) {
			//右側押し出し処理
			/*RightPushingBack();*/
			speed = 0.0f;
		}
		//ぶつかっていない時
		else {
			speed = 5.0f;
		}
	}
	else {
		speed = 0.0f;
	}

	//移動
	playerPos.x += speed;
}

void Stage1::PlayerJumpInitialize()
{
	isHop = true;
	jumpSpeed = -30.0f;
	playerAcceleration = 0.8f;
	isGravity = false;
	isLanding = false;
}

void Stage1::PlayerJumpUpdate()
{
	if (!isLanding) {
		//下のブロックにぶつかったとき
		if (map[leftBottomY][leftBottomX] == BLOCK ||
			map[rightBottomY][rightBottomX] == BLOCK) {
			//ジャンプの速度を0にする
			jumpSpeed = 0.0f;
			playerAcceleration = 0.0f;
			//着地開始
			isLanding = true;
		}
		//上のブロックにぶつかったとき
		/*else if (IsHitTop()) {
			//上側押し出し処理
			TopPushingBack();
		}*/
		//上にも下にもぶつかっていないとき
		else {
			//移動
			jumpSpeed += playerAcceleration;
			playerPos.y += jumpSpeed;
		}
	}

	//着地処理
	else {
		//下のブロックに埋まっている時
		//BottomPushingBack();//下側押し出し処理
		//着地終了
		isLanding = false;
		//ジャンプ終了
		isHop = false;
		//加速度を元に戻す
		playerAcceleration = 0.8f;
	}
}

//void Stage1::GravityInitialize()
//{
//	isGravity = true;
//	jumpSpeed = pushingSpeed;
//	isJump = false;
//	isLanding = false;
//}

//void Stage1::GravityUpdate()
//{
//
//	if (!isLanding) {
//		//下のブロックにぶつかったとき
//		if (map[leftBottomY][leftBottomX] == BLOCK ||
//			map[rightBottomY][rightBottomX] == BLOCK) {
//			//落下速度を0にする
//			jumpSpeed = 0.0f;
//			//着地開始
//			isLanding = true;
//		}
//		//上にも下にもぶつかっていないとき
//		else {
//			//落下
//			playerPos.y += jumpSpeed;
//		}
//	}
//	//着地処理
//	else {
//		//下のブロックに埋まっている時
//		BottomPushingBack();//下側押し出し処理
//		//着地終了
//		isLanding = false;
//		//重力処理終了
//		isGravity = false;
//	}
//}

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
	//AllPushingBack();

	//プレイヤーと敵の当たり判定
	Player2EnemyCollision();
}

void Stage1::AllPushingBack()
{
	//押し出し処理
	//左
	if (IsHitLeft()) {
		LeftPushingBack();
	}
	//右
	if (IsHitRight()) {
		RightPushingBack();
	}
}

void Stage1::LeftPushingBack()
{
	while (map[int((playerPos.y) / blockSize)][int((playerPos.x) / blockSize)] == BLOCK ||
		map[int((playerPos.y + playerRad) / blockSize)][int((playerPos.x) / blockSize)] == BLOCK) {
		playerPos.x += pushingSpeed;
	}
}

void Stage1::RightPushingBack()
{
	while (map[int((playerPos.y) / blockSize)][int((playerPos.x + playerRad) / blockSize)] == BLOCK ||
		map[int((playerPos.y + playerRad) / blockSize)][int((playerPos.x + playerRad) / blockSize)] == BLOCK) {
		playerPos.x -= pushingSpeed;
		break;
	}
}

void Stage1::TopPushingBack()
{
	while (1) {
		playerPos.y += pushingSpeed;
		break;
	}
}

void Stage1::BottomPushingBack()
{
	while (map[int((playerPos.y + playerRad - 1) / blockSize)][int((playerPos.x) / blockSize)] == BLOCK ||
		map[int((playerPos.y + playerRad - 1) / blockSize)][int((playerPos.x + playerRad - 1) / blockSize)] == BLOCK) {
		if (!IsHitLeft() && !IsHitRight() || IsHitLeft() && IsHitRight()) {
			playerPos.y -= pushingSpeed;
		}
		isJump = false;
	}
}

bool Stage1::IsHitLeft()
{
	/*int start = int(playerPos.y / blockSize);tt
	int end = int((playerPos.y + playerRad) / blockSize) - 1;
	int X = int((playerPos.x) / blockSize);*/

	//return map[start][X] == BLOCK || map[end][X] == BLOCK ? true : false;

	int startY = int((playerPos.y) / blockSize);
	int endY = int((playerPos.y + playerRad - 1) / blockSize);
	int startX = int((playerPos.x) / blockSize);
	int endX = int((playerPos.x) / blockSize);

	return map[startY][startX] == BLOCK || map[startY][endX] == BLOCK ||
		map[endY][startX] == BLOCK || map[endY][endX] == BLOCK ? true : false;
}

bool Stage1::IsHitRight()
{
	/*int start = int((playerPos.y) / blockSize);
	int end = int((playerPos.y + playerRad) / blockSize) - 1;
	int X = int((playerPos.x + playerRad) / blockSize);*/

	//return map[start][X] == BLOCK || map[end][X] == BLOCK ? true : false;

	int startY = int((playerPos.y) / blockSize);
	int endY = int((playerPos.y + playerRad - 1) / blockSize);
	int startX = int((playerPos.x + playerRad - 1) / blockSize);
	int endX = int((playerPos.x + playerRad - 1) / blockSize);

	return map[startY][startX] == BLOCK || map[startY][endX] == BLOCK ||
		map[endY][startX] == BLOCK || map[endY][endX] == BLOCK ? true : false;
}

bool Stage1::IsHitTop()
{
	/*int start = int((playerPos.x) / blockSize);
	int end = int((playerPos.x + playerRad) / blockSize);
	int Y = int((playerPos.y) / blockSize);

	return map[Y][start] == BLOCK || map[Y][end] == BLOCK ? true : false;*/

	int startY = int((playerPos.y + playerRad - 1) / blockSize);
	int endY = int((playerPos.y + playerRad - 1) / blockSize);
	int startX = int((playerPos.x) / blockSize);
	int endX = int((playerPos.x + playerRad - 1) / blockSize);

	return map[startY][startX] == BLOCK || map[startY][endX] == BLOCK ||
		map[endY][startX] == BLOCK || map[endY][endX] == BLOCK ? true : false;
}

bool Stage1::IsHitBottom()
{
	/*int start = int((playerPos.x) / blockSize);
	int end = int((playerPos.x + playerRad) / blockSize);
	int Y = int((playerPos.y + playerRad) / blockSize) - 1;

	return map[Y][start] == BLOCK || map[Y][end] == BLOCK ? true : false;*/

	int startY = leftBottomY;
	int endY = rightBottomY;
	int startX = leftBottomX;
	int endX = rightBottomX;

	return map[startY][startX] == BLOCK || map[startY][endX] == BLOCK ||
		map[endY][startX] == BLOCK || map[endY][endX] == BLOCK ? true : false;
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
	playerAcceleration = 0.8f;

	isJump = false;
	isLanding = false;
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
