#pragma once
#include "Scene.h"
#include <Novice.h>
#include "Vector2.h"

#include "Enemy.h"

class Stage1 : public Scene
{
public:

	Stage1();
	~Stage1();
	void Initialize() override;
	void Update() override;
	void Draw() override;

private:
	enum MapInfo {
		NONE,
		BLOCK,
		ENEMY,
	};

	struct Block {
		MapInfo state; //ブロックの状態
		Vector2 pos; //座標
		Vector2 size; //画像の大きさ
		Vector2 imagePos; //読み込む画像の座標
		int color;//色
	};

private:
	//プレイヤー
	void PlayerUpdate();
	void PlayerMove();
	void PlayerJumpInitialize();
	void PlayerJumpUpdate();

	//当たり判定
	void GetAllCollision();
	void Player2EnemyCollision();
	void AllPushingBack();

	//マップ
	void CreateMap();

	//リセット
	void Reset();

	//デバイス関連
	void GetDevice();

	//キー操作
	bool IsTriggerJump();
	bool IsPushLeft();
	bool IsPushRight();

private:
	//キーボード
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };
	//スティック
	int stickPosX = 0;
	int stickPosY = 0;

	//画像
	int gh1 = Novice::LoadTexture("./Resources/Mblock.png");
	int gh2 = Novice::LoadTexture("./Resources/stage00.png");

	//プレイヤー
	Vector2 playerPos;
	Vector2 playerPosStart;
	float playerRad;
	float speed;
	unsigned int playerColor = 0xFFFFFFFF;

	bool isJump = false;
	float jumpSpeed = 0.0f;
	bool isGravity = false;

	//敵の生成
	Enemy* enemy_ = nullptr;

	//ブロック
	Block block[100][100]{};
	int blockSize = 128;
	int blockColor = 0xFFFFFFFF;

	//マップ
	int map[100][100]{};

	//ステージ
	int stage = 0;

	//当たり判定
	bool isHitP2E = false;
};