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
	void GetDevice();

	void CreateMap();

	void PlayerUpdate();
	void PlayerMove();
	void PlayerJumpInitialize();
	void PlayerJumpUpdate();

	void GetAllCollision();
	void Player2EnemyCollision();

	//プレイヤーと藁の当たり判定
	void PlayerWalaCollision();

	//プレイヤーを藁から飛ばす処理
	
	//回転初期化関数
	
	//回転更新関数

	void AllPushingBack();

	void Reset();

	bool IsTriggerJump();
	bool IsPushLeft();
	bool IsPushRight();

private:
	enum MapInfo {
		NONE,
		BLOCK,
		ENEMY,
		WALA,
	};

	struct Block {
		MapInfo state; //ブロックの状態
		Vector2 pos; //座標
		Vector2 size; //画像の大きさ
		Vector2 imagePos; //読み込む画像の座標
		int color;//色
	};

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
	int gh3 = Novice::LoadTexture("./Resources/komedawara.png");

	//プレイヤー
	Vector2 playerPos;
	Vector2 playerPosStart;
	float playerRad;
	float speed;
	unsigned int playerColor = 0xFFFFFFFF;

	bool isJump = false;
	float jumpSpeed = 0.0f;

	bool isGravity = false;

	//藁
	Vector2 WalaPos;
	float WalaRad;
	float rotateSpeed;

	//藁の回転
	bool RotateFlag = false;

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