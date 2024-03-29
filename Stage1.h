﻿#pragma once
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

	void GravityInitialize();
	void GravityUpdate();

	void Reset();

	void GetAllCollision();
	//void Player2MapCollision();
	void Player2EnemyCollision();

	void AllPushingBack();
	void LeftPushingBack();
	void RightPushingBack();
	void TopPushingBack();
	void BottomPushingBack();

	bool IsHitLeft();
	bool IsHitRight();
	bool IsHitTop();
	bool IsHitBottom();

	bool IsTriggerJump();
	bool IsPushLeft();
	bool IsPushRight();

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

	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	int stickPosX = 0;
	int stickPosY = 0;

	int gh1 = Novice::LoadTexture("./Resources/Mblock.png");
	int gh2 = Novice::LoadTexture("./Resources/stage00.png");

	Vector2 playerPos;//実ポジション
	float playerRad;
	float speed;
	float speed1;
	float playerAcceleration = 0.8f;
	unsigned int playerColor = 0xFFFFFFFF;
	unsigned int playerColor1 = 0xFFFFFFFF;
	unsigned int playerColor2 = 0xFFFFFFFF;
	unsigned int playerColor3 = 0xFFFFFFFF;
	unsigned int playerColor4 = 0xFFFFFFFF;

	float scenePosX;
	float scenePosY;

	bool isJump = false;
	float jumpSpeed = 0.0f;

	bool isSpeed = false;

	bool isLanding = false;

	bool isGravity = false;

	bool isHop = false;

	float pushingSpeed = 0.1f;

	//敵の生成
	Enemy* enemy_ = nullptr;

	Block block[100][100]{};
	int blockSize = 128;
	int blockColor = 0xFFFFFFFF;

	int map[100][100]{};

	int stage = 0;

	bool isHitP2E = false;

	// 背景
	int viewPosX = 0;
	int viewPosY = 0;

	//Vector2 playerPosOld;//仮に進んだときの変数

	int leftTopX;//左上のX座標
	int leftTopY;//左上のY座標
	int rightTopX;//右上のX座標
	int rightTopY;//右上のY座標
	int leftBottomX;//左下のX座標
	int leftBottomY;//左下のY座標
	int rightBottomX;//右下のX座標
	int rightBottomY;//右下のY座標
};