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

	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Vector2 playerPos;//実ポジション

	Vector2 playerPosOld;//仮に進んだときの変数

	float playerRad;
	float speed;

	bool isJump = false;
	float jumpSpeed = 0.0f;

	float playerAcceleration = 0.8f;

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

	Block block[100][100]{};

	int blockSize = 128;

	/*int mapHeight = 8;
	int mapWidth = 30;*/

	/*float posXtmp = 0.0f;
	float posYtmp = 0.0f;*/

	int gh1 = Novice::LoadTexture("./Resources/block.png");

	int map[8][15]{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	};

	//スティック操作
	int stickPosX = 0;
	int stickPosY = 0;

	int leftTopX;//左上のX座標
	int leftTopY;//左上のY座標
	int rightTopX;//右上のX座標
	int rightTopY;//右上のY座標
	int leftBottomX;//左下のX座標
	int leftBottomY;//左下のY座標
	int rightBottomX;//右下のX座標
	int rightBottomY;//右下のY座標

};

