#pragma once
#include "Scene.h"
#include <Novice.h>
#include "Vector2.h"

class Stage1 : public Scene
{
public:

	void Initialize() override;

	void Update() override;

	void Draw() override;

private:
	void GetDevice();

	void CreateMap();

	void Player2MapCollision();

	void PlayerMove();

	void PlayerJumpInitialize();
	void PlayerJumpUpdate();

	void Reset();

	bool isTriggerSpace();

private:
	enum MapInfo {
		NONE,
		BLOCK
	};

	struct Block {
		MapInfo state; //ブロックの状態
		Vector2 pos; //座標
		Vector2 size; //画像の大きさ
		Vector2 imagePos; //読み込む画像の座標
	};

private:

	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	int stickPosX = 0;
	int stickPosY = 0;

	int gh1 = Novice::LoadTexture("./Resources/block.png");

	Vector2 playerPos;//実ポジション
	float playerRad;
	float speed;
	float playerAcceleration = 0.8f;

	bool isJump = false;
	float jumpSpeed = 0.0f;

	Block block[100][100]{};
	int blockSize = 128;

	int map[100][100]{};

	int stage = 0;

	bool isHitP2M = false;

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

